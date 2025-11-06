#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void inum_to_iname(ino_t, char *, int);
void printpath(ino_t);
ino_t get_inode(char *);

int main(int argc, char *argv[]) {
  printpath(get_inode("."));
  putchar('\n');
  return 0;
}

void inum_to_iname(ino_t find_inode, char *name, int size) {
  DIR *dirp;
  struct dirent *dp;

  dirp = opendir(".");
  if (dirp == NULL) {
    perror("opendir error");
    exit(1);
  }

  while ((dp = readdir(dirp)) != NULL) {
    if (dp->d_ino == find_inode) {
      strncpy(name, dp->d_name, size - 1);
      name[size - 1] = '\0'; // 确保字符串终止
      closedir(dirp);
      return;
    }
  }
  fprintf(stderr, "inode not found\n");
  exit(1);
}

ino_t get_inode(char *name) {
  struct stat info;
  if (stat(name, &info) == -1) {
    perror("stat error");
    exit(1);
  }
  return info.st_ino;
}

void printpath(ino_t this_inode) {
  ino_t parent_inode;
  char name[256];

  if (this_inode == get_inode("..")) {
    return;
  }
  if (chdir("..") == -1) {
    perror("chdir error");
    exit(1);
  }
  parent_inode = get_inode(".");
  printpath(parent_inode);
  inum_to_iname(this_inode, name, sizeof(name));
}
