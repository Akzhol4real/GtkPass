SUBDIRS = icons

desktopdir = $(datadir)/applications
desktop_in_files = gtkpass.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

$(desktop_DATA): $(desktop_in_files)
	$(AM_V_GEN) $(MSGFMT) --desktop --template $< -d $(top_srcdir)/po -o $@

dist_noinst_DATA = \
	appMenu.ui \
	window.ui

EXTRA_DIST = \
	$(desktop_in_files) \
  gtkpass.gresource.xml

CLEANFILES = \
	$(desktop_DATA)
