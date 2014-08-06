/*  
    -- CONFIDENTIAL - SOURCE MATERIALS --
                                                                                                                                                                                                        
    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE.
    
    -- CONFIDENTIAL - SOURCE MATERIALS --

 */


#include <stdio.h>
#include <stdlib.h>
#include "module.h"
#include "katana_shell.h"
#include "modules/core/exploit.h"


void
banner(void)
{
	char str[20096];
	FILE * file;

	memset(str, 0, sizeof(str));

	file = fopen( "banner.txt" , "r");

	if (file) {
    	fread(str, sizeof(str), 1, file);
    	fclose(file);
	}

	printf("%s%s%s\n\n", _GREEN, str, _ENDC);

}

int 
main(int argc, char **argv)
{

	system("clear");
	banner();
    init_modules();
    printf("%s[+]%s Loaded %d exploit modules\n\n", _GREEN, _ENDC, loaded_module_count);
    katana_shell();

}
