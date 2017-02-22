ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

SUBDIRS = src data po
DIST_SUBDIRS = src data po

dist_doc_DATA = \
  README.md \
  LICENSE \
  ChangeLog

DISTCLEANFILES = \
  intltool-extract \
  intltool-merge \
  intltool-update \
  po/.intltool-merge-cache

uninstall-local: ; rm -r $(docdir)
