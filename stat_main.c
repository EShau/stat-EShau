#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>

void printFileSize(off_t size);
void makeMode(char mode, char modes[11]);
void printFilePermissions(mode_t mode);
void printLastFileAccessTime(time_t time);

void printFileSize(off_t size){
  printf("File size: ");
  double billion = pow(10, 9);
  double million = pow(10, 6);
  double thousand = pow(10, 3);
  if (size > billion){
    printf("%.3lf GB", size / billion);
  }
  else if (size > million){
    printf("%.3lf MB", size / million);
  }
  else if (size > thousand){
    printf("%.3lf KB", size / thousand);
  }
  else{
    printf("%d B", size);
  }
  printf("\n");
}

void makeMode(char mode, char modes[11]){
  int i;
  for (i = 2; i >= 0; i--){
    if (mode>>i & 1){
      if (i == 2){
        strcat(modes, "r");
      }
      else if (i == 1){
        strcat(modes, "w");
      }
      else{
        strcat(modes, "x");
      }
    }
    else{
      strcat(modes, "-");
    }
  }
}

void printFilePermissions(mode_t mode){
  int actual_permissions = mode & 511;
  char modes[11];
  strcat(modes,"-");
  int i;
  for (i = 2; i >= 0; i--){
    makeMode(actual_permissions>>(i * 3) & 7, modes);
  }
  printf("File Permissions: %s\n", modes);
}

void printLastFileAccessTime(time_t time){
  struct tm * time_a = localtime(& time);
  printf("Time of Last Access: %s\n", asctime(time_a));
}

int main(){
  struct stat buffer;
  printf("Attempting to analyze my own file Sudoku-Naive-Times.txt...\n");
  int status = stat("Sudoku-Naive-Times.txt", &buffer);
  if (status == 0){
    printf("Success!\n");
    printFileSize(buffer.st_size);
    printFilePermissions(buffer.st_mode);
    printLastFileAccessTime(buffer.st_atime);
  }
  else{
    printf("Failure: %s",strerror(errno));
  }
  return 0;
}