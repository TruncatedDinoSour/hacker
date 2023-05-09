# hacker

> pretend as if ur a hacker

![screenshot](/media/ss.jpg)

# sources

-   arr.c -- converts files to c arrays
-   main.c -- main file

# arr

`arr` is a utility that converts files into c arrays, its only used for build time most likely, dont install it, its
useless for this besides build time, it takes files as input, for the build script the output will be cached to
`code.txt`, although ur free to just use it inline lol, i include the `code.txt` cache from my system if u want it to
just work, but for uniqueness and more diverse output id suggest to just use ur own

# compilation

run `./scripts/build.sh` or :

```sh
cc -o arr src/arr.c -Ofast -s  -std=c89
cc -o hacker -DCODE="$(./arr $(find /usr/include/ -type f -name '*.c*' -or -name '*.h*' | head -n 500))" src/main.c -Ofast -s -std=c89
#                            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ u can play around with this
```

## build script config

env vars :

-   `CC` -- c compiler ( default : `cc` )
-   `CFLAGS` -- c compiler flags ( default : `-Ofast -s -std=c89` )
-   `SRC` -- folder to look for code ( default : `/usr/include` )
-   `SRCC` -- how many files to find in `SRC` ( default : `500` )

## `hacker` configuration

macro definitions ( `-DMACRO` ( e.g. `-DSCAN_COUNT=1` ) :

-   `CODE` -- c array, should be an array of characters or integers of ASCII values ( see `arr.c` ) ( default : `{0}` )
-   `SCAN_COUNT` -- how many characters of code should one keystroke equal to ( default : `6` )
-   `CODE_CLR` -- ansi colour your code is ( default : `\033[32m` ( green ) )

# usage

launch the program, type anything and to exit just press CTRL + C
