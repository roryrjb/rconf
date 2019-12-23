#include <stdio.h>
#include <stdlib.h>

#include "rconf.h"

int main(void) {
	FILE *fp;
	size_t len = 0;
	int rconf = 0;

	fp = fopen("./example.conf", "r");

	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((rconf = rconf_get(&len, fp)) != -1) {
		printf("[%s] -> [%s]\n", rconf_key, rconf_value);
	}

	fclose(fp);

	exit(EXIT_SUCCESS);
}
