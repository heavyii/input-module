#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "input.h"
#include "reader.h"

static const char *version_text =
"input-module ("__DATE__ "-" __TIME__")- an example shows you how to use input module with readline\n"
"Copyright (C) 2012-2013 ruisheng <ruishengleen@gmail.com>\n"
"This is free software; see the source for copying conditions.  There is NO\n"
"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR "
"PURPOSE.\n";

static int process_loop(void) {
	reader_loop(1);
	return 0;
}

int main(int argc, char *argv[]) {
	int ret = 0;
	puts(version_text);

	if (input_module->init() < 0)
		return EXIT_FAILURE;

	ret = process_loop();

	input_module->exit();

	return ret ? EXIT_FAILURE : EXIT_SUCCESS;
}
