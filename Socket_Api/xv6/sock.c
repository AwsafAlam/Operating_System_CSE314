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
      s->remoteport = 1;
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
  cprintf("Connected to server at remote : %d\n",rport);

  release(&stable.lock);
  return s->state;

}

int
send(int lport, const char* data, int n) {
  //
  // TODO: Put the actual implementation of send here.
  //
  // struct sock *s;
  // while(s->dataPresent); // blocking call outside mutex
  // acquire(&stable.lock);
  // cprintf("Sending data.--> %d; port->%d\n",n,lport);
  // for(int i = 0; i < n; i++ )
  // {
  //   //cprintf("Send - |%d|\n",data[i]);
  //   s->buf[i] = data[i];
  //   i++;
  // }
  // s->dataPresent = 1;
  // release(&stable.lock);

  return 0;
}


int
recv(int lport, char* data, int n) {
  //
  // TODO: Put the actual implementation of recv here.
  //
  //cprintf("\ninside rec\n");
  // struct sock *s;
  // while(!s->dataPresent); // blocking call outside mutex
  // acquire(&stable.lock);
  // cprintf("\nRecv data len--> %d , port-> %d\n",n,lport);
  // // for(int i = 0; i < n; i++ )
  // // {
  // //   cprintf("Rec - %s\n",data[i]);
  // //   data[i] = 'a';

  // // }
  // int i = 0;
  // while(s->buf[i] != '\0'){
  //   //cprintf("Rec - %s\n",s->buf[i]);
  //   // data[i] = 'a';
  //   data[i] = s->buf[i];
  //   //strncpy(data , s->buf);
  //   i++;
  // }
  // s->buf[0]='\0';
  // s->dataPresent = 0;
  // release(&stable.lock);
  return 0;
}

int
disconnect(int lport) {
  //
  // TODO: Put the actual implementation of disconnect here.
  //
    // socket state close
  return 0;
}
