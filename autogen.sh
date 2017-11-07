#!/bin/sh
#autogen.sh

mkdir -p 'm4' || exit 1
autoreconf --force --install || exit 1
printf 'autotools generated; now run:\n\t./configure\n\tmake\n\tmake install\n'
exit 0;
