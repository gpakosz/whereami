# These might be a good idea
.POSIX:
AM_CFLAGS = -std=c99 -pedantic -D_POSIX_C_SOURCE=200809L -Wall -Wextra
AM_LDFLAGS = 

# This might be how to add CPP stuff
# AM_CPPFLAGS =  -pedantic -Wall -Wextra
# AM_CPPFLAGS+= -std=c++11

# This might be how to link against things:
AM_CFLAGS += -ldl
# AM_LDFLAGS += -lsome_library

# === Programs ===

bin_PROGRAMS = whereami_runner
whereami_runner_SOURCES = \
	whereami.c \
	main.c

# Needed, as per:
# https://www.gnu.org/software/automake/manual/html_node/Objects-created-both-with-libtool-and-without.html

whereami_runner_CFLAGS = $(AM_CFLAGS)

# === End Programs ===

# === Libraries ===
# Libraries that are generated and to be installed by this:

lib_LTLIBRARIES = libwhereami.la

libwhereami_la_SOURCES = \
	whereami.c \
	whereami.h

include_HEADERS = whereami.h

libwhereami_la_LDFLAGS = -version-info 0:0:0

# === End Libraries ===
