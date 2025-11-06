#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd1 = -1;
  printf("stdin fd is %d\n", fileno(stdin));
  printf("stdout fd is %d\n", fileno(stdout));
  printf("stderr fd is %d\n", fileno(stderr));

  if ((fd1 = open("./temp.txt", O_RDONLY)) == -1) {
    perror("open failed\n");
    exit(1);
  }
  printf("new fd is %d\n", fd1);
  return 0;
}
