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

struct sock *s;

void
sinit(void)
{
  //
  // TODO: Write any initialization code for socket API
  // initialization.
  //
  initlock(&stable.lock, "stable");
  s = stable.sock;
}

int
listen(int lport) {

  //
  // TODO: Put the actual implementation of listen here.
  //
  /// Lock s taable
  /// Listen call by server
  // choose socket in remote host
  /// state.listen

  /// assign arbitaary remote port to a socket;
  // In 10- arr indx of stable
  //  stable.sock[10].remoteport = 10;
  /// unlock
  acquire(&stable.lock);
  cprintf("Listening at \n",lport);
    
  // s = stable.sock;
  s->localport = lport;
  s->state = LISTEN;
  //sock.localport = lport;
  //sock.st.LISTEN;
  release(&stable.lock);
  return s->state;

}

int
connect(int rport, const char* host) {
  //
  // TODO: Put the actual implementation of connect here.
  //
  acquire(&stable.lock);

  // remote port
  ///listen
  cprintf("Connecting\n");
  // s= stable.sock;
  s->remoteport = rport;
  s->state = CONNECT;
  release(&stable.lock);
  return s->localport;

}

int
send(int lport, const char* data, int n) {
  //
  // TODO: Put the actual implementation of send here.
  //
  while(s->dataPresent); // blocking call outside mutex
  acquire(&stable.lock);
  cprintf("Sending data.--> %d; port->%d\n",n,lport);
  for(int i = 0; i < n; i++ )
  {
    //cprintf("Send - |%d|\n",data[i]);
    s->buf[i] = data[i];
    i++;
  }
  s->dataPresent = 1;
  release(&stable.lock);
  
  return 0;
}


int
recv(int lport, char* data, int n) {
  //
  // TODO: Put the actual implementation of recv here.
  //
  //cprintf("\ninside rec\n");
  while(!s->dataPresent); // blocking call outside mutex
  acquire(&stable.lock);
  cprintf("\nRecv data len--> %d , port-> %d\n",n,lport);
  // for(int i = 0; i < n; i++ )
  // {
  //   cprintf("Rec - %s\n",data[i]);
  //   data[i] = 'a';

  // }
  int i = 0;
  while(s->buf[i] != '\0'){
    //cprintf("Rec - %s\n",s->buf[i]);
    // data[i] = 'a';
    data[i] = s->buf[i];
    //strncpy(data , s->buf);
    i++;
  }
  s->buf[0]='\0';
  s->dataPresent = 0;
  release(&stable.lock);
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
