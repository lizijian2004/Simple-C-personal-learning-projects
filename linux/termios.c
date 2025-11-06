#include <stdio.h>
#include <stdlib.h>
#include <sys/termios.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

int print_message();
void set_model(); // 设置当前tty的模式
void tty_mode(int);

int main(int argc, char *argv[]) {
  int res;
  tty_mode(0); // 保存当前tty模式
  set_model();
  res = print_message();
  tty_mode(1); // 恢复tty模式
  return 0;
}

int print_message() {
  char ch;
  printf("如果要退出请按q\n");
  while (1) {
    switch (ch = getchar()) {
    case 'q':
    case 'Q':
      return 0;
    case EOF:
      return -1;
    default:
      printf("请继续\n");
    }
  }
}

void set_model() {
  struct termios info;
  tcgetattr(0, &info);
  info.c_lflag &= ~ICANON;
  info.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &info);
}

void tty_mode(int how) {
  struct termios info;
  if (how == 0)
    tcgetattr(how, &info);
  else
    tcsetattr(how, TCSANOW, &info);
}
