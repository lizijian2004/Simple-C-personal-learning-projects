#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  pid = fork();
  signal(SIGCHLD, SIG_IGN); // 交给OS处理(init进程为子进程收尸)
  if (pid < 0) {
    perror("fork failed");
    exit(-1);
  }
  if (pid == 0) {
    sleep(100); // 父进程睡100秒, 期间子进程即使
    printf("father pid is ");
  } else {
    printf("child pid is ");
  }
  printf("%d", getpid());
  return 0;
}
