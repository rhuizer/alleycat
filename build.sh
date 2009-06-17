#!/bin/sh

# Update timestamp to make sure autoconf rebuilds everything.
touch configure.ac

aclocal
libtoolize --force --copy
autoheader
automake --add-missing --copy --gnu
autoconf
