sbin_PROGRAMS=lms
dist_bin_SCRIPTS=notifyDesktop.sh
xml_dir=$(datadir)/xml
xml__DATA=AMTAlerts.xml

SYNCLIB_SRCDIR=SyncLib/src
SYNCLIB_HDRDIR=SyncLib/Include
MEI_DIR=mei
TOOLS_DIR=tools

INCLUDES=-I$(srcdir) -I$(srcdir)/$(SYNCLIB_HDRDIR) -I$(srcdir)/$(MEI_DIR) -I$(srcdir)/$(TOOLS_DIR)

include Makefile.inc

lms_SOURCES=$(SRCS) $(HDRS)

install-data-hook:
	mkdir -p $(DESTDIR)$(prefix)/share

