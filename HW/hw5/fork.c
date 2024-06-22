//使用chatGPT生成

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_george() {    // 每隔一秒鐘印出一次 George 的函數
  while (1) {    
    printf("George\n");    
    sleep(1);    
  }    
}    

void print_mary() {     // 每隔2秒鐘印出一次 Mary 的函數
  while (1) {    
    printf("Mary\n");    
    sleep(2);    
  }    
}    

int main() {     // 主程式開始
  pid_t pid1, pid2;

  pid1 = fork();  // 創建第一個子進程
  if (pid1 == 0) {
    // 子進程1 執行 print_george 函數
    print_george();
    exit(0);  // 子進程完成後退出
  }

  pid2 = fork();  // 創建第二個子進程
  if (pid2 == 0) {
    // 子進程2 執行 print_mary 函數
    print_mary();
    exit(0);  // 子進程完成後退出
  }

  while (1) {     // 主程式每隔一秒鐘
    printf("----------------\n");    // 就印出分隔行
    sleep(1);     // 停止一秒鐘
  }    

  // 等待所有子進程結束
  wait(NULL);
  wait(NULL);

  return 0;    
}
