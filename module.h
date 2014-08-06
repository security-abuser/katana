/* 	
	-- CONFIDENTIAL - SOURCE MATERIALS --
                                                                                                                                                                                                        
 	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE.
	
	-- CONFIDENTIAL - SOURCE MATERIALS --

 */

#include <dlfcn.h>
#include "./modules/core/exploit.h"

extern int loaded_module_count;
extern struct module *modules;

void init_modules(void);
int load_module(char *module_path);
int load_all_modules(void);
int count_modules(char *path);
int find_module_by_path(char *path);
void show_all_modules_by_type(char *type);
int module_exists(int module_index);

struct module
{
	char *name;
	char *path;
	char *type;
	char *sub_type;
	void *module_handle;
    void (*help)(void);
    struct module * (*info)(void);
    void (*check_exploit)(struct exploit_params *p);
    void (*exploit)(struct exploit_params *p);
};
