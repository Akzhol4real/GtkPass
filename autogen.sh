#!/bin/sh
# Generates all the initial Makefiles, etc.

topsrcdir=`dirname $0`
if test x$topsrcdir = x; then
    topsrcdir=.
fi

(test -f $topsrcdir/configure.ac) || {
    echo -n "*** ERROR: Directory \"$topsrcdir\" does not seem to be the"
    echo -n "top-level directory of the project! ***"
    exit 1
}

autoreconf --verbose --force --install . || exit 1
