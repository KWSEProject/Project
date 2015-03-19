//////////////////////////////////////////////////////////////////////////////////////////
//File name : srv.c			   						//
//Date	    : 2014/06/05                                               			//
//Os	    : Ubuntu 12.04 LTS 64bits 							//
//Author    : Hwang JIn Yong 								//
//Student ID: 2010720139 								//
//---------------------------------------------------------------------			//
//Title : Basic Web SErver								//
//Description : Making a HTML server to connect						//
//              Via Mozilla FierFox, shows the result.		 			//
//		End of COnnect, client send server the request			 	//
//              Then, SErver send the response to the client			        //	
//////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define BUF_SIZE 4000

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Use like this : ""./srv PORTNO""\n");
		exit(0);
	}
        char *ch;
	FILE * fp = fopen("test.html", "r");
        ch = fgetc(fp);
	char buff[BUF_SIZE]; // client message
	char rspn[BUF_SIZE]; // response header      
	char html[BUF_SIZE]; // test.html

	memset(buff, 0, BUF_SIZE); // initialize buff
	memset(html, 0, BUF_SIZE); // initialize html
	memset(rspn, 0, BUF_SIZE); // initialize rspn

        /* print the response header */
	strcpy(rspn, "HTTP/1.1 200 OK \nDate: Sat, 20-May-95 03:25:12 GMT \n");
	strcat(rspn, "Server:Apache/1.3.19 (Unix) PHP/4.0.6\nMIME-version: 1.0\n");
	strcat(rspn, "Content-type: text/html\nLast-modified: Wed, 14-Mar-95 18:15:23 GMT\n");
	strcat(rspn, "Content-length: 1029 \n\n");

	//strcpy(html, ch);
        /* write the main html code */
	strcpy(html, "<HTML><HEAD><TITLE> System Programming Assignment </TITLE>");
	strcat(html, "</HEAD><BODY>");
	strcat(html, "<TABLE BORDER COLOR = WHITE>");
	strcat(html, "<TR><TH>Student name</TH> <TD>Hwang JIn YOng</TD> </TR>");
	strcat(html, "<TR><TH>Student number</TH> <TD>2010720139</TD> </TR>");
	strcat(html, "</TABLE>");
	strcat(html, "<P>");
	strcat(html, "<I><B>Thank you Professor!!</B></I><BR><BR>");
	strcat(html, "I was afraid of C Programming.<BR>But you raise me up<BR>Cause of your teaching<BR>");
	strcat(html, "So I'm very fond of you and proud of you<BR>that I met you<BR>And the rest<BR>");
	strcat(html, "Assistants,<BR>for one cemetery,<BR>I really appreciate<BR>");
	strcat(html, "for the rest of the year,<BR>Please <BR>be happy and nice of you<BR>");
	strcat(html, "THank you<BR>THis is the<BR>End of Assignment<BR>");
	strcat(html, "</BODY></HTML>");

	struct sockaddr_in server_addr, client_addr; 
	int server_fd, client_fd;		     
	int len;				     
	int port;                                   

        /* make a socket */
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf(stderr, "socket error\n");
		exit(1);
	}
	port = atoi(argv[1]); // receive portno from user
	memset(&server_addr, 0, sizeof(server_addr)); // initialize server_addr
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(port);

	//bind
	if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))< 0)
	{
		fprintf(stderr, "bind error\n");
		exit(1);
	}
	
	//listen
	if(listen(server_fd, 5)<0)
	{
		fprintf(stderr, "listen error\n");
		exit(1);
	}

	while(1)
	{
		len = sizeof(client_addr);
		pid_t pid;

		//accept
		if((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len)) < 0)
		{
			fprintf(stderr, "accpet fail\n");
			exit(1);
		}
		
		//child process
		if(!(pid = fork())) 
		{
			if(read(client_fd, buff, BUF_SIZE)<0)
			{
				fprintf(stderr, "read fail\n");
				close(client_fd);
				exit(1);
			}
			if(write(STDOUT_FILENO, buff, BUF_SIZE)<0)
			{
				fprintf(stderr, "write HTTP requset Header fail\n");
				close(client_fd);
				exit(1);
			}
			if(write(client_fd, rspn, strlen(rspn))<0)
			{
				fprintf(stderr, "write HTTP Response Header fail\n");
				close(client_fd);
				exit(1);
			}
			if(write(client_fd, html, strlen(html))<0)
			{
				fprintf(stderr, "write test.html fail\n");
				close(client_fd);
				exit(1);
			}
		}
	
		//parent process
		else 
		{
			close(client_fd);
		}
		close(client_fd);	
	}
	
	return 0;
}

