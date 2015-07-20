include ../Makefile.inc

noinst_LIBRARIES = libtraffic_mngr.a
libtraffic_mngr_a_SOURCES = traffic_mngr.c

bin_PROGRAMS = traffic_mngr_main$(EXEEXT)
dist_traffic_mngr_main_SOURCES = traffic_mngr_main.c
traffic_mngr_main_LDADD = libtraffic_mngr.a $(LIBCUNIT_COMMON) $(LIBODP)
