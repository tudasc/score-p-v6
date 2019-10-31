
:: 
:: This file is part of the CUBE software (http:\\www.scalasca.org\cube%
::
:: Copyright (c) 2009-2019, 
::    Forschungszentrum Juelich GmbH, Germany
::    German Research School for Simulation Sciences GmbH, Juelich\Aachen, Germany
::
:: Copyright (c) 2009-2014, 
::    RWTH Aachen University, Germany
::    Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
::    Technische Universitaet Dresden, Germany
::    University of Oregon, Eugene, USA
::    Forschungszentrum Juelich GmbH, Germany
::    German Research School for Simulation Sciences GmbH, Juelich\Aachen, Germany
::    Technische Universitaet Muenchen, Germany
::
:: See the COPYING file in the package base directory for details.
::
:: maintainer Pavel Saviankou <p.saviankou@fz-juelich.de>

set MINGW="C:/Qt/Tools/mingw730_64"
set NSIS="C:\Program Files (x86)\NSIS"
set srcdir=..\..\
set PWD=%~dp0
set PREFIX=%1
set TARGET=C:\Scalasca-Soft\Install\Cube2.0\%PREFIX%\install


mkdir  %TARGET%\bin
mkdir  %TARGET%\lib
mkdir  %TARGET%\include\cubelib
mkdir  %TARGET%\share\icons
mkdir  %TARGET%\share\doc\cube\examples

for %%f in ( 
cube
tools\calltree
tools\canonize
tools\clean
tools\cmp
tools\commoncalltree
tools\cube3to4
tools\cube4to3
tools\cut
tools\derive
tools\diff
tools\dump
tools\exclusify
tools\inclusify
tools\info
tools\isempty
tools\mean
tools\merge
tools\nodeview
tools\part
tools\rank
tools\regioninfo
tools\remap2
tools\sanity
tools\score
tools\stat
tools\tau2cube
tools\test
tools\topoassist
) do (
cd  %%f
qmake 
mingw32-make clean
mingw32-make
cd %PWD%
echo "Copy %%f..."
copy %%f\release\*.exe %TARGET%\bin
copy %%f\release\*.dll %TARGET%\bin
copy %%f\release\*.a   %TARGET%\lib
)


::GOTO:EOF

echo "Copy system libraries..."
copy %MINGW%\bin\libgcc_s_*.dll %TARGET%\bin
copy %MINGW%\bin\libstdc*-6.dll %TARGET%\bin
copy %MINGW%\bin\libwinpthread*.dll %TARGET%\bin
copy C:\MinGW\msys\1.0\bin\msys-1.0.dll %TARGET%\bin
copy C:\MinGW\msys\1.0\bin\msys-z.dll %TARGET%\bin
copy C:\Scalasca-Soft\Misc\regex-2.7-bin\bin\regex2.dll %TARGET%\bin
echo "Copy c++ header files..."
for %%f in (
%srcdir%\src\cube\include\service
%srcdir%\src\cube\include\service\cubelayout 
%srcdir%\src\cube\include\service\cubelayout\layout 
%srcdir%\src\cube\include\service\cubelayout\readers 
%srcdir%\src\cube\include\dimensions\metric 
%srcdir%\src\cube\include\dimensions\metric\strategies 
%srcdir%\src\cube\include\dimensions\metric\data 
%srcdir%\src\cube\include\dimensions\metric\cache 
%srcdir%\src\cube\include\dimensions\metric\data\rows 
%srcdir%\src\cube\include\dimensions\metric\matrix 
%srcdir%\src\cube\include\dimensions\metric\index 
%srcdir%\src\cube\include\dimensions\metric\value 
%srcdir%\src\cube\include\dimensions\metric\value\trafo 
%srcdir%\src\cube\include\dimensions\metric\value\trafo\single_value 
%srcdir%\src\cube\include\dimensions\calltree 
%srcdir%\src\cube\include\dimensions\system 
%srcdir%\src\cube\include\dimensions 
%srcdir%\src\cube\include\network
%srcdir%\src\cube\include\syntax 
%srcdir%\src\cube\include\syntax\cubepl\evaluators 
%srcdir%\src\cube\include\syntax\cubepl\evaluators\nullary 
%srcdir%\src\cube\include\syntax\cubepl\evaluators\nullary\statements 
%srcdir%\src\cube\include\syntax\cubepl\evaluators\unary 
%srcdir%\src\cube\include\syntax\cubepl\evaluators\unary\functions\single_argument 
%srcdir%\src\cube\include\syntax\cubepl\evaluators\unary\functions\two_arguments 
%srcdir%\src\cube\include\syntax\cubepl\evaluators\unary\functions\lambda_calcul 
%srcdir%\src\cube\include\syntax\cubepl\evaluators\binary 
%srcdir%\src\cube\include\syntax\cubepl 
%srcdir%\src\cube\include\derivated 
%srcdir%\src\cube\include\topologies 
%srcdir%\src\cube\include\ 
%srcdir%\src\tools\common_inc\ 
) do (
copy %%f  %TARGET%\include\cubelib\.
)
echo "Copy generated header files..."
copy %srcdir%\vpath\src\*.h %TARGET%\include\cubelib\.





echo Copy Cube documentation..."
copy  %srcdir%\doc\*.pdf %TARGET%\share\doc\cube
@echo "Copy Cube images..."
copy  %srcdir%\share\icons\* %TARGET%\share\icons\.
@echo "Copy Cube license..."
copy  %srcdir%\COPYING %TARGET%\license.txt

echo "NOW COMPILE NSIS script..." 


