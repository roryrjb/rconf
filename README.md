# rconf

> A simple config file library

## About

rconf is a very simple config file parsing library and command line program
suitable for scripting.

It is similar to the `.ini` file format in that there are multiple key value
pairs, but all pairs exist in the same namespace. The format and
implementation is designed to be as simple as possible. Pairs are parsed
line by line in a similar way to `getopt`.

## Installation

rconf should be able to be built on any modern UNIX or UNIX-like system,
if you find this is not the case then please either file a bug or send a patch.

    $ make install

## Usage

In C:

    #include <rconf.h>

    int main(void)
    {
        FILE *fp;
        size_t len = 0;
        int rconf = 0;

        fp = fopen("my.conf", "r");

        while ((rconf = rconf_get(&len, fp)) != -1) {
            printf("%s - %s\n", rconf_key, rconf_value);
        }

        return 0;
    }

Using `rconf(1)`:

    $ echo "hello = world" | rconf -k hello -
    world
    $ rconf my.conf
    here = are
    some = examples

See the included man pages for more information and examples.