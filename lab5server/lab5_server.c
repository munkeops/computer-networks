// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<time.h>
#include<sys/stat.h>
#include"md5.h"
#include <sys/types.h>

#define PORT 8080 


void getFileCreationTime(char *path,char lastmod[]) {
    struct stat attr;
    stat(path, &attr);
    strcpy(lastmod,ctime(&attr.st_mtime));
    // /printf("Last modified time: %s",ctime(&attr.st_mtime) );
}

void getIndexShort()
{
    

}
void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 
} 
  
int main(int argc, char const *argv[]) 
{ 
    printf("\n\n\nListening...\n\n\n");

	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 

	char *hello = "Hello from server"; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	}
	while((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))>0) 
    {
        if (new_socket<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 
        //send(new_socket , "Menu\n1)" , strlen("Menu\n1)") , 0 );
        char sizec;
        int i,j;
        char n[20];
        valread=read(new_socket,n,20);
        if(strcmp(n,"1")==0)
        {
            printf("%s\n","IndexGet Request");
            char t1[20],t2[20];
            valread=read(new_socket,t1,20);
            valread=read(new_socket,t2,20);
            printf("time between %s and %s\n",t1,t2);
        }
        else if(strcmp(n,"1")==0)
        {
            printf("%s\n","IndexGet Request");

        }
        else if(strcmp(n,"2")==0)
        {
            printf("%s\n","IndexGet Request");
            
        }
        else if(strcmp(n,"3")==0)
        {
            
        }
        else if(strcmp(n,"4")==0)
        {
            
        }
        else if(strcmp(n,"5")==0)
        {
            printf("%s\n","FileUpload Request");

            char name[20],size[20];
            int size1;
            valread=read(new_socket,name,20);
            valread=read(new_socket,size,20);
            //printf("name= %s\n",name);
            sscanf(size, "%d", &size1); 
            //printf("size= %s\n",size);
            if(size1>1024*1024)
            {
                send(new_socket,"1",sizeof("1"),0);
            }
            else
            {
                send(new_socket,"0",sizeof("0"),0);
                //printf("hello\n");
                //delay(10);
                char file[size1];
                valread=read(new_socket,file,size1);
                FILE* fptr = fopen(name,"w");
                if (fptr != NULL)
                {
                    fputs(file, fptr);
                    fseek(fptr, 0, SEEK_SET);
                    fclose(fptr);
                }
                //char* hash=(char*)malloc(sizeof(char)*34);
                char hash[34]="";
                hashfn(file,hash,size1);
                //printf("%ld\n",strlen(hash));
                printf("md5hash = %s\n",hash);
                //free(hash);
                char lastmod[50];
                getFileCreationTime(name,lastmod);
                printf("last mod = %s",lastmod);
                send(new_socket,"Request Completed",sizeof("Request Completed"),0);

            }
            

        }
        else if(strcmp(n,"6")==0)
        {
            printf("%s\n","FileDownload Request");

            char name[20];
            valread=read(new_socket,name,20);
            //if(name) //check if name exists in file and then check size 
            send(new_socket,"1",sizeof("1"),0);
            FILE * f = fopen (name, "rb");
            int length;
            char * buffer;

            struct stat st; /*declare stat variable*/
     
            /*get the size using stat()*/
            char size[20];
            
            if(stat(name,&st)==0)
                sprintf(size, "%ld", st.st_size); 
            else
                printf("no\n");

            if (f)
            {
                fseek (f, 0, SEEK_END);
                length = ftell (f);
                fseek (f, 0, SEEK_SET);
                buffer =(char *) malloc (length);
                if (buffer)
                {
                    fread (buffer, 1, length, f);
                }
                fclose (f);
            }
            send(new_socket,size,20,0);
            sscanf(size,"%d",&length);
            if(length>1024*1024)
		    {
			    
		    }
		    else
		    {
                send(new_socket,buffer,length,0);
            }
        }
        
        //rohan's code
        

        
        printf("Response Sent!\n"); 

        printf("\n\n\nListening...\n\n\n");
    }

        
        //clear_code(arr,row,col,n);
	return 0; 
} 
