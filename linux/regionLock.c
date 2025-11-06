#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

const char *testfile = "/tmp/test_file";

int main(int argc, char *argv[]) {
  int file_desc;
  int byte_count;
  char *data = "A";
  struct flock region_1, region_2;
  int res;
  file_desc = open(testfile, O_RDWR | O_CREAT, 0644);
  if (file_desc == -1) {
    perror("testfile open failed");
    exit(1);
  }

  for (byte_count = 0; byte_count < 100; byte_count++) {
    write(file_desc, data, 1);
  }
  // 共享锁
  region_1.l_type = F_RDLCK;
  region_1.l_whence = SEEK_SET;
  region_1.l_start = 10; // 开始的字节数
  region_1.l_len = 20;

  // 独占锁
  region_2.l_type = F_WRLCK;
  region_2.l_whence = SEEK_SET;
  region_2.l_start = 40;
  region_2.l_len = 10;

  printf("加锁成功, 进程号%d\n", getpid());
  if ((res = fcntl(file_desc, F_SETLK, &region_1)) == -1) {
    fprintf(stderr, "failed to lock region_2\n");
  }
  if ((res = fcntl(file_desc, F_SETLK, &region_2)) == -1) {
    fprintf(stderr, "failed to lock region_2\n");
  }
  sleep(60);
  close(file_desc);
  exit(0);

  return 0;
}
