#include <stdio.h>
#include <dlfcn.h>
#include <stdbool.h>

#define NOEXPORT __attribute__((visibility ("hidden")))

extern int *foo;

/**
 * Function pointer to the symbol importer in the core. This function returns a
 * pointer to the requested symbol/interface. It's automatically initialized
 * upon plugin load.
 */
void *(*import_symbol) (void);

/**
 * Function that the core will call after the plugin is loaded (this is to
 * automate symbol import into the plugin). Relies on import_symbol being
 * already set.
 */
bool HPM_shared_symbols(int server_type)
{
	foo = (int *)import_symbol();
	return foo ? true : false;
}
