#!/usr/bin/env bash

set -xe

main() {
    CC="${CC:-cc}"
    CFLAGS="${CFLAGS:--Ofast -s -std=c89}"
    SRC="${SRC:-/usr/include/}"
    SRCC="${SRCC:-500}"

    if [ -f code.txt ]; then
        read -rd '' code <code.txt || :
    else
        $CC -o arr $CFLAGS src/arr.c
        code="$(./arr $(find "$SRC" -type f -name '*.c*' -or -name '*.h*' | head -n "$SRCC"))"
        echo "$code" >code.txt
    fi

    $CC -o hacker $CFLAGS src/main.c -DCODE="$code"

    [ "$1" = '-r' ] && ./hacker || :
}

main "$@"
