#include"customshell.h"
/**
 * info_init - Initializes a struct of type info_t
 *
 * @struct_address: Pointer to the address of a struct of type info_t
 */
void info_init(info_t *struct_address)
{
	struct_address->arg = NULL;
	struct_address->argv = NULL;
	struct_address->path = NULL;
	struct_address->argc = 0;
}
