#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {
findfile("c:\\");
findfile("d:\\");
}
void findfile(char dossier[4096]) {
   char ssdossier[4096];
   struct dirent *lecture;
   DIR *rep;
   rep = opendir(dossier);
   
   while ((lecture = readdir(rep))) {
         if(!strcmp(lecture->d_name,".") || !strcmp(lecture->d_name,"..")) continue;
         sprintf(ssdossier,"%s%s\\",dossier,lecture->d_name);
         if (opendir(ssdossier) != NULL) {findfile(ssdossier);}
         printf("%s\n",ssdossier);
         }   
   closedir(rep);
}