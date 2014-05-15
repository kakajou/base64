/*
#ifdef WIN32 
	
	#include <cstdlib>
	#include <iostream>
	#include <winsock2.h>
	#include <stdlib.h>

#elif defined (linux) 
*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h> 
	#include <netdb.h> 

	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
	typedef struct in_addr IN_ADDR;	

	#define closesocket(s) close(s)	
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1

	#define Host "127.0.0.1"
	#define Port 80
/*
#else 
	#error not defined for this platform
#endif
*/

static void init(void)
{ 
#ifdef WIN32
	WSADATA wsa;
	int err = WSAStartup(MAKEWORD(2, 2), &wsa);
	if(err < 0)
	{
	puts("WSAStartup failed !");
	exit(EXIT_FAILURE);
	}
#endif
}

static void end(void)
{ 
#ifdef WIN32
	WSACleanup();
#endif
}	



int main(int argc, char *argv[])
{

    FILE* file;

    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer [1024] = ""; 
    char file_buffer [1024] = ""; 
    
    sin.sin_addr.s_addr = inet_addr(Host);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(Port);

    
    
    init();

	file = fopen("Unix.xml","r+");

    //if ( file == INVALID_SOCKET ) { perror("fopen ()"); exit(0); }

    sock =  socket(  AF_INET , SOCK_STREAM , IPPROTO_TCP );
    if ( sock == INVALID_SOCKET ) { perror("socket ()"); exit(1); }
    
    if ( connect( sock , ( SOCKADDR*) &sin , sizeof (sin) ) == SOCKET_ERROR ) { perror("connect ()"); exit(2); }
    
    printf("Connetion on %s with port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));



	
	while (	fgets(file_buffer,sizeof(file_buffer),file)) {

	//printf("Client send :%s",file_buffer);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    strcat(buffer,"GET /Telnet/index.php?msg=");
    strncat(buffer,file_buffer,strlen(file_buffer));
    //strcat(buffer,buffer);
    //rncat(buffer,buffer,strlen(buffer));
    strcat(buffer," HTTP/1.1\r\n");

    strcat(buffer,"Accept:*/*\r\n");
    strcat(buffer,"Accept-Language: en-gb\r\n");
    strcat(buffer,"Content-Type: application/x-www-form-urlencoded\r\n");
    strcat(buffer,"Accept-Encoding:  deflate\r\n");
    strcat(buffer,"User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0)\r\n");
    
    /*strcat(buffer,"Host:");
    strncat(buffer,Host,strlen(Host));
    strcat(buffer," \r\n");*/

    strcat(buffer,"Host:localhost \r\n");

    strcat(buffer,"Content-Length: 20\r\n");//----------->>
    strcat(buffer,"Connection: Keep-Alive\r\n");//----------->>

    strcat(buffer,"Cache-Control: no-cache\r\n\r\n");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if ( send( sock, buffer , sizeof(buffer) , 0 ) == -1 ) { perror("send ()"); exit(3); }
	printf("Client send :\n %s",buffer);
	
	}

    if (closesocket(sock) == SOCKET_ERROR ) { perror("closesocket ()"); exit(4); }
    
    if (fclose(file) == SOCKET_ERROR ) { perror("fclose ()"); exit(5); }


    printf("====================  END  ========================");

    end();
    
    return 0;
}