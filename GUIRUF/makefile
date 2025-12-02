PREFIX ?= /usr/local
LIBDIR ?= $(PREFIX)/lib
INCDIR ?= $(PREFIX)/include
PKGDIR ?= $(LIBDIR)/pkgconfig

SRCS = src/guiruf.cxx
HDRDIR = include/GUIRUF/
LIBNAME = GUIRUF

VERSION = 1.0.2
SOVERSION = 1

LIB_SO = lib$(LIBNAME).so.$(VERSION)
LIB_SONAME = lib$(LIBNAME).so.$(SOVERSION)
LIB_SO_SHORT = lib$(LIBNAME).so
PCFILE = ${PKGDIR}/${LIBNAME}.pc

CXX = g++
CFLAGS = -Wall -fPIC -Iinclude
LDFLAGS = -lX11 -lXext 

.PHONY: all clean install uninstall

all: $(LIB_SO)

$(LIB_SO): $(SRCS)
	$(CXX) $(CFLAGS) -I $(HDRDIR) -c $< -o $(basename $<).o
	$(CXX) -shared -o $(LIB_SO) $(basename $<).o $(CFLAGS) $(LDFLAGS) -Wl,-soname,$(LIB_SONAME)

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
	find ./ -name "*.o" -type f -delete

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
	echo "Libs: -L$${libdir} -lGUIRUF -lX11" >> $(PCFILE)
	echo "Cflags: -I$${includedir}" >> $(PCFILE)