
//
// TODO: Define an enumeration to represent socket state.
//
enum socstate { CLOSED, LISTENING, CONNECTED };
//
// TODO: Define a structure to represent a socket.
//
struct sock {

  int localport;
  int remoteport;

  int owner;
  char buf[128];
  int dataPresent;

  enum socstate state;        // Socket state
};
