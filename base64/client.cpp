#include <cstdlib>
#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include <dirent.h>
#include <time.h>

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
    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer_in [Packet_Size] = "",buffer_out [Packet_Size] = "";
    FILE *out_file;
    long file_size;

  char path [Packet_Size] = "";
  printf("\n taper your message : ");
  gets(path);

    int i=0,j=0,k=0;
    for (i=strlen(path)-1;i>=0;i--)
        if (path[i]=='\\' /*|| path[i]=='/'*/){j=i+1;break;}
    for (i=j;i<strlen(path);i++)
        //sprintf(buffer_out,"%s%c",buffer_out,path[i]);
        {buffer_out[k]=path[i];k++;}

 
    out_file = fopen(path,"r+");
    fseek(out_file, 0, SEEK_END);
    file_size = ftell(out_file);
    fclose(out_file);
    printf("\nname :'%s' , size = %d octets or %.3f Ko or %.3f Mo or %.3f Go\n",buffer_out, file_size, (float)file_size/1024, (float)file_size/1048576,(float)file_size/1073741824);                
   

  printf("\n\n");

 
    
    sin.sin_addr.s_addr = inet_addr(Host);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(Port);
    
    WSAData wsadata;
    WSAStartup( MAKEWORD(2,2) , &wsadata );
    
    sock =  socket(  AF_INET , SOCK_STREAM , IPPROTO_TCP );
    if ( sock == INVALID_SOCKET ) { perror("socket ()"); exit(1); }
    
    if ( connect( sock , ( SOCKADDR*) &sin , sizeof (sin) ) == SOCKET_ERROR ) { perror("connect ()"); exit(2); }
    
    if ( send( sock, buffer_out , sizeof(buffer_out) , 0 ) == -1 ) { perror("send ()"); exit(3); }
    





    i=1;
    out_file = fopen(path,"r+");
begin:    
    while (/*fread(buffer_out,sizeof(buffer_out),1, out_file)*/fgets (buffer_out , sizeof(buffer_out) , out_file) > 0) { 
        
        const std::string msg = buffer_out ;

        std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(msg.c_str()), msg.length());

        const char* e = encoded.c_str();
        printf("\nencoded64 --> %s\n", e);
        //buffer_out[0]='\0';
        for (int i = 0; i < strlen(e); i++)
        {
        buffer_out[i]=e[i];
        }


        if (send(sock,e,sizeof(buffer_out),0)){
        //printf("%.3f pour cent \n",(float)(Packet_Size*i*100)/file_size);    
        i++;
        }else { printf("transmission error"); goto end;}
    }
    
    send(sock,"End",sizeof(buffer_out)+1,0);
    printf("End of Tansmission !\n");
    
    if (recv(sock, buffer_in, sizeof(buffer_in), 0) == SOCKET_ERROR ) {  printf("Retransmission <--|"); goto begin; }
    if ( strcmp ((char*)buffer_in,"Ack") == 0  ) {printf("Recive ACK\n");}
    
end:   
    fclose(out_file);



    if (closesocket(sock) == -1 ) { perror("closesocket ()"); exit(4); }
    
    WSACleanup();
    
    system("PAUSE");
    return EXIT_SUCCESS;
}








/*
char *searchword="" ;
char *prefix ="";        
        
void Client (char IP[15], char PORT[10], char path[4096]) {
    
    
    SOCKADDR_IN Server_Address;
    SOCKET Socket;
    int Port ;
    FILE *out_file;
    char Buff_info[50]="";
    char buffer_in[Packet_Size]="";
    long file_size;
    int i=0,j=0;


    for (i=strlen(path)-1;i>=0;i--)
        if (path[i]=='\\' /*|| path[i]=='/'*\/){j=i+1;break;}
    for (i=j;i<strlen(path);i++)
        sprintf(Buff_info,"%s%c",Buff_info,path[i]);

 
    out_file = fopen(path,"r+");
    fseek(out_file, 0, SEEK_END);
    file_size = ftell(out_file);
    fclose(out_file);
    printf("\nname :'%s' , size = %d octets or %.3f Ko or %.3f Mo or %.3f Go\n",Buff_info, file_size, (float)file_size/1024, (float)file_size/1048576,(float)file_size/1073741824);                
   
    
    
    
    Port = atoi(PORT);   
    Server_Address.sin_family = AF_INET;
    Server_Address.sin_port = htons ( Port );
    Server_Address.sin_addr.s_addr = inet_addr(IP);    
    
    Socket = socket ( AF_INET, SOCK_STREAM, 0 );
    
    if ( Socket == INVALID_SOCKET ) {perror ("socket()"); exit(errno);}
    
    if ( Server_Address.sin_addr.s_addr == INADDR_NONE ) {printf ( "Bad Address!" ); exit(errno);}
    
    if (connect ( Socket, (struct sockaddr *)&Server_Address, sizeof (Server_Address) )) {perror ("connect()"); exit(errno);}

    send(Socket,Buff_info,sizeof(Buff_info)+1,0);
    
    i=1;
    out_file = fopen(path,"r+");
begin:    
    while (fread(buffer_in,sizeof(buffer_in),1, out_file) > 0) {            
        if (send(Socket,buffer_in,sizeof(buffer_in)+1,0)){
        //printf("%.3f pour cent \n",(float)(Packet_Size*i*100)/file_size);    
        i++;
        }else { printf("transmission error"); goto end;}
    }
    
    send(Socket,"End",sizeof(buffer_in)+1,0);
    
    if (recv(Socket, buffer_in, sizeof(buffer_in)+1, 0) == SOCKET_ERROR ) {  printf("Retransmission <--|"); goto begin; }
    if ( strcmp (buffer_in,"Ack") == 0  ) {printf("Recive ACK\n");}
    
end:   
    close (Socket);
    fclose(out_file);
    
    
    
}       



int IS_Contain (char fn[50]) {
    
    //printf("\n'%s' <--> '%s' == ",fn,searchword);
    
    int i=0,j=0,k=0;
    
    for (i=0;i<strlen(fn);i++) if (fn[i]==searchword[0]) {j=i;break;}
    
    for (i=j;i<j+strlen(searchword);i++) 
        if (fn[i]!=searchword[k]) {printf("");return 0;}
        else                      k++;
    
    printf("");
    return 1;
}


void findfile(char dossier[4096]) {
    
    char ssdossier[4096];
    struct dirent *lecture;
    DIR *rep;
        

    
    rep = opendir(dossier);

    while ((lecture = readdir(rep))) {
        
        if (!strcmp(lecture->d_name, ".") || !strcmp(lecture->d_name, "..")) continue;
        
        sprintf(ssdossier, "%s%s\\", dossier, lecture->d_name);
        if (opendir(ssdossier) != NULL) {findfile(ssdossier);}
        
        
    int i=0,j=0,k=0;
    char file_name[50] = "";
    char source [4096] = "";

    //printf("finde file\n");
    for (i=strlen(ssdossier)-2;i>=0;i--) if (ssdossier[i]=='\\') {j=i+1;break;}
    
    for (i=j;i<strlen(ssdossier)-1;i++)
        {
        sprintf(file_name,"%s%c",file_name,ssdossier[i]);//file_name[k]=path[i];k++;
        }
    
    for (i=0;i<strlen(ssdossier)-1;i++)  { sprintf(source,"%s%c",source,ssdossier[i]);}

    if (!strcmp(searchword,"all")==0) {if (IS_Contain(file_name)){Client("127.0.0.1","2013",source);} }
    else                              {Client("127.0.0.1","2013",source);}
    
    //Sleep(2000);
    
    }
    
    closedir(rep);
}


void detectUSB () {
    detect:
    char d[1024] = "";
    char *adr;
    int i=0;
    GetLogicalDriveStrings(1024, d);
    adr = d;
    
    while (*adr) {
        if (GetDriveType(adr) == DRIVE_REMOVABLE/*2*\/)
        {
            i++;
            printf("DRIVE AMOVIBLE %d :%s\n", i, adr);
            findfile(adr);
        }
        adr += 4;
    }

    //goto detect;
    //if (i==0) printf("no drive amovible is exist!");    
}




        
int main ( int agrc, char *argv[] )
{
    if (agrc !=3) 
    {
        printf("must be entred 2 argument! for example :\n./program searchword partition(c,d,etc.)");
    }
    else 
    {
    
    searchword = argv[1];
    prefix = argv[2];
    
    if (strlen(prefix)!=1) {printf ("argument 2 must be 1 char, it represent each partition , for example c,d ...\n");exit(1);}
    
    sprintf(prefix,"%s%s%s%c",prefix,":\\",searchword,'\\');
    
    
    if (!strcmp(searchword,"all")==0) CreateDirectory(prefix,0);

        
    detectUSB();
    //findfile("D:\\k' root\\");
    
    //double timed = clock();
    //printf("%f",timed);
    //Sleep(1000);
    
    //double timef = clock()-timed;
    //printf("%f",timef);
    
    
    printf("\n###################  End  ###########################\n");
    }
}*/