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
  int num_cars=0;
  int num_cats=0;
  int num_trucks=0;
  int num_dogs=0;
  char* token;
  char prev_token[20];
  const char delm[2] = " ";
  char html[4096] = "<!DOCTYPE html><html><head><title>Assignment 1</title></head><body><h1> Here is the response of your query </h1><table>";
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
   		if(i==0){
   			strcat(html,"<tr>");
   		}
        if(i > 3){
            strcat(html,"</tr>");
            strcat(msg, "<h3>Only 4 dog images are available, you requested more. Showing all four images. </h3> <br>");
            break;
        }
   		strcat(html,"<td>");
   		strcat(html,"<img src=\"");
   		strcat(html,cwd);
   		strcat(html,"/images/dog");
   		char temp[3];
   		sprintf(temp, "%d", i+1);
   		strcat(html,temp);
   		strcat(html,".jpeg\"></td>");

   		if(i==num_dogs-1){
   			strcat(html,"</tr>");
   		}
        flag = 1;
   	}
   	for(int i=0;i<num_cats;i++){
   		if(i==0){
   			strcat(html,"<tr>");
   		}
        if(i > 3){
            strcat(html,"</tr>");
            strcat(msg, "<h3>Only 4 cat images are available, you requested more. Showing all four images. </h3> <br>");
            break;
        }
   		strcat(html,"<td>");
   		strcat(html,"<img src=\"");
   		strcat(html,cwd);
   		strcat(html,"/images/cat");
   		char temp[3];
   		sprintf(temp, "%d", i+1);
   		strcat(html,temp);
   		strcat(html,".jpeg\"></td>");

   		if(i==num_cats-1){
   			strcat(html,"</tr>");
   		}
        flag = 1;
   	}
   	for(int i=0;i<num_cars;i++){
   		if(i==0){
   			strcat(html,"<tr>");
   		}
        if(i > 3){
            strcat(html,"</tr>");
            strcat(msg, "<h3>Only 4 car images are available, you requested more. Showing all four images. </h3> <br>");
            break;
        }
   		strcat(html,"<td>");
   		strcat(html,"<img src=\"");
   		strcat(html,cwd);
   		strcat(html,"/images/car");
   		char temp[3];
   		sprintf(temp, "%d", i+1);
   		strcat(html,temp);
   		strcat(html,".jpeg\"></td>");

   		if(i==num_cars-1){
   			strcat(html,"</tr>");
   		}
        flag = 1;
   	}
   	for(int i=0;i<num_trucks;i++){
   		if(i==0){
   			strcat(html,"<tr>");
   		}
        if(i > 3){
            strcat(html,"</tr>");
            strcat(msg, "<h3>Only 4 truck images are available, you requested more. Showing all four images. </h3> <br>");
            break;
        }
   		strcat(html,"<td>");
   		strcat(html,"<img src=\"");
   		strcat(html,cwd);
   		strcat(html,"/images/truck");
   		char temp[3];
   		sprintf(temp, "%d", i+1);
   		strcat(html,temp);
   		strcat(html,".jpeg\"></td>");

   		if(i==num_trucks-1){
   			strcat(html,"</tr>");
   		}
        flag = 1;
   	}

   	strcat(html,"</table>");
    strcat(html,msg);
    strcat(html,"</body></html>");

    if(flag == 0){
        strcpy(html,"<!DOCTYPE html><html><body><h1> Query doesn't have any returns. </h1></html></body>");
    }
   	n = send(newSocket,html,strlen(html),0);
   	strcpy(html,"<!DOCTYPE html><html><head><title>Assignment 1</title></head><body><h1> Here is the response of your query </h1><table>");
   	num_dogs =0;
   	num_trucks =0;
   	num_cats =0;
   	num_cars=0;
}
  return 0;
}
