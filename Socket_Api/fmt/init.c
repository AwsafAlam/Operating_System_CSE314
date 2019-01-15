8550 // init: The initial user-level program
8551 
8552 #include "types.h"
8553 #include "stat.h"
8554 #include "user.h"
8555 #include "fcntl.h"
8556 
8557 char *argv[] = { "sh", 0 };
8558 
8559 int main(void)
8560 {
8561   int pid, wpid;
8562 
8563   if(open("console", O_RDWR) < 0){
8564     mknod("console", 1, 1);
8565     open("console", O_RDWR);
8566   }
8567   dup(0);  // stdout
8568   dup(0);  // stderr
8569 
8570   for(;;){
8571     printf(1, "init: starting sh\n");
8572     pid = fork();
8573     if(pid < 0){
8574       printf(1, "init: fork failed\n");
8575       exit();
8576     }
8577     if(pid == 0){
8578       exec("sh", argv);
8579       printf(1, "init: exec sh failed\n");
8580       exit();
8581     }
8582     while((wpid=wait()) >= 0 && wpid != pid)
8583       printf(1, "zombie!\n");
8584   }
8585 }
8586 
8587 
8588 
8589 
8590 
8591 
8592 
8593 
8594 
8595 
8596 
8597 
8598 
8599 
