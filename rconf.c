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

#include "rconf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char rconf_key[RCONF_STRING_LIMIT] = {'\0'};
char rconf_value[RCONF_STRING_LIMIT] = {'\0'};

int rconf_get(size_t *llen, FILE *fp) {
	int i = 0;
	int k = 0;
	int v = 0;
	int len = 0;
	int in_key = 1;
	char *line = NULL;

	memset(rconf_key, '\0', RCONF_STRING_LIMIT);
	memset(rconf_value, '\0', RCONF_STRING_LIMIT);

	if (getline(&line, llen, fp) < 0) {
		free(line);
		return -1;
	}

	len = strlen(line);

	switch (line[0]) {
	case '=':
	case '#':
		free(line);
		return 0;

	default:
		if (isspace(line[0])) {
			free(line);
			return 0;
		}
	}

	for (i = 0; i < len; i++) {
		char c = line[i];

		switch (c) {
		case '=':
			if (in_key == 1) {
				in_key = 0;
				break;
			}
		default:
			if (c != '\n') {
				if (isspace(c)) {
					/* if previous char was '=' then skip */
					if (i > 0 && line[i - 1] == '=') {
						break;
					}

					/* if next char is '=' then skip */
					if (i + 1 < len && line[i + 1] == '=') {
						break;
					}
				}

				if (in_key) {
					rconf_key[k++] = c;
				} else {
					rconf_value[v++] = c;
				}
			}

			break;
		}
	}

	free(line);

	return 0;
}
