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

#ifndef RCONF_H
#define RCONF_H

#include <ctype.h>
#include <stdio.h>

#define RCONF_STRING_LIMIT 1024

extern char rconf_key[RCONF_STRING_LIMIT];
extern char rconf_value[RCONF_STRING_LIMIT];

int rconf_get(size_t *len, FILE *fp);

#endif
