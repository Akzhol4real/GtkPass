ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

SUBDIRS = src data po

INTLTOOL_FILES = \
  intltool-extract.in \
  intltool-merge.in \
  intltool-update.in

dist_doc_DATA = \
  README.md \
  LICENSE

EXTRA_DIST = \
  $(INTLTOOL_FILES)

DISTCLEANFILES = \
  intltool-extract \
  intltool-merge \
  intltool-update \
  po/.intltool-merge-cache

uninstall-local: ; rm -r $(docdir)
