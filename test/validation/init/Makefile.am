include ../Makefile.inc
noinst_LTLIBRARIES = libinit.la
libinit_la_SOURCES = init.c

# most platforms are expected not to support multiple ODP inits
# following each other: therefore 3 separate binaries are
# created, each containing its ODP init test.
bin_PROGRAMS = init_main_abort$(EXEEXT) init_main_log$(EXEEXT) init_main_ok$(EXEEXT)
dist_init_main_abort_SOURCES = init_main_abort.c
dist_init_main_log_SOURCES   = init_main_log.c
dist_init_main_ok_SOURCES    = init_main_ok.c
init_main_abort_LDADD = libinit.la $(LIBCUNIT_COMMON) $(LIBODP)
init_main_log_LDADD   = libinit.la $(LIBCUNIT_COMMON) $(LIBODP)
init_main_ok_LDADD    = libinit.la $(LIBCUNIT_COMMON) $(LIBODP)

EXTRA_DIST = init.h
