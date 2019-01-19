#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"

int
sys_listen(void)
{
  int port = 0;

  //
  // TODO: Write your code to get and validate port no.
  //
  if(argint(0 , &port) < 0)
    return -1;

  if(port < 0 || port > NPORT)
    return E_INVALID_ARG;
  
  return listen(port);
}

int
sys_connect(void)
{
  int port = 0;
  char *host = 0;

  //
  // TODO: Write your code to get and validate port no., host.
  // Allow connection to "localhost" or "127.0.0.1" host only
  //
  if(argint(0 , &port) < 0)
    return -1;
  
  if(argstr(1,&host) < 0)
    return -1;
    
  if(port < 0 || port > NPORT)
    return E_INVALID_ARG;

  if(strncmp("localhost",host,strlen(host))==0 || strncmp("127.0.0.1",host,strlen(host))==0)
  {
    return connect(port, host);
  }
  else{
    return E_INVALID_ARG;
  } 

}

int
sys_send(void)
{
  int port = 0;
  char* buf = 0;
  int n = 0;

  //
  // TODO: Write your code to get and validate port no., buffer and buffer size
  //
  if(argint(0 , &port) < 0)
    return -1;
  
  if(argstr(1,&buf) < 0)
    return -1;
  
  if(argint(2,&n) < 0)
    return -1;

  if(port < 0 || port > NPORT)
    return E_INVALID_ARG;

  // if(sizeof(buf) +1 > n){
  //   cprintf("\nSend func:Size mismatch n: %d - buf: %d \n",n,sizeof(buf) +1 );
  //   return E_INVALID_ARG;
  // }

  return send(port, buf, n);
}

int
sys_recv(void)
{
  int port = 0;
  char* buf = 0;
  int n = 0;

  //
  // TODO: Write your code to get and validate port no., buffer and buffer size
  //
  if(argint(0 , &port) < 0)
    return -1;
  
  if(argstr(1,&buf) < 0)
    return -1;
  
  if(argint(2,&n) < 0)
    return -1;

  if(port < 0 || port > NPORT)
    return E_INVALID_ARG;

  // if(sizeof(buf) +1 < n){
  //   cprintf("\nRecv func:Size mismatch n: %d - buf: %d \n",n,sizeof(buf) +1 );
  //   return E_INVALID_ARG;
  // }

  return recv(port, buf, n);
}

int
sys_disconnect(void)
{
  int port = 0;

  //
  // TODO: Write your code to get and validate port no.
  //
  if(argint(0 , &port) < 0)
    return -1;
  
  if(port < 0 || port > NPORT)
    return E_INVALID_ARG;

  return disconnect(port);
}
