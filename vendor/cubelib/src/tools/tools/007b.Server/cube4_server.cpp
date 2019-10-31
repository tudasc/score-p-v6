/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016                                                     **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


/*-------------------------------------------------------------------------*/
/**
 *  @file
 *  @ingroup CUBE_tools
 *  @brief   Server application for the client-server network layer.
 *
 *  The cube server will listen on a given port for incoming client
 *  connections to serve information read and computed from a Cube file
 *  local to the server.
 **/
/*-------------------------------------------------------------------------*/


#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "CubeError.h"
#include "CubeNetworkRequest.h"
#include "CubeServerCallbackData.h"
#include "CubeServerConnection.h"
#include "CubeSocket.h"
#include "CubeUrl.h"

using namespace std;
using namespace cube;

/// @brief Signal handler to clean up child processes.
///
/// @param s
///     Signal number
///
void
sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0)
    {
    }

    errno = saved_errno;
}


/// @brief Print command-line options and usage info
///
const string&
getUsage()
{
    stringstream portNo;
    portNo << Url::getDefaultPort();
    static const string USAGE =
        "Usage: cube_server [options]\n"
        " -h, -?    Print this help message.\n"
        " -p N      Bind socket on port N (default port: " + portNo.str()
        + ")\n"
    ;

    return USAGE;
}


int
main(int   argc,
     char* argv[])
{
    size_t           portNo = Url::getDefaultPort();
    struct sigaction sigAction;
    stringstream     message;

    int option_arg;

    // check for command line parameters
    while ((option_arg = getopt(argc, argv, "h?p:")) != -1)
    {
        switch (option_arg)
        {
            case 'h':
            case '?':
                cerr << getUsage() << endl;
                exit(EXIT_SUCCESS);
                break;

            case 'p':
                portNo = atoi(optarg);
        }
    }

    ServerConnection::Ptr connection;
    try
    {
        connection = ServerConnection::create(Socket::create(),
                                              portNo);
    }
    catch (NetworkError& theError)
    {
        cerr << theError.what() << endl;
        exit(EXIT_FAILURE);
    }
    message << "[" << getpid() << "] Cube Server: "
            << connection->getInfoString();
    cerr << message.str() << endl;
    message.str("");

    // install signal handler
    sigAction.sa_handler = sigchld_handler;    // reap all dead processes
    sigemptyset(&sigAction.sa_mask);
    sigAction.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sigAction, NULL) == -1)
    {
        cerr << "Could not install signal handler." << endl;
        exit(EXIT_FAILURE);
    }

    while (connection->isListening())
    {
        // wait for incoming connection
        message << "[" << getpid() << "] Waiting for connections on port " << portNo << ".";
        cerr << message.str() << endl;
        message.str("");

        try
        {
            connection->accept();
        }
        catch (const exception& err)
        {
            message << "[" << getpid() << "] " << err.what();
            cerr << message.str() << endl;
            message.str("");
            continue;
        }
        message << "[" << getpid() << "] Accepted connection";
        cerr << message.str() << endl;
        message.str("");

        // fork process handling connection to client
        if (!fork())
        {
            // child does not need to listen to the server socket
            try
            {
                connection->stopListening();
            }
            catch (const exception& err)
            {
                message << "[" << getpid() << "] " << err.what();
                cerr << message.str() << endl;
                message.str("");
                exit(EXIT_FAILURE);
            }
            message << "[" << getpid() << "] Child stopped listening.";
            cerr << message.str() << endl;
            message.str("");
        }
        else
        {
            // parent can disconnect socket handled by child
            try
            {
                connection->disconnect();
            }
            catch (const exception& err)
            {
                message << "[" << getpid() << "] " << err.what();
                cerr << message.str() << endl;
                message.str("");
                exit(EXIT_FAILURE);
            }
            message << "[" << getpid() << "] Parent disconnected.";
            cerr << message.str() << endl;
            message.str("");
        }

        /* Allocated here and only one instance of ServerCallbackData, so that
         * server-side information is truly stored between distinct network
         * requests i.e. for the whole time of connection->isEstablished()
         */
        ServerCallbackData* data = new ServerCallbackData();

        // listen for incoming request on established connection
        while (connection->isEstablished())
        {
            // read request ID from stream
            NetworkRequest::Ptr request;
            try
            {
                // create request from input on connection stream
                request = connection->createRequestFromStream();

                #if defined(CUBE_NETWORK_DEBUG)
                    message << "[" << getpid() << "] -- Receive request: "
                            << request->getName() << " --";
                    cerr << message.str() << endl;
                    message.str("");
                #endif

                // complete reception of request data
                request->receiveRequest(*connection, data);

                #if defined(CUBE_NETWORK_DEBUG)
                    message << "[" << getpid() << "] -- done --";
                    cerr << message.str() << endl;
                    message.str("");
                #endif

                request->processRequest(data);
            }
            catch (const RecoverableNetworkError& theError)
            {
                message << "[" << getpid()
                        << "] ### Recoverable error while handling request.\n"
                        << "[" << getpid() << "] ### " << theError.what();
                cerr << message.str() << endl;
                message.str("");

                request->sendErrorResponse(*connection,
                                           REQUEST_ERROR_RECOVERABLE,
                                           theError.what());

                break;
            }
            catch (const UnrecoverableNetworkError& theError)
            {
                message << "[" << getpid()
                        << "] ### Unrecoverable error while handling request.\n"
                        << "[" << getpid() << "] ### " << theError.what();
                cerr << message.str() << endl;
                message.str("");

                request->sendErrorResponse(*connection,
                                           REQUEST_ERROR_UNRECOVERABLE,
                                           theError.what());
                connection->disconnect();

                break;
            }
            catch (const std::exception& theError)
            {
                message << "[" << getpid()
                        <<
                    "] ### Unexpected exception while handling request.\n"
                        << "[" << getpid() << "] ### " << theError.what();
                cerr << message.str() << endl;
                message.str("");
            }
            try
            {
                #if defined(CUBE_NETWORK_DEBUG)
                    message << "[" << getpid() << "] -- Send response --";
                    cerr << message.str() << endl;
                    message.str("");
                #endif

                // reply with corresponding response
                request->sendResponse(*connection, data);

                #if defined(CUBE_NETWORK_DEBUG)
                    message << "[" << getpid() << "] -- done --";
                    cerr << message.str() << endl;
                    message.str("");
                #endif
            }
            catch (NetworkError& theError)
            {
                message << "[" << getpid() << "] ### Failed to send response.\n"
                        << "[" << getpid() << "] ### " << theError.what();
                cerr << message.str() << endl;
                message.str("");

                connection->disconnect();

                break;
            }
            catch (const std::exception& theError)
            {
                message << "[" << getpid()
                        <<
                    "] ### Unexpected exception while handling request.\n"
                        << "[" << getpid() << "] ### " << theError.what();
                cerr << message.str() << endl;
                message.str("");
            }
        }    // connection->isEstablished()

        message << "[" << getpid() << "] Connection terminated.";
        cerr << message.str() << endl;
        message.str("");

        // reset connection protocol
        connection->setProtocolVersion(0);
    }

    message << "[" << getpid() << "] Done.";
    cerr << message.str() << endl;
    message.str("");
}
