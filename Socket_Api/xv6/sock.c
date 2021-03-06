#include "types.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "sock.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"


struct {
  struct spinlock lock;
  struct sock sock[NSOCK];
  int nsockets;
} stable;


void
sinit(void)
{
  initlock(&stable.lock, "stable");
  stable.nsockets = 0;
}


int
listen(int lport) {

  if(stable.nsockets > NSOCK)
    return E_FAIL;

  acquire(&stable.lock);
  cprintf("Listening at %d\n",lport);
  struct sock *s;
  
  for(s = stable.sock; s < &stable.sock[NSOCK]; s++){
    if(s->state == CLOSED){
      s->localport = lport;
      s->state = LISTENING;
      s->remoteport = 5;
      s->owner = myproc()->pid;
      break;
    }
  }
  stable.nsockets++;
  release(&stable.lock);
  return 0;

}

int
connect(int rport, const char* host) {
  
  if(stable.nsockets > NSOCK)
    return E_FAIL;

  struct sock *s;
  acquire(&stable.lock);

  int serverrp=-1;

  for(s = stable.sock; s < &stable.sock[NSOCK]; s++){
    if(s->localport == rport && s->state == LISTENING){
      serverrp = s->remoteport;
      s->state = CONNECTED;
      break;
    }
  }
  if(serverrp == -1)
    return E_NOTFOUND;

  for(s = stable.sock; s < &stable.sock[NSOCK]; s++){
    if(serverrp != -1 && s->state == CLOSED){
      s->localport = serverrp;
      s->remoteport = rport;
      s->state = CONNECTED;
      s->owner = myproc()->pid;
      break;
    }
  }
  cprintf("Client>>Connected to server at remote : %d\nClient>>localport: %d\n",rport,serverrp);
  stable.nsockets++;
  release(&stable.lock);
  return serverrp;

}

int
send(int lport, const char* data, int n) {
  
  struct sock *s;
  struct sock *dst;
  
  acquire(&stable.lock);
  int flag = -1;
  for(s = stable.sock; s < &stable.sock[NSOCK]; s++){
    if(s->localport == lport){
      flag = 0;
      break;
    }
  }
  if(flag == -1)
    return E_NOTFOUND;

  flag = -1;// Not found flag
  for(dst = stable.sock; dst < &stable.sock[NSOCK]; dst++){
    if(dst->localport == s->remoteport){
      flag = 0;
      break;
    }
  }
  if(flag == -1)
    return E_NOTFOUND;

  if(myproc()->pid != s->owner)
    return E_ACCESS_DENIED;
  
  if(s->state != CONNECTED)
    return E_WRONG_STATE;
  
  // cprintf("Sending data len: %d to %d\n",n, dst->localport);
  int len = strlen(dst->buf);
  
  if(len == 0){
    strncpy(dst->buf , data , n);
    wakeup(dst);
  }
  else{
    cprintf("Buffer already has data: %d\n",len);
    sleep(s,&stable.lock);
    strncpy(dst->buf , data , n);
  }
  
  // cprintf("data send done\n");
  release(&stable.lock);

  return 0;
}


int
recv(int lport, char* data, int n) {
 
  struct sock *s;
  struct sock *dst;

  acquire(&stable.lock);
  // cprintf("\nRecving at port-> %d\n",lport);
  int flag = -1;
  for(s = stable.sock; s < &stable.sock[NSOCK]; s++){
    if(s->localport == lport){
      flag = 0;
      break;
    }
  }
  if(flag == -1)
    return E_NOTFOUND;

  flag = -1;
  for(dst = stable.sock; dst < &stable.sock[NSOCK]; dst++){
    if(dst->localport == s->remoteport){
      flag = 0;
      break;
    }
  }
  if(flag == -1)
    return E_NOTFOUND;

  if(myproc()->pid != s->owner)
    return E_ACCESS_DENIED;
  if(s->state != CONNECTED)
    return E_WRONG_STATE;
  
// CHECK:
  int len = strlen(s->buf);
  if(len == 0 ){//No data in buffer. wait for rec

    // cprintf("No data in buffer. waiting... %d\n",s->localport);
    sleep(s,&stable.lock);
    
    // goto CHECK;
    
    len = strlen(s->buf);
    data[0] = '\0';
    strncpy(data, s->buf , len);
    
    for(int i = 0; i < n; i++)
    {
      s->buf[i] = '\0';
    }
    
  }
  else{
    
    strncpy(data, s->buf , len);
    for(int i = 0; i < n; i++)
    {
      s->buf[i] = '\0';
    }
    wakeup(dst);

  }

  release(&stable.lock);
  return 0;
}

int
disconnect(int lport) {
  //
  // TODO: Put the actual implementation of disconnect here.
  //
  // socket state close
  struct sock *s;
  acquire(&stable.lock);
  for(s = stable.sock; s < &stable.sock[NSOCK]; s++){
    if(s->localport == lport && s->state == CONNECTED){
      s->state = CLOSED;
      s->localport = -1;
      s->remoteport = -1;
      memset(&s->buf[0], 0, sizeof(s->buf));
      break;
    }
  }
  cprintf("Closing socket at port %d..\n",lport);
  stable.nsockets--;
  release(&stable.lock);

  return 0;
}
