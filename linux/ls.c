#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void do_ls(char dirname[]);
void printTime(time_t tm);
int main(int argc, char *argv[]) {
  struct stat sb;
  if (argc < 2)
    fprintf(stderr, "Please enter one filename");
  else if (stat(argv[1], &sb) != -1) {
    printf("  model:%d\n", sb.st_mode);
    printf("  user:%d\n", sb.st_uid);
    printTime(sb.st_mtime);
  }

  //  if (argc == 1) {
  //    do_ls(".");
  //  } else
  //    while (--argc) {
  //      printf("%s\n", *++argv);
  //      do_ls(*argv);
  //    }
  return 0;
}

void do_ls(char dirname[]) {
  DIR *p_DIR;
  struct dirent *p_dirent;

  if ((p_DIR = opendir(dirname)) == NULL) {
    fprintf(stderr, "ls: cannot open");
  } else {
    while ((p_dirent = readdir(p_DIR)) != NULL) {
      printf("%s\n", p_dirent->d_name);
    }
    closedir(p_DIR);
  }
}
void printTime(time_t tm) {
  char buf[100];
  struct tm day;
  day = *localtime(&tm);
  strftime(buf, 100, "%Y-%m-%d,%H:%M:%S", &day);
  printf("%s\n", buf);
}
