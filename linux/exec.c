#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *shell[] = {"/bin/ls", "-l", NULL};
  if (execve("/bin/ls", shell, NULL) == -1) {
    perror("EXECVE");
    exit(-1);
  }
  puts("不会运行到这里, 因为ls数据段和代码段被加载");
  return 0;
}
