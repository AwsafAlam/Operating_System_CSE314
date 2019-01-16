# Offline 1 Adding new SYsytem call

1. Create a new system call in xv6 with the following specifications:

  a. Name of the system call will be your firstname_lastname
  b. The system call will print your name and date of birth
  c. The system call will return your student id
2. Create a user program in xv6 that will call your newly added system call
3. From xv6 shell, run the user program

# syscall.h
 #define awsaf_alam 32

# defs.h

//proc.c

int awsaf_alam(void);

# user.h
int awsaf_alam(void);

# sysproc.c

int
sys_awsaf_alam(void)
{
  return awsaf_alam();
}

# usys.c

SYSCALL(awsaf_alam())

# syscall.c

extern int sys_awsaf_alam(void);

[SYS_awsaf_alam] sys_awsaf_alam

# proc.c

int
awsaf_alam(void)
{
  return 1505114;
}

# roll.c

- First create a new user program

#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    printf(1, "%d\n",awsaf_alam());
    // awsaf_alam();
    exit();
}

modify the makefile

- add _roll to UPROGS
- add roll.c to EXTRA
  
make
sudo apt-get install qemu
make qemu