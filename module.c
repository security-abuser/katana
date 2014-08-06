/*  
    -- CONFIDENTIAL - SOURCE MATERIALS --
                                                                                                                                                                                                        
    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE.
    
    -- CONFIDENTIAL - SOURCE MATERIALS --

 */

#include "module.h"
#include "./modules/core/common.h"

int loaded_module_count = 0;
struct module *modules;

void 
init_modules(void)
{

    int exploit_count = count_modules("./modules/exploits");

    modules = malloc(exploit_count * sizeof(struct module));

    load_all_modules();

}

int 
module_exists(int module_index)
{

    if(module_index >= loaded_module_count) {
        return 0;
    }

    return strlen(modules[module_index].path);

}

void
show_all_modules_by_type(char *type)
{
    int i;

    for(i = 0; i < loaded_module_count; i++){ 
        if ( strcmp(modules[i].type, type) == 0) {
            printf("\t %d - %s %s-%s %s\n", i, modules[i].name, _GREEN, _ENDC, modules[i].path);
        }
    }

}

int 
find_module_by_path(char *path)
{
    int i;

    for(i = 0; i < loaded_module_count; i++){
        if ( strcmp(modules[i].path, path) == 0) {
            return i;
        }
    }

    return -1;
}

int 
load_module(char *module_path)
{
    const char * error = 0;
    struct module *module_info;

    modules[loaded_module_count].module_handle = dlopen(module_path, RTLD_LAZY);

    if (!modules[loaded_module_count].module_handle) {
        return -1;
    }

    modules[loaded_module_count].info = dlsym(modules[loaded_module_count].module_handle, "info");
    modules[loaded_module_count].help = dlsym(modules[loaded_module_count].module_handle, "help");
    modules[loaded_module_count].exploit = dlsym(modules[loaded_module_count].module_handle, "exploit");
    modules[loaded_module_count].check_exploit = dlsym(modules[loaded_module_count].module_handle, "check_exploit");


    if ((error = dlerror()) != 0) {
        return -1;
    }

    module_info = modules[loaded_module_count].info();

    modules[loaded_module_count].name = module_info->name;
    modules[loaded_module_count].type = module_info->type;
    modules[loaded_module_count].sub_type = module_info->sub_type;

    char *path = malloc(strlen(module_path)+2);
    snprintf(path, strlen(module_path)+1, "%s", module_path);

    modules[loaded_module_count].path = path;
 
    return 1;
}

int 
load_all_modules(void)
{
    DIR *dir;
    struct dirent *ent;
    char module_path[256];

    if ((dir = opendir ("./modules/exploits")) != NULL) {
      while ((ent = readdir (dir)) != NULL) {
        char *ext = strrchr(ent->d_name, '.');
        if (ext && !strcmp(ext, ".so") ) {
            snprintf(module_path, 255, "./modules/exploits/%s", ent->d_name);
            if( load_module(module_path) ) {
                loaded_module_count++;
            }
        }
      }
      closedir (dir);
    }
    
    return 1;
}

int 
count_modules(char *path)
{
    DIR *dir;
    struct dirent *ent;
    char module_path[256];
    int count = 0;

    if ((dir = opendir (path)) != NULL) {
      while ((ent = readdir (dir)) != NULL) {
        char *ext = strrchr(ent->d_name, '.');
        if (ext && !strcmp(ext, ".so") ) {
            count++;
        }
      }
      closedir (dir);
    }
    
    return count;
}
