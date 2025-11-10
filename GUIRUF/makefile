PREFIX ?= /usr/local
LIBDIR ?= $(PREFIX)/lib
INCDIR ?= $(PREFIX)/include
PKGDIR ?= $(LIBDIR)/pkgconfig

SRCS = src/guiruf.cxx
HDRDIR = include/GUIRUF/
LIBNAME = GUIRUF

VERSION = 1.0.0
SOVERSION = 1

LIB_SO = lib$(LIBNAME).so.$(VERSION)
LIB_SONAME = lib$(LIBNAME).so.$(SOVERSION)
LIB_SO_SHORT = lib$(LIBNAME).so
PCFILE = ${PKGDIR}/${LIBNAME}.pc

CXX = g++
CFLAGS = -Wall -fPIC -Iinclude
LDFLAGS = -shared -lX11

.PHONY: all clean install uninstall

all: $(LIB_SO)

$(LIB_SO): $(SRCS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -I ${HDRDIR} -Wl,-soname,$(LIB_SONAME) -o $@ $^

install: all ${PCFILE}
	mkdir -p $(LIBDIR)
	mkdir -p $(INCDIR)
	cp $(LIB_SO) $(LIBDIR)/
	ln -sf $(LIB_SO) $(LIBDIR)/$(LIB_SONAME)
	ln -sf $(LIB_SONAME) $(LIBDIR)/$(LIB_SO_SHORT)
	cp -r $(HDRDIR) $(INCDIR)/
	ldconfig

uninstall:
	rm -f $(LIBDIR)/$(LIB_SO) $(LIBDIR)/$(LIB_SONAME) $(LIBDIR)/$(LIB_SO_SHORT)
	rm -rf $(INCDIR)/GUIRUF
	rm -f $(PCFILE)
	ldconfig

clean:
	rm -f $(LIB_SO) $(LIB_SONAME) $(LIB_SO_SHORT) *.o

PKGDIR = $(LIBDIR)/pkgconfig
PCFILE = $(PKGDIR)/GUIRUF.pc

$(PCFILE):
	mkdir -p $(PKGDIR)
	echo "prefix=$(PREFIX)" > $(PCFILE)
	echo "exec_prefix=$${prefix}" >> $(PCFILE)
	echo "libdir=$${exec_prefix}/lib" >> $(PCFILE)
	echo "includedir=$${prefix}/include" >> $(PCFILE)
	echo "" >> $(PCFILE)
	echo "Name: GUIRUF" >> $(PCFILE)
	echo "Description: Minimal X11 GUI Wrapper" >> $(PCFILE)
	echo "Version: $(VERSION)" >> $(PCFILE)
	echo "Libs: -L$${libdir} -lGUIRUF" >> $(PCFILE)
	echo "Cflags: -I$${includedir}" >> $(PCFILE)