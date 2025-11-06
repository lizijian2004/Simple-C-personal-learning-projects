#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
  char buf[10];
  int fd, i, j, n;
  fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
  if (fd < 0) {
    perror("open /dev/tty failed");
    exit(1);
  }

  for (i = 0; i < 5; i++) {
    n = read(fd, buf, 10);
    if (n >= 0)
      break;
    if (errno != EAGAIN) {
      perror("open /dev/tty failed");
      exit(1);
    }
    sleep(6);
    write(STDOUT_FILENO, "please try again\n", strlen("please try again\n"));
  }
  if (i == 5)
    write(STDOUT_FILENO, "timeout\n", strlen("timeout\n"));
  else {
    write(STDOUT_FILENO, buf, n);
    printf("YOU HAVE BEEN WRITE\n");
  }
  return 0;
}
