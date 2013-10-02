#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include "reader.h"
#include "input.h"

#define MAX_READER_LINE		1024

static char repeat_buf[MAX_READER_LINE];
static volatile int want_exit = 0;

int prompt_abort(int flags)
{
	if (!flags)
		return 0;

	return input_module->prompt_abort("Do you really want to exit (y/n)?");
}

static int do_command(char *arg, int interactive)
{
	if (!strcasecmp(arg, "exit"))
		reader_exit();

	printf("%s:%d: (%s) %d\n", __FUNCTION__, __LINE__, arg, interactive);

	return 0;
}

void reader_set_repeat(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(repeat_buf, sizeof(repeat_buf), fmt, ap);
	va_end(ap);
}

void reader_exit(void)
{
	want_exit = 1;
}

void reader_loop(int abort_flag)
{
	do {
		want_exit = 0;

		for (;;) {
			char tmpbuf[MAX_READER_LINE] = { 0 };
			char *buf = tmpbuf;

			if (input_module->read_command(tmpbuf, sizeof(tmpbuf)))
				break;

			//set repeat
			if (*buf) {
				memcpy(repeat_buf, tmpbuf, sizeof(tmpbuf));
			} else
				memcpy(tmpbuf, repeat_buf, sizeof(tmpbuf));

			do_command(buf, 1);

			if (want_exit)
				break;
		}
	} while (prompt_abort(abort_flag));
}
