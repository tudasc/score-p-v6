##*************************************************************************##
##  CUBE        http://www.scalasca.org/                                   ##
##*************************************************************************##
##  Copyright (c) 1998-2018                                                ##
##  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          ##
##                                                                         ##
##  Copyright (c) 2009-2015                                                ##
##  German Research School for Simulation Sciences GmbH,                   ##
##  Laboratory for Parallel Programming                                    ##
##                                                                         ##
##  This software may be modified and distributed under the terms of       ##
##  a BSD-style license.  See the COPYING file in the package base         ##
##  directory for details.                                                 ##
##*************************************************************************##



## The SUBDIRS variable holds a list of subdirectories automake (recursivly)
## must build.
SUBDIRS = $(subdirs) $(ax_config_subdirs)

## ACLOCAL_AMFLAGS contains options to pass to aclocal when aclocal.m4 is to be
## rebuilt by make. This line is also used by autoreconf to run aclocal with
## suitable options, or by autopoint and gettextize to locate the place where
## Gettext's macros should be installed. So even if you do not really care about
## the rebuild rules, you should define ACLOCAL_AMFLAGS.
ACLOCAL_AMFLAGS = -I build-config/m4 -I vendor/common/build-config/m4
PHONY_TARGETS =





include vendor/common/build-config/Makefile.inc.am
include vendor/windows/Makefile.win32.inc.am
include build-config/platforms/platforms.am
include vendor/common/build-config/platforms.am

###############################################################################
## testing
##

SCOREP_RECURSIVE_TARGETS += \
    unittest-recursive \
    integrationtest-recursive
    
unittest-sp:
unittest: unittest-recursive

integrationtest-sp:
integrationtest: integrationtest-recursive
                                                                             ##
                                                                             ##
###############################################################################


## To install configuration summary file(s)
pkgdata_DATA = \
    @PACKAGE@.summary

## To install extra documentation files
dist_doc_DATA = \
    README \
    OPEN_ISSUES

## To clean up configuration summary files
DISTCLEANFILES += \
    $(builddir)/config.summary \
    $(builddir)/@PACKAGE@.summary


## Still, sometimes there are files that must be distributed, but which are not
## covered in the automatic rules. These files should be listed in the 
## EXTRA_DIST variable. You can mention files from subdirectories in EXTRA_DIST.
## 
## You can also mention a directory in EXTRA_DIST. In this case the entire
## directory will be recursively copied into the distribution. Please note that
## this will also copy everything in the directory, including CVS/RCS version
## control files. We recommend against using this feature.
EXTRA_DIST += $(srcdir)/src/config.h.in \
	      $(srcdir)/src/cubelib-version.h.in \
	      $(srcdir)/src/cubelib-config-custom.h \
              $(srcdir)/build-config/VERSION \
              $(srcdir)/build-config/REVISION \
              $(srcdir)/build-config/REVISION_COMMON \
              $(srcdir)/build-config/tap-driver.sh \
	      $(srcdir)/vendor/common/build-config/generate-library-version.sh \
	      $(srcdir)/vendor/common/build-config/generate-package-version.sh \
              $(srcdir)/vendor/common/build-config/test-runner-plain.sh \
	      $(srcdir)/share/@PACKAGE@/* \
              $(srcdir)/build-frontend/configure.ac \
              $(srcdir)/build-frontend/aclocal.m4   \
              $(srcdir)/build-frontend/Makefile.am  \
              $(srcdir)/build-frontend/Makefile.in  \
              $(srcdir)/build-frontend/configure    \
              $(srcdir)/src/cubelib-config-frontend.h.in


CLEANFILES += \
    src/tools/tools/0002.Config/cubelib_config_usage.h 

BUILT_SOURCES += \
    src/tools/tools/0002.Config/cubelib_config_usage.h

src/tools/tools/0002.Config/cubelib_config_usage.h: $(srcdir)/src/tools/tools/0002.Config/cubelib_config_usage.dox.in
	$(AM_V_GEN)$(AWK) '{print "\"" $$0 "\\n\""}' $< >$@


dist-hook: \
    doxygen-user-pack


clean-local: \
    doxygen-dev-clean \
    doxygen-user-clean

CLEANFILES += 
DISTCLEANFILES +=\
		$(builddir)/config.summary \
                $(builddir)/@PACKAGE@.summary \
		include/cubelib/cubelib_error_decls.gen.h

uninstall-local:
	rm -rf $(DESTDIR)$(includedir)/cubelib
	rm -rf $(DESTDIR)$(datadir)/@PACKAGE_NAME@
	rm -rf $(DESTDIR)$(datadir)/@PACKAGE@
	rm -rf $(DESTDIR)$(datadir)/icons/@PACKAGE@
	rm -rf $(DESTDIR)$(datadir)/@PACKAGE@
	rm -rf $(DESTDIR)$(datadir)/doc/@PACKAGE@
	rm -rf $(DESTDIR)$(datadir)/modulefiles/@PACKAGE_NAME@


install-data-local: doxygen-user-unpack
	@echo "Install version information "
	$(MKDIR_P) $(DESTDIR)$(datadir)/@PACKAGE@$(AM_TARGET)
	@$(INSTALL_DATA) src/cubelib-version.h  $(DESTDIR)$(includedir)/@PACKAGE@/cubelib-version.h
	@$(INSTALL_DATA) @PACKAGE@.summary $(DESTDIR)$(datadir)/@PACKAGE@$(AM_TARGET)/@PACKAGE@.summary
	@echo "=============================================================="
	$(MKDIR_P) $(DESTDIR)$(datadir)/doc/@PACKAGE@
	@echo "=============================================================="


 
if SVN_CONTROLLED

update-revision-file:
	@svnversion $(srcdir) > "$(srcdir)/build-config/REVISION"

else !SVN_CONTROLLED

update-revision-file:

endif !SVN_CONTROLLED




##--- Doxygen-related targets -----------------------------------------------

if SVN_CONTROLLED

## Documentation tarballs will not be generated in SVN mode,
## so there is nothing to unpack here...
doxygen-user-unpack:

else !SVN_CONTROLLED

htmldocpackdir	 = $(srcdir)/doc
doxygen-user-unpack:
	$(MKDIR_P) $(DESTDIR)$(docdir)
	for i in $(htmldocpackdir)/*-html.tar.gz; do \
		test ! -f $$i || tar xzvf $$i -C $(DESTDIR)$(docdir) || exit $$?; \
	done
	$(INSTALL_DATA) $(srcdir)/doc/*.pdf $(DESTDIR)$(docdir)

endif !SVN_CONTROLLED

















include doc/Makefile.top.inc.am
include doc/doxygen-common/Makefile.top.inc.am
include doc/doxygen-user/tools-dev/Makefile.top.inc.am
include doc/doxygen-user/tools-guide/Makefile.top.inc.am
include doc/doxygen-user/derived/Makefile.top.inc.am
include doc/doxygen-dev/cubelib/Makefile.top.inc.am

.PHONY: $(PHONY_TARGETS)
	
	
	
	
	
	
	
