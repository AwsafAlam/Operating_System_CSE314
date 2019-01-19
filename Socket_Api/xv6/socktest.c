#include "types.h"
#include "user.h"
#include "param.h"

int serverPort = 10;

void printError(int status){
  if(status == E_NOTFOUND)
      printf(1, "Client>>Error E_NOTFOUND: %d\n",status);
    else if(status == E_ACCESS_DENIED)
        printf(1, "Client>>Error E_ACCESS_DENIED: %d\n",status);
    else if(status == E_WRONG_STATE)
        printf(1, "Client>>Error E_WRONG_STATE: %d\n",status);
    else if(status == E_FAIL)
        printf(1, "Client>> Error E_FAIL: %d\n",status);
    else if(status == E_INVALID_ARG)
          printf(1, "Client>> Error E_INVALID_ARG: %d\n",status);
    else
      printf(1, "Client>>Unknown Error : %d\n",status);
}

void clientProc() {
  int clientPort;
  char buf[128];
  char host[16] = "localhost";

  // sleep for 100 clock ticks to ensure that the server process starts first.
  sleep(100);

  printf(1, "Client>> Attempting to connect to port %d, host %s ...\n", serverPort, host);
  clientPort = connect(serverPort, host);
  if(clientPort < 0){
    printError(clientPort);
    printf(1, "Exiting client..\n");
    return;
  }
  else
    printf(1, "Client>> connect() returned %d\n", clientPort);

  while (1) {
    printf(1, "Client>> Enter text to send to server: ");
    gets(buf, sizeof(buf));
    buf[strlen(buf) - 1] = '\0'; // Eliminating the '\n'
    int sendStat = send(clientPort, buf, strlen(buf) + 1);
    if(sendStat < 0)
      printError(sendStat);

  

    if (0 == strcmp(buf, "exit")) {
      printf(1, "Client exiting...\n");
      disconnect(clientPort);
      break;
    }

    sleep(100 + uptime() % 100);

    memset(&buf[0], 0, sizeof(buf));
    int recStatus = recv(clientPort, buf, sizeof(buf));
    if(recStatus < 0)
      printError(recStatus);
    else
      printf(1, "Client>> Received: \"%s\" STATUS: %d\n", buf,recStatus);
  }
}

void serverProc() {
  int status;
  char buf[128];

  // sleep(100); // Make sure client starts before server
  printf(1, "Server>> Starting to listen at port %d ...\n", serverPort);
  status = listen(serverPort);
  if(status < 0)
    printError(status);
  else
    printf(1, "Server>> listen() returned STATUS %d\n", status);

  while (1) {
    sleep(100 + uptime() % 100);
    
    memset(&buf[0], 0, sizeof(buf));
    int recvStatus = recv(serverPort, buf, sizeof(buf));
    if(recvStatus < 0)
      printError(recvStatus);
    else
      printf(1, "Server>> Received: \"%s\" STATUS: %d\n", buf, recvStatus);

    if (0 == strcmp(buf, "exit")) {
      printf(1, "Server exiting...\n");
      disconnect(serverPort);
      break;
    }

    sleep(100 + uptime() % 100);

    strcpy(buf+strlen(buf), " OK");
    int sendStatus = send(serverPort, buf, strlen(buf) + 1);
    if(sendStatus < 0)
      printError(sendStatus);
    
  }
}


int main(int argc, char *argv[])
{
  if (0 == fork()) {
    clientProc();
    exit();
  } else {
    serverProc();
    // This is the parent process. So, it needs to wait before client terminates
    wait();
    exit();
  }
}
