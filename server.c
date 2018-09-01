#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<libgen.h>

int main(){
  int welcomeSocket, newSocket;
  char buffer[1024];
  int n;
  char* local_file = "/images/car1.jpeg";
	char* ts2 = strdup(local_file);

	char* dir = dirname(ts2);
	
	char* filename = basename(ts2);
	printf("%s\n",dir);
  int num_cars=0;
  int num_cats=0;
  int num_trucks=0;
  int num_dogs=0;
  char* token;
  char prev_token[20];
  const char delm[2] = " ";
  char html[4096] = "<!DOCTYPE html><html><head><title>Assignment 1</title></head><body><h1> Here is the response of your query </h1><table>";
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
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
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
  
  while(1){
    bzero(buffer,256);
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  /*---- Send message to the socket of the incoming connection ----*/
  	n = recv( newSocket,buffer,255,0 );
  	token = strtok(buffer,delm);
  	strcpy(prev_token,token);
  	while( token != NULL ) {
      token = strtok(NULL, delm);
      if(token != NULL){
      	if((strcmp(token,"cars")==0)||(strcmp(token,"car")==0)){
      		printf("cars\n");
      		num_cars = (prev_token[0]-'0');
      	}
      	if((strcmp(token,"dogs")==0) || (strcmp(token,"dog")==0)){
      		printf("cars2\n");
      		num_dogs = prev_token[0]-'0';
      	}
      	if((strcmp(token,"cats")==0) || (strcmp(token,"cat")==0)){
      		printf("cars3\n");
      		num_cats = prev_token[0]-'0';
      	}
      	if((strcmp(token,"trucks")==0) || (strcmp(token,"truck")==0)){
      		printf("cars4\n");
      		num_trucks = prev_token[0]-'0';
      	}
      	strcpy(prev_token,token);	
      }
      
   	}

   	for(int i=0;i<num_dogs;i++){
   		if(i==0){
   			strcat(html,"<tr>");
   		}
   		strcat(html,"<td>");
   		strcat(html,"<img src=\"./images/dog");
   		char temp[3];
   		sprintf(temp, "%d", i+1);
   		strcat(html,temp);
   		strcat(html,".jpeg\"></td>");
   		if(i==num_dogs-1){
   			strcat(html,"</tr>");
   		}
   	}
   	for(int i=0;i<num_cats;i++){
   		if(i==0){
   			strcat(html,"<tr>");
   		}
   		strcat(html,"<td>");
   		strcat(html,"<img src=\"./images/cat");
   		char temp[3];
   		sprintf(temp, "%d", i+1);
   		strcat(html,temp);
   		strcat(html,".jpeg\"></td>");
   		if(i==num_dogs-1){
   			strcat(html,"</tr>");
   		}
   	}
   	for(int i=0;i<num_cars;i++){
   		if(i==0){
   			strcat(html,"<tr>");
   		}
   		strcat(html,"<td>");
   		strcat(html,"<img src=\"./images/car");
   		char temp[3];
   		sprintf(temp, "%d", i+1);
   		strcat(html,temp);
   		strcat(html,".jpeg\"></td>");
   		if(i==num_dogs-1){
   			strcat(html,"</tr>");
   		}
   	}
   	for(int i=0;i<num_trucks;i++){
   		if(i==0){
   			strcat(html,"<tr>");
   		}
   		strcat(html,"<td>");
   		strcat(html,"<img src=\"./images/truck");
   		char temp[3];
   		sprintf(temp, "%d", i+1);
   		strcat(html,temp);
   		strcat(html,".jpeg\"></td>");
   		if(i==num_dogs-1){
   			strcat(html,"</tr>");
   		}
   	}
   	n = send(newSocket,html,strlen(html),0);
   	bzero(buffer,256);

}
  return 0;
}
