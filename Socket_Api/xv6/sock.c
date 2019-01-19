#include "types.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "sock.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"

//
// TODO: Create a structure to maintain a list of sockets
// Should it have locking?
//
struct {
  struct spinlock lock;
  struct sock sock[NSOCK];
} stable;


void
sinit(void)
{
  //
  // TODO: Write any initialization code for socket API
  // initialization.
  //
  initlock(&stable.lock, "stable");
  //s = stable.sock;
}

// Allocate a file structure.
struct sock*
sockalloc(void)
{
  struct sock *f;

  acquire(&stable.lock);
  for(f = stable.sock; f < stable.sock+ NSOCK; f++){
//    if(f->ref == 0){
//      f->ref = 1;
//      release(&ftable.lock);
//      return f;
//    }
  }
  release(&stable.lock);
  return 0;
}

int
listen(int lport) {

  //
  // TODO: Put the actual implementation of listen here.
  //
 
  acquire(&stable.lock);
  cprintf("Listening at %d\n",lport);
  struct sock *s;
  // struct sock *server;
  for(s = stable.sock; s < &stable.sock[NSOCK]; s++){
    if(s->state == CLOSED){
      s->localport = lport;
      s->state = LISTENING;
      s->remoteport = 5;
      break;
    }
  }
  
  release(&stable.lock);
  return s->state;

}

int
connect(int rport, const char* host) {
  //
  // TODO: Put the actual implementation of connect here.
  //
  struct sock *s;
  //struct sock *client;
  acquire(&stable.lock);

  int serverrp=-1;

  for(s = stable.sock; s < &stable.sock[NSOCK]; s++){
    if(s->localport == rport && s->state == LISTENING){
      serverrp = s->remoteport;
      s->state = CONNECTED;
      break;
    }
  }
  
  for(s = stable.sock; s < &stable.sock[NSOCK]; s++){
    if(serverrp != -1 && s->state == CLOSED){
      s->localport = serverrp;
      s->remoteport = rport;
      s->state = CONNECTED;
      break;
    }
  }
  cprintf("Client>>Connected to server at remote : %d\nClient>>localport: %d\n",rport,serverrp);

  release(&stable.lock);
  return serverrp;

}

int
send(int lport, const char* data, int n) {
  //
  // TODO: Put the actual implementation of send here.
  //
  struct sock *s;
  struct sock *dst;

  acquire(&stable.lock);
  for(s = stable.sock; s < &stable.sock[NSOCK]; s++){
    if(s->localport == lport){
      break;
    }
  }
  for(dst = stable.sock; dst < &stable.sock[NSOCK]; dst++){
    if(dst->localport == s->remoteport){
      break;
    }
  }
  
  // cprintf("Sending data len: %d to %d\n",n, dst->localport);
  int len = strlen(dst->buf);
  
  if(len == 0){
    strncpy(dst->buf , data , n);
    wakeup(dst);
  }
  else{
    cprintf("Buffer already has data: %d\n",len);
  }
  
  // cprintf("data send done\n");
  release(&stable.lock);

  return 0;
}


int
recv(int lport, char* data, int n) {
  //
  // TODO: Put the actual implementation of recv here.
  //
  struct sock *s;
  // struct sock *dst;

  acquire(&stable.lock);
  // cprintf("\nRecving at port-> %d\n",lport);
  for(s = stable.sock; s < &stable.sock[NSOCK]; s++){
    if(s->localport == lport){
      break;
    }
  }
  // for(dst = stable.sock; dst < &stable.sock[NSOCK]; dst++){
  //   if(dst->localport == s->remoteport){
  //     break;
  //   }
  // }
  
// CHECK:
  int len = strlen(s->buf);
  if(len == 0 ){//No data in buffer. wait for rec

    // cprintf("No data in buffer. waiting... %d\n",s->localport);
    sleep(s,&stable.lock);
    // cprintf("Wakeup from sleep\n");
    // goto CHECK;
    
    // cprintf("Data: \"%s\"\n",data);
    // cprintf("Kernel Buffer: \"%s\"\n",s->buf);

    len = strlen(s->buf);
    data[0] = '\0';
    strncpy(data, s->buf , len);
    // cprintf("Data received, len : %d\n",len);
    // strncpy(s->buf, "" , 0);
    
    for(int i = 0; i < n; i++)
    {
      s->buf[i] = '\0';
    }
    
  }
  else{
    // cprintf("Data: \"%s\"\n",data);
    // cprintf("%d-Kernel Buffer: \"%s\"\n",len,s->buf);
    strncpy(data, s->buf , len);
    // strncpy(s->buf, "" , 0);
    for(int i = 0; i < n; i++)
    {
      s->buf[i] = '\0';
    }

    // cprintf("Data received, len : %d\n",len);
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
      break;
    }
  }
  cprintf("Closing socket");

  release(&stable.lock);

  return 0;
}
