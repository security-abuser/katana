/*  
    -- CONFIDENTIAL - SOURCE MATERIALS --
                                                                                                                                                                                                        
    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE.
    
    -- CONFIDENTIAL - SOURCE MATERIALS --

 */


#include "modules/core/common.h"
#include <readline/readline.h>
#include <readline/history.h>

extern char target_host[255];
extern char connect_back_ip[255];
extern int current_exploit;

void katana_shell(void);
int check_exploit_params();