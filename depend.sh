#!/bin/sh
DIR="$1"
shift 1
case "$DIR" in
"" | ".")
gcc -Iinclude -MM -MG "$@" |
sed -e ’s@^\(.*\)\.o:@\1.d \1.o:@’
;;
*)
gcc -Iinclude -MM -MG "$@" |
sed -e "s@^\(.*\)\.o:@$DIR/\1.d \
$DIR/\1.o:@"
;;
esac
