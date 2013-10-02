#ifndef READER_H_
#define READER_H_

/* This should be called before a destructive operation to give the user
 * a chance to abort. If it returns 1, then the operation should be aborted.
 *
 * The flags argument should be a bitwise combination representing the bits
 * modify_flags that will be affected by the operation.
 */
int prompt_abort(int flags);

/* Run the reader loop
 * @abort_flag: 0 not abort message, none zero abort message
 */
void reader_loop(int abort_flag);

/* Cause the reader loop to exit */
void reader_exit(void);

/* Set up the command to be repeated. When the user presses enter without
 * typing anything, the last executed command is repeated, by default.
 *
 * Using this function, a command can specify an alternate command for
 * the next execution.
 */
void reader_set_repeat(const char *fmt, ...);

#endif
