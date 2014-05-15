
#include <cstdlib>
#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream.h>

#define Packet_Size 1024
#define errno 1


#define Host "127.0.0.1"
#define Port 2013


using namespace std;



static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                        "abcdefghijklmnopqrstuvwxyz"
                                        "0123456789+/";


static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}


std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}


std::string base64_decode(std::string const& encoded_string) {

  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}











int main(/*int argc, char *argv[]*/)
{
    
    SOCKET Main_Socket;    
    SOCKET Communication_Socket; 

    SOCKADDR_IN sin ,csin;
    char buffer_in [Packet_Size]="",buffer_out [Packet_Size]="";
    FILE *in_file;
    
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(Port);
    
    WSAData wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata );
    
    Main_Socket = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP );
    if ( Main_Socket == INVALID_SOCKET ) { perror("socket ()"); exit(1);}
    
    if ( bind( Main_Socket , (SOCKADDR *) &sin , sizeof(sin)) == SOCKET_ERROR ) { perror("bind ()"); exit(2);}
    
    if ( listen(Main_Socket , 5 ) == SOCKET_ERROR ) { perror("listen ()"); exit(3);}
    

   printf ("Server Communicating By Using Port %d\n", Port);
    cout << "\n \n the server is ready to use.\n";
       
    int csin_size = sizeof(csin);

        Communication_Socket = accept( Main_Socket , (SOCKADDR *) &csin, &csin_size );
        if ( Communication_Socket == INVALID_SOCKET ) { perror("accept ()"); exit(4);}



        if (recv(Communication_Socket, buffer_in, sizeof(buffer_in), 0)) {in_file=fopen(buffer_in,"w+");printf("file_name :'%s'\n",buffer_in);}
        else                                                          { printf("can not get the file name!\n"); goto end;}

        
            
            while(1) {

                if (recv(Communication_Socket, buffer_in, sizeof(buffer_in), 0)) {
                    //sleep(0.1);
                    if ( strcmp ((char*)buffer_in,"End") == 0  ) { printf("End of Tansmission !\n"); break; }
                    else                              
                     { 
                      
                      const std::string msg = buffer_in ;

                      std::string decoded = base64_decode(msg);

                      const char* d = decoded.c_str();
                      printf("\ndecoded64 --> %s\n", d);

                      for (int i = 0; i < strlen(d); i++)
                      {
                      buffer_in[i]=d[i];
                      }
                      
                      //fwrite(buffer_in,sizeof(buffer_in),1, in_file); 
                      fputs (d , in_file );


                    }
                }
                else 
                {
                    printf("Tansmission error !\n"); goto end;
                }
            }

            send(Communication_Socket, "Ack" ,sizeof(buffer_out),0);
            printf("ACK Send");                
                
            end: 
            fclose(in_file);








    
        if ( closesocket( Communication_Socket ) ==-1 ) { perror("closesocket ()"); exit(6);}

    
    cout << "\n \n the server is closed.\n \n";
    
       
    if ( closesocket( Main_Socket ) ==-1 ) { perror("closesocket ()"); exit(7);}
    
    WSACleanup();
    
    system("PAUSE");
    return EXIT_SUCCESS;
}


/*

        #define Packet_Size 16
        #define errno 1
        //#define IP "127.0.0.1"
        //#define PORT 2013

        
        
void Server (char IP[15], char PORT[10]) {
    

    SOCKET Main_Socket;    
    SOCKET Communication_Socket; 
    SOCKADDR_IN Server_Address; 
    SOCKADDR_IN Client_Address;
    int Port;
    FILE *in_file;
    socklen_t lenght;        
    
    char buffer_in[Packet_Size];
    

    Server_Address.sin_family = AF_INET;
    Server_Address.sin_addr.s_addr = inet_addr(IP);
    Port = atoi(PORT);
    Server_Address.sin_port = htons(Port);
    
    printf ("Server Communicating By Using Port %d\n", Port);
    
    
    
    
    
    

    while (1) {
        
    Main_Socket = socket ( AF_INET, SOCK_STREAM, 0 );
    
    if ( Main_Socket == SOCKET_ERROR ) {perror ("socket()"); exit(errno); }

    if ( bind ( Main_Socket, (struct sockaddr*)&Server_Address, sizeof(Server_Address) ) == SOCKET_ERROR ) {printf ("bind()"); exit(errno);}
  
    if (listen (Main_Socket,12) == SOCKET_ERROR ) {printf ("listen()"); exit(errno);}
    
    lenght = sizeof (Client_Address);        
        
        Communication_Socket = accept ( Main_Socket, (struct sockaddr*)&Client_Address, &lenght );
   //if (!fork()) {
        char Buff_info[50]="";
        if (recv(Communication_Socket, Buff_info, sizeof(Buff_info)+1, 0)) {in_file=fopen(Buff_info,"w+");}
        else                                                          { printf("can not get the file name!\n"); goto end;}

        printf("file_name :'%s'\n",Buff_info);
            
            while(1) {

                if (recv(Communication_Socket, buffer_in, sizeof(buffer_in)+1, 0)) {
                    //sleep(0.1);
                    if ( strcmp (buffer_in,"End") == 0  ) { printf("End of Tansmission !\n"); break; }
                    else                               { fwrite(buffer_in,sizeof(buffer_in),1, in_file); }
                }
                else 
                {
                    printf("Tansmission error !\n"); goto end;
                }
            }

            send(Communication_Socket, "Ack" ,sizeof(buffer_in)+1,0);
            printf("ACK Send");                
                
            end: 
            close(Main_Socket);
            close(Communication_Socket);
            fclose(in_file);
       
    //}
    }    
    
}        
        
int main ( int agrc, char *argv[] )
{
    if (agrc!=3) { printf("2 arguments must be entred ! for example:\n./program IP Port.\n"); exit(1);}
    Server(argv[1],argv[2]);
    return 0;
}
*/