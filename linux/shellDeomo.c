#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXSIZE 20
#define MAXLENG 512

int execute(char *shell[]);
char *makeString(char *string);

int main(int argc, char *argv[]) {
  char *shell[MAXSIZE + 1];
  int index_of_shell = 0;
  char string[MAXLENG] = "";
  while (index_of_shell < MAXSIZE) {
    if (fgets(string, MAXLENG, stdin) && *string != '\n') {
      shell[index_of_shell++] = makeString(string);
    } else if (index_of_shell > 0) {
      shell[index_of_shell] = NULL;
      execute(shell);
      index_of_shell = 0;
    }
  }
  return 0;
}

int execute(char *shell[]) {
  pid_t pid = fork();
  int status;
  switch (pid) {
  case -1:
    perror("fork failed");
    exit(1);
  case 0:
    execvp(shell[0], shell);
    perror("execvp failed");
  default:
    if (waitpid(pid, &status, 0) == -1) {
      perror("waitpid failed");
      exit(1);
    }
    printf("Over\n");
  }
  // execvp(shell[0], shell);
  // perror("execvp failed"); // 如果成功不会运行到这里
  // exit(1);
}

char *makeString(char *string) {
  char *cp = NULL;
  string[strlen(string) - 1] = '\0';
  cp = (char *)malloc(strlen(string) + 1);
  if (cp == NULL) {
    perror("malloc fail");
    exit(1);
  }
  strcpy(cp, string);
  return cp;
}
