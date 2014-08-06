/* 	
	-- CONFIDENTIAL - SOURCE MATERIALS --
                                                                                                                                                                                                        
 	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE.
	
	-- CONFIDENTIAL - SOURCE MATERIALS --

 */

#include "socket.h"


void 
snd(int s, char *req, int size)
{
	if (send(s, req, size, 0) < 0)
  		printf("[!] error sending");
}

void 
rcv(int s)
{
	char r[999];
	recv(s, r, 999, 0);
}

int 
con(char *h)
{
	struct hostent *server;
  	struct sockaddr_in serveraddr;
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
	    printf("[!] error opening socket\n");
	}
	server = gethostbyname(h);
	if (server == NULL) {
	    printf("[!] gethostbyname() failed\n");
	}
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
	serveraddr.sin_port = htons(80);
	if (connect(s, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
		printf("[!] error connecting\n");
	}

	return s;
}