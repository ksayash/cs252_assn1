
/* credit @Daniel Scocco */

/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
  int clientSocket;
  int n;
  char cwd[128];
  getcwd(cwd, sizeof(cwd));
  char path_name[256];
  strcpy(path_name,cwd);
  char buffer[1024];
  char html[4096] = "<!DOCTYPE html><html><head><title>Assignment 1</title></head><body><h1> Here is the response of your query </h1><table>";
  FILE* fp;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  int num_cars=0;
  int num_cats=0;
  int num_trucks=0;
  int num_dogs=0;
  char* token;
  char prev_token[20];
  const char delm[2] = " ";

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(5432);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  n=connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  char revbuf[512];
  //  printf("%d",n);
  /*---- Read the query to be sent to the server and send it ----*/
  printf("please enter the Query\n");
  bzero(buffer,256);
  scanf("%[^\n]s",buffer );
  n = send(clientSocket, buffer, strlen(buffer),0);
  token = strtok(buffer,delm);
  strcpy(prev_token,token);
  int flag = 0;
  while( token != NULL ) {
    token = strtok(NULL, delm);
    if(token != NULL){
      if((strcmp(token,"cars")==0)||(strcmp(token,"car")==0)){
        num_cars = (prev_token[0]-'0');
        if(num_cars > 4 || num_cars < 0) {
          flag = 0;
          break;
        }
        if(num_cars) flag = 1;
      }
      if((strcmp(token,"dogs")==0) || (strcmp(token,"dog")==0)){
        num_dogs = prev_token[0]-'0';
        if(num_dogs > 4 || num_dogs < 0) {
          flag = 0;
          break;
        }
        if(num_dogs) flag = 1;
      }
      if((strcmp(token,"cats")==0) || (strcmp(token,"cat")==0)){
        num_cats = prev_token[0]-'0';
        if(num_cats > 4 || num_cats < 0) {
          flag = 0;
          break;
        }
        if(num_cats) flag = 1;
      }
      if((strcmp(token,"trucks")==0) || (strcmp(token,"truck")==0)){
        num_trucks = prev_token[0]-'0';
        if(num_trucks > 4 || num_trucks < 0) {
          flag = 0;
          break;
        }
        if(num_trucks) flag = 1;
      }
      strcpy(prev_token,token);
    }

  }
  if (!flag) {
    printf("Please enter a valid query next time. Bye!\n");
    return 0;
  }
  /*---- Write the results of the query into a file  ----*/
  bzero(buffer,256);
  for(int i=0;i<num_dogs;i++){
    if(i==0){
      strcat(html,"<tr>");
    }
    strcat(html,"<td>");
    strcat(html,"<img src=\"");
    strcat(html,cwd);
    strcat(html,"/dog");
    char temp[3];
    sprintf(temp, "%d", i+1);
    strcat(html,temp);
    strcat(html,".jpeg\"></td>");
    if(i==num_dogs-1){
      strcat(html,"</tr>");
    }
    strcat(path_name,"/dog");
    strcat(path_name,temp);
    strcat(path_name,".jpeg");
    bzero(revbuf, 512);
    int fr_block_sz = 0;
    int success = 0;
    FILE *fr = fopen(path_name, "w");
    //while(success == 0)
    //{
    while((fr_block_sz = recv(clientSocket, revbuf, 512, 0))>0)
    {
      int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
      if(write_sz < fr_block_sz)
      {
        break;
        //error("File write failed.\n");
      }
      if(fr_block_sz<512){
        break;
      }
      if(!fr_block_sz)
      {
        break;
      }
      bzero(revbuf, 512);
    }
    fclose(fr);
    bzero(revbuf, 512);
    strcpy(path_name,cwd);
  }


  for(int i=0;i<num_cats;i++){
    if(i==0){
      strcat(html,"<tr>");
    }
    strcat(html,"<td>");
    strcat(html,"<img src=\"");
    strcat(html,cwd);
    strcat(html,"/cat");
    char temp[3];
    sprintf(temp, "%d", i+1);
    strcat(html,temp);
    strcat(html,".jpeg\"></td>");
    if(i==num_cats-1){
      strcat(html,"</tr>");
    }
    strcat(path_name,"/cat");
    strcat(path_name,temp);
    strcat(path_name,".jpeg");
    bzero(revbuf, 512);
    int fr_block_sz = 0;
    int success = 0;
    FILE *fr = fopen(path_name, "w");
    //while(success == 0)
    //{
    while((fr_block_sz = recv(clientSocket, revbuf, 512, 0))>0)
    {
      int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
      if(write_sz < fr_block_sz)
      {
        break;
        //error("File write failed.\n");
      }
      if(fr_block_sz<512){
        break;
      }
      if(!fr_block_sz)
      {
        break;
      }
      bzero(revbuf, 512);
    }
    fclose(fr);
    bzero(revbuf, 512);
    strcpy(path_name,cwd);
  }

  for(int i=0;i<num_cars;i++){
    if(i==0){
      strcat(html,"<tr>");
    }
    strcat(html,"<td>");
    strcat(html,"<img src=\"");
    strcat(html,cwd);
    strcat(html,"/car");
    char temp[3];
    sprintf(temp, "%d", i+1);
    strcat(html,temp);
    strcat(html,".jpeg\"></td>");
    if(i==num_cars-1){
      strcat(html,"</tr>");
    }
    strcat(path_name,"/car");
    strcat(path_name,temp);
    strcat(path_name,".jpeg");
    bzero(revbuf, 512);
    int fr_block_sz = 0;
    int success = 0;
    FILE *fr = fopen(path_name, "w");
    //while(success == 0)
    //{
    while((fr_block_sz = recv(clientSocket, revbuf, 512, 0))>0)
    {
      int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
      if(write_sz < fr_block_sz)
      {
        break;
        //error("File write failed.\n");
      }
      if(fr_block_sz<512){
        break;
      }
      if(!fr_block_sz)
      {
        break;
      }
      bzero(revbuf, 512);
    }
    fclose(fr);
    bzero(revbuf, 512);
    strcpy(path_name,cwd);
  }

  for(int i=0;i<num_trucks;i++){
    if(i==0){
      strcat(html,"<tr>");
    }
    strcat(html,"<td>");
    strcat(html,"<img src=\"");
    strcat(html,cwd);
    strcat(html,"/truck");
    char temp[3];
    sprintf(temp, "%d", i+1);
    strcat(html,temp);
    strcat(html,".jpeg\"></td>");
    if(i==num_trucks-1){
      strcat(html,"</tr>");
    }
    strcat(path_name,"/truck");
    strcat(path_name,temp);
    strcat(path_name,".jpeg");
    bzero(revbuf, 512);
    int fr_block_sz = 0;
    int success = 0;
    FILE *fr = fopen(path_name, "w");
    //while(success == 0)
    //{
    while((fr_block_sz = recv(clientSocket, revbuf, 512, 0))>0)
    {
      int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
      if(write_sz < fr_block_sz)
      {
        break;
        //error("File write failed.\n");
      }
      if(fr_block_sz<512){
        break;
      }
      if(!fr_block_sz)
      {
        break;
      }
      bzero(revbuf, 512);
    }
    fclose(fr);
    bzero(revbuf, 512);
    strcpy(path_name,cwd);
  }
  strcat(html,"</table>");
  strcat(html,"</body></html>");
  fp = fopen("index.html", "w");
  if (fp == NULL)
  {
    printf("File not found!\n");
    return 0;
  }
  fwrite(html, sizeof(char), strlen(html), fp);
  fclose(fp);
  /*---- Open the browser to show the file received from server ----*/
  system("x-www-browser index.html");
  sleep(10);
  system("rm index.html");
  system("rm *.jpeg");
  return 0;
}
