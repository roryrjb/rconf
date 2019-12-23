/* rconf - Copyright (C) 2019 Rory Bradford <roryrjb@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "rconf.h"

extern char *__progname;

void usage(void)
{
	fprintf(stderr, "Usage: %s [-k key]\n", __progname);
}

int main(int argc, char **argv)
{
	char opt;
	char *filename;
	char *key = NULL;
	FILE *fp;
	size_t len = 0;
	int rconf = 0;

	while ((opt = getopt(argc, argv, "k:v")) != -1) {
		switch (opt) {
		case 'k':
			key = optarg;
			break;
		case 'h':
		default:
			usage();
			exit(EXIT_FAILURE);
		}
	}

	if (optind < argc) {
		filename = argv[optind];
	} else {
		fprintf(stderr, "Error: no file specified.\n");
		usage();
		exit(EXIT_FAILURE);
	}

	fp = fopen(filename, "r");

	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((rconf = rconf_get(&len, fp)) != -1) {
		if (key != NULL) {
			if (strlen(rconf_key) && strlen(rconf_value) &&
			    strcmp(key, rconf_key) == 0) {
				printf("%s\n", rconf_value);
			}
		} else {
			if (strlen(rconf_key) && strlen(rconf_value)) {
				printf("%s = %s\n", rconf_key, rconf_value);
			} else if (strlen(rconf_key)) {
				printf("%s\n", rconf_key);
			}
		}
	}

	fclose(fp);

	exit(EXIT_SUCCESS);
}
