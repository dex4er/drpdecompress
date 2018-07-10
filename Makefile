BINDIR = /usr/local/bin
CC = cc
CFLAGS = -Wall -g -O2
EXTRA_CFLAGS =
INSTALL = install
RM = rm

all: drpdecompress

install: all
	$(INSTALL) drpdecompress $(BINDIR)

uninstall:
	-$(RM) -f $(BINDIR)/drpdecompress

clean:
	-$(RM) -f *.o drpdecompress

drpdecompress: drpdecompress.o
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o drpdecompress drpdecompress.o -lucl

drpdecompress.o: drpdecompress.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c -Iinclude -I. drpdecompress.c
