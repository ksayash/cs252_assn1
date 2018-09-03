#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
  int welcomeSocket, newSocket;
  char buffer[1024];
  int n;
  char cwd[128];
  getcwd(cwd, sizeof(cwd));
  char path_name[256];
  strcpy(path_name,cwd);
  int num_cars=0;
  int num_cats=0;
  int num_trucks=0;
  int num_dogs=0;
  char* token;
  char prev_token[20];
  const char delm[2] = " ";
  char msg[1024] = "";
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(5432);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("I'm listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  char sdbuf[512];
  while(1){
    bzero(sdbuf,512);
    bzero(buffer,256);
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  /*---- Send message to the socket of the incoming connection ----*/
    n = recv( newSocket,buffer,255,0 );
    token = strtok(buffer,delm);
    strcpy(prev_token,token);
    int flag = 0;
    while( token != NULL ) {
      token = strtok(NULL, delm);
      if(token != NULL){
        if((strcmp(token,"cars")==0)||(strcmp(token,"car")==0)){
          num_cars = (prev_token[0]-'0');
        }
        if((strcmp(token,"dogs")==0) || (strcmp(token,"dog")==0)){
          num_dogs = prev_token[0]-'0';
        }
        if((strcmp(token,"cats")==0) || (strcmp(token,"cat")==0)){
          num_cats = prev_token[0]-'0';
        }
        if((strcmp(token,"trucks")==0) || (strcmp(token,"truck")==0)){
          num_trucks = prev_token[0]-'0';
        }
        strcpy(prev_token,token);
      }

    }

    for(int i=0;i<num_dogs;i++){
      char temp[3];
      sprintf(temp, "%d", i+1);
      strcat(path_name,"/images/dog");
      strcat(path_name,temp);
      strcat(path_name,".jpeg");
      FILE *fs = fopen(path_name, "r");
      bzero(sdbuf, 512); 
      int fs_block_sz; 
    //int success = 0;
      while((fs_block_sz = fread(sdbuf, sizeof(char), 512, fs))>0)
      {
        
          if(send(newSocket, sdbuf, fs_block_sz, 0) < 0)
          {
              //printf("ERROR: Failed to send file %s.\n", fs_name);
              break;
          }
          bzero(sdbuf, 512);
        
      }
      fclose(fs);
      bzero(sdbuf, 512);
      strcpy(path_name,cwd);
      sleep(2);
    }


    for(int i=0;i<num_cats;i++){
      
       char temp[3];
      sprintf(temp, "%d", i+1);
      strcat(path_name,"/images/cat");
      strcat(path_name,temp);
      strcat(path_name,".jpeg");
      FILE *fs = fopen(path_name, "r");
      bzero(sdbuf, 512); 
      int fs_block_sz; 
      
    //int success = 0;
      while((fs_block_sz = fread(sdbuf, sizeof(char), 512, fs))>0)
      {
        
          if(send(newSocket, sdbuf, fs_block_sz, 0) < 0)
          {
              //printf("ERROR: Failed to send file %s.\n", fs_name);
              break;
          }
          bzero(sdbuf, 512);
          
      }

      fclose(fs);
      bzero(sdbuf, 512);
      strcpy(path_name,cwd);  
      sleep(2);
    }


    for(int i=0;i<num_cars;i++){
       char temp[3];
      sprintf(temp, "%d", i+1);
      strcat(path_name,"/images/car");
      strcat(path_name,temp);
      strcat(path_name,".jpeg");
      FILE *fs = fopen(path_name, "r");
      bzero(sdbuf, 512); 
      int fs_block_sz; 
    //int success = 0;
      while((fs_block_sz = fread(sdbuf, sizeof(char), 512, fs))>0)
      {
        
          if(send(newSocket, sdbuf, fs_block_sz, 0) < 0)
          {
              //printf("ERROR: Failed to send file %s.\n", fs_name);
              break;
          }
          bzero(sdbuf, 512);
          
      }
      fclose(fs);
      bzero(sdbuf, 512);
      strcpy(path_name,cwd);
      sleep(2);
    }


    for(int i=0;i<num_trucks;i++){
       char temp[3];
      sprintf(temp, "%d", i+1);
      strcat(path_name,"/images/truck");
      strcat(path_name,temp);
      strcat(path_name,".jpeg");
      FILE *fs = fopen(path_name, "r");
      bzero(sdbuf, 512); 
      int fs_block_sz; 
    //int success = 0;
      while((fs_block_sz = fread(sdbuf, sizeof(char), 512, fs))>0)
      {
        
          if(send(newSocket, sdbuf, fs_block_sz, 0) < 0)
          {
              //printf("ERROR: Failed to send file %s.\n", fs_name);
              break;
          }
          bzero(sdbuf, 512);
          
      }
      fclose(fs);
      bzero(sdbuf, 512);
      strcpy(path_name,cwd);
      sleep(2);
    }

    num_dogs =0;
    num_trucks =0;
    num_cats =0;
    num_cars=0;
}
  return 0;
}
