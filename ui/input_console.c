#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#include "input_console.h"

#ifndef USE_READLINE
#define LINE_BUF_SIZE 128

static char *readline(const char *prompt)
{
	char *buf = malloc(LINE_BUF_SIZE);

	if (!buf) {
		fprintf(stdout, "readline: can't allocate memory: %s\n",
			last_error());
		return NULL;
	}

	for (;;) {
		printf("%s", prompt);
		fflush(stdout);

		if (fgets(buf, LINE_BUF_SIZE, stdin)) {
			int len = strlen(buf);

			while (len > 0 && isspace(buf[len - 1]))
				len--;

			buf[len] = 0;
			return buf;
		}

		if (feof(stdin))
			break;

		printf("\n");
	}

	free(buf);
	return NULL;
}

#define add_history(x)
#endif

static int console_init(void)
{
	return 0;
}

static void console_exit(void) { }

static int console_read_command(char *out, int max_len)
{
	char *buf = readline("(input-module) ");

	if (!buf) {
		printf("\n");
		return 1;
	}

	if (*buf)
		add_history(buf);

	strncpy(out, buf, max_len);
	out[max_len - 1] = 0;
	free(buf);

	return 0;
}

static int console_prompt_abort(const char *message)
{
	char buf[32];

	for (;;) {
		printf("%s ", message);
		fflush(stdout);

		if (!fgets(buf, sizeof(buf), stdin)) {
			printf("\n");
			return 1;
		}

		if (toupper(buf[0]) == 'Y')
			return 0;
		if (toupper(buf[0]) == 'N')
			return 1;

		printf("Please answer \"y\" or \"n\".\n");
	}

	return 0;
}

const struct input_interface input_console = {
	.init		= console_init,
	.exit		= console_exit,
	.read_command	= console_read_command,
	.prompt_abort	= console_prompt_abort
};
