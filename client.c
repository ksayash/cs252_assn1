
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
  char buffer[1024];
  char html[4096];
  FILE* fp;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

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
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  /*---- Read the message from the server into the buffer ----*/

  /*---- Print the received message ----*/

  printf("please enter the Query\n");
  bzero(buffer,256);
  scanf("%[^\n]s",buffer );
  n = send(clientSocket, buffer, strlen(buffer),0);
  bzero(buffer,256);
  n = recv(clientSocket, html,4096,0);
  fp = fopen("index.html", "w");
   if (fp == NULL)
    {
      printf("File not found!\n");
      return 0;
    }
  fwrite(html, sizeof(char), strlen(html), fp);
  fclose(fp);
  system("x-www-browser index.html");
  sleep(1);
  system("rm index.html");

  return 0;
}
