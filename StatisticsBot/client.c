#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

int client_connect(int port, char *hostname){
  int socketfd;
  struct hostent *host;
  struct sockaddr_in serverAdd;
  if((socketfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
    return -1;
  }
  if((host = gethostbyname(hostname)) == NULL){
    return -1;
  }
  bzero((char *)&serverAdd, sizeof(serverAdd));
  serverAdd.sin_family = AF_INET;
  bcopy((char *)host->h_addr_list[0],(char *)&serverAdd.sin_addr.s_addr,host->h_length);
  serverAdd.sin_port = htons(port);
  if (connect(socketfd,(struct sockaddr *)&serverAdd,sizeof(serverAdd)) < 0){
    return -1;
  }
  return socketfd;
}

int stat_solver(char buffer[], int *num){
  char *split = strtok(buffer, " ");
  char op[10] = "min";
  for(int i=0; i<=6; i++){
    split = strtok(NULL, " ");
    if(i == 0){
      continue;
    }
    if(i == 1){
      strcpy(op, split);
    }else{
      num[i-2] = atoi(split);
    }
  }
  if(strcmp(op, "min") == 0){
    int ans = num[0];
    for(int i=0; i<5; i++){
      if(num[i] < ans){
        ans = num[i];
      }
    }
    return ans;
  }
  if(strcmp(op,"max") == 0){
    int ans = num[0];
    for(int i=0; i<5; i++){
      if(num[i] > ans){
        ans = num[i];
      }
    }
    return ans;
  }
  if(strcmp(op, "median") == 0){
    int temp; 
    for(int i=0; i<5; i++){
      for(int j = i + 1; j < 5; ++j){
        if(num[i] > num[j]){
          temp = num[i];
          num[i] = num[j];
          num[j] = temp;
        }
      }
    }
    return num[2];
  }
  return 0;
}

int main(int argc, char **argv)
{
  int socketfd;
  int port;
  char *host;
  if(argc != 4){
    printf("Error detected.");
    exit(0);
  }
  port = atoi(argv[2]);
  host = argv[3];
  printf("Connecting to server...");
  socketfd = client_connect(port, host);
  char buffer[256];
  sprintf(buffer, "cs230 HELLO ktalwar@umass.edu\n");
  int req = send(socketfd, buffer, strlen(buffer), 0);
  if(req < 0){
    printf("Error while trying to send a message");
    exit(0);
  }
  int arr[5];
  int rec = 0;
  do{
    rec = recv(socketfd, buffer, 256, 0);
    printf("Connection successful!");
    buffer[rec] = '\0';
    printf("%s", buffer);
    if(buffer[6] == 'S'){
      int ans = stat_solver(buffer, arr);
      sprintf(buffer, "cs230 %i\n", ans);
      printf("%s", buffer);
      req = send(socketfd, buffer, strlen(buffer), 0);
      if(req < 0){
        printf("Error while trying to create a request");
        exit(0);
      }
    }else{
      printf("\nConnection lost");
      break;
    }
  }while(rec > 0);

  close(socketfd);
  return 0;
}
