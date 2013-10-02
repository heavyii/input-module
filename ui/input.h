#ifndef INPUT_H_
#define INPUT_H_

/* This defines the interface to an input module. The input module is
 * responsible for providing a way of fetching commands to be executed,
 * and a way of presenting yes/no questions to the user ("are you sure
 * you want to ...?").
 */
struct input_interface {
	/* Initialize/tear down the input subsystem. */
	int	(*init)(void);
	void	(*exit)(void);

	/* Read a command from the user into the supplied buffer. This
	 * function returns 0 on success, -1 if an error occurs, and 1
	 * if the end of input has been reached.
	 */
	int	(*read_command)(char *buf, int max_len);

	/* Prompt the user before performing a destructive operation.
	 * The question should be phrased so that "yes" confirms that
	 * the operation should proceed.
	 *
	 * Returns 1 for no (abort), 0 for yes (continue), and -1 if an
	 * error occurs.
	 */
	int	(*prompt_abort)(const char *message);
};

/* Variable which holds a reference to the selected input module. */
extern const struct input_interface *input_module;

#endif
