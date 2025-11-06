#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

const char *testfile = "/tmp/test_file";
#define readsize 5

void show(struct flock *show_lock);

int main(int argc, char *argv[]) {
  int file_desc, res;
  struct flock region_to_test;
  file_desc = open(testfile, O_RDWR | O_CREAT, 0666);
  if (file_desc == -1) {
    fprintf(stderr, "open failed");
    exit(1);
  }
  for (int start_byte = 0; start_byte < 99; start_byte += readsize) {
    region_to_test.l_type = F_WRLCK;
    region_to_test.l_whence = SEEK_SET;
    region_to_test.l_start = start_byte;
    region_to_test.l_len = readsize;
    // 因为操作系统分配的pid不可能为负数, 因此必定是人为赋值
    region_to_test.l_pid = -1;

    printf("F_WRLCK start from %d to %d", start_byte,
           start_byte + readsize); // 输出信息
    // 检查锁信息
    res = fcntl(file_desc, F_GETLK, &region_to_test);
    if (res == -1) {
      perror("F_GETLK failed");
      exit(1);
    }

    if (region_to_test.l_pid == -1) {
      printf("F_WRLCK Success\n");
    } else {
      printf("F_WRLCK Failed\n");
      show(&region_to_test);
    }

    region_to_test.l_type = F_RDLCK;
    region_to_test.l_whence = SEEK_SET;
    region_to_test.l_start = start_byte;
    region_to_test.l_len = readsize;
    // 因为操作系统分配的pid不可能为负数, 因此必定是人为赋值
    region_to_test.l_pid = -1;
    printf("F_RDLCK start from %d to %d", start_byte,
           start_byte + readsize); // 输出信息
    // 尝试加锁
    res = fcntl(file_desc, F_GETLK, &region_to_test);
    if (res == -1) {
      perror("F_GETLK failed");
      exit(1);
    }
    if (region_to_test.l_pid == -1) {
      printf("F_RDLCK Success\n");
    } else {
      printf("F_RDLCK Failed\n");
      show(&region_to_test);
    }
  }
  close(file_desc);
  exit(0);
}

void show(struct flock *show_lock) {
  printf("l_type is %d\n", show_lock->l_type);
  printf("l_whence is %d\n", show_lock->l_whence);
  printf("l_start is %ld\n", show_lock->l_start);
  printf("l_len is %ld\n", show_lock->l_len);
}
