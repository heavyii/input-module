#include "input.h"
#include "input_console.h"

/* Default input module */
const struct input_interface *input_module = &input_console;
