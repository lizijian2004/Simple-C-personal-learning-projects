#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  pid = fork();
  if (pid < 0) {
    perror("fail to create");
    exit(-1);
  }
  if (pid == 0)
    printf("this is children");
  else {
    printf("this is parent");
    sleep(1);
  }
  printf(" %d\n", getpid());
  return 0;
}
