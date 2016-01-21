.PHONY: build clean

# directories
ifeq ($(realpath .),)
  $(error your version of Make doesn't support $$(realpath names...) - please use GNU Make 3.81 or later)
endif

ifeq ($(platform),)
  __uname_s := $(shell sh -c 'uname -s 2>/dev/null | tr [A-Z] [a-z] || echo unknown-platform')
  __uname_m := $(shell sh -c 'uname -m 2>/dev/null | tr [A-Z] [a-z] || echo unknown-architecture')

  ifeq ($(__uname_s),linux)
    override platform := linux
    override architecture := $(__uname_m)
  endif
  ifeq ($(__uname_s),darwin)
    override platform := mac
    override architecture := $(__uname_m)
  endif
endif
ifeq ($(architecture),)
  override architecture := unknown-architecture
endif

prefix := $(realpath ..)
srcdir := $(realpath ../src)
exampledir := $(realpath ../example)
testdir := $(realpath ../test)
buildir := $(realpath .)/build
binsubdir := $(platform)-$(architecture)
bindir := $(prefix)/bin/$(binsubdir)

CFLAGS := -O2 -g -Wall -Werror

ifeq ($(platform),linux)
override LDFLAGS := $(LDFLAGS) -ldl -lstdc++
endif

ifeq ($(platform),mac)
libsuffix := .dylib
else
libsuffix := .so
endif

.PHONY: build-executable
build: build-executable
build-executable: $(bindir)/executable $(bindir)/executable-cpp

$(bindir)/executable: $(srcdir)/whereami.c $(srcdir)/whereami.h $(exampledir)/executable.c
	mkdir -p $(@D)
	$(CC) -o $@ -I $(srcdir) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -fpic $(filter-out %.h,$^)
	$(if $(postbuild),$(postbuild) $@)

$(bindir)/executable-cpp: $(srcdir)/whereami.c $(srcdir)/whereami.h $(exampledir)/executable.c
	mkdir -p $(@D)
	$(CC) -x c++ -o $@ -I $(srcdir) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -fpic $(filter-out %.h,$^)
	$(if $(postbuild),$(postbuild) $@)

.PHONY: build-library
build: build-library
build-library: $(bindir)/library$(libsuffix) $(bindir)/library-cpp$(libsuffix)

$(bindir)/library$(libsuffix): $(srcdir)/whereami.c $(srcdir)/whereami.h $(exampledir)/library.c
	mkdir -p $(@D)
	$(CC) -shared -o $@ -I $(srcdir) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -fpic $(filter-out %.h,$^)
	$(if $(postbuild),$(postbuild) $@)

$(bindir)/library-cpp$(libsuffix): $(srcdir)/whereami.c $(srcdir)/whereami.h $(exampledir)/library.c
	mkdir -p $(@D)
	$(CC) -x c++ -shared -o $@ -I $(srcdir) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -fpic $(filter-out %.h,$^)
	$(if $(postbuild),$(postbuild) $@)

clean:
	rm -rf $(buildir)
	rm -rf $(bindir)
