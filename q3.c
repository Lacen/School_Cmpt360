#include <stdio.h>
#include <stdlib.h>

/*
Yes you can have the child always print first without using wait.
You simply just have to delay the parent process from running using 
call such as Sleep/Usleep() 

 */
int main(){

  int process = fork();

  if(process < 0){
    printf("Error");
    exit(0);

  }else if (process == 0){
      printf("Hello\n");

    }else{
    // using usleep here will allow the child proces to finish before the parent
    usleep(100);
      printf("Goodbye\n");
      
}









  return 0;

}
