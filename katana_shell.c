/*  
    -- CONFIDENTIAL - SOURCE MATERIALS --
                                                                                                                                                                                                        
    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE.
    
    -- CONFIDENTIAL - SOURCE MATERIALS --

 */

#include "katana_exploit.h"
#include "katana_shell.h"

char target_host[255];
char connect_back_ip[255];
int current_exploit = -1;

int is_int(char const* p)
{

	char buffer[10];
	snprintf(buffer, 10,"%d", atoi(p) );
    return strcmp(buffer, p) == 0;
}

void 
chomp(char *s) 
{
    while(*s && *s != '\n' && *s != '\r') s++;
 
    *s = 0;
}

int 
check_exploit_params()
{
	int error = 1;
	if (strlen(target_host) == 0) {
		printf("\n%s[!]%s target_host not set \n\n", _RED, _ENDC);
		error = 0;
	}

	if (strlen(connect_back_ip) == 0) {
		printf("%s[!]%s connect_back_ip not set \n\n", _RED, _ENDC);
		error = 0;
	}
	return error;
}

int 
parse_command(char *line)
{
	char *token;

	token = strtok (line, " ");
  
  	while (token != NULL) {

  		/* set */
    	if ( strcmp(token, "set") == 0) {

    		token = strtok(NULL, " ");

	  		if ( strcmp(token, "target_host") == 0) {
	  			token = strtok(NULL, " ");
	  			snprintf(target_host, 254, "%s", token);
	  			printf("\n%s[!]%s target_host set : %s\n\n", _GREEN, _ENDC, target_host);
			}

			if ( strcmp(token, "connect_back_ip") == 0) {
				token = strtok(NULL, " ");
	  			snprintf(connect_back_ip, 254, "%s", token);
	  			printf("\n%s[!]%s connect_back_ip set : %s\n\n", _GREEN, _ENDC, connect_back_ip);

			}
    	}

    	/* show */
    	if ( strcmp(token, "show") == 0) {

    		token = strtok(NULL, " ");

    		chomp(token);

	  		if ( strcmp(token, "exploits") == 0) {
	  			show_all_modules_by_type("EXPLOIT");
			}

    	}

    	/* use */
    	if ( strcmp(token, "use") == 0) {

    		token = strtok(NULL, " ");

	  		if ( strcmp(token, "exploit") == 0) {
	  			token = strtok(NULL, " ");

	  			chomp(token);

	  			if ( is_int(token) ) {
	  				
	  				if ( module_exists( atoi(token) ) ) {
	  					current_exploit = atoi(token);
	  					printf("\n%s[!]%s exploit ready\n\n", _GREEN, _ENDC);
	  				}

	  				else {
	  					printf("\n%s[!]%s could not find exploit\n\n", _RED, _ENDC);
	  				}

	  			}

	  			else {
	  				current_exploit = find_module_by_path(token);

		  			if (current_exploit >= 0 ) {
		  				printf("\n%s[!]%s exploit ready\n\n", _GREEN, _ENDC);
		  			}

		  			else {
		  				printf("\n%s[!]%s could not find exploit\n\n", _RED, _ENDC);
		  			}
	  			}

			}

    	}

    	/* use */
    	if ( strcmp(token, "exploit") == 0) {

    		if (current_exploit < 0 ) {
		  		printf("\n%s[!]%s no exploit set \n\n", _RED, _ENDC);
		  	}

		  	else {

		  		if ( check_exploit_params() ) {
		  			run_exploit();
		  		}

		  	}

    	}

    	token = strtok(NULL, " ");
  	}

}

void 
katana_shell(void)
{
	int exit = 0;
	char *user_input;

	while(!exit) {

		user_input = readline("#> ");
		add_history(user_input);
		parse_command(user_input);
		
	}
}
