#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Both the parent and the child has a local copy of the variable "X" when fork
// is called therefore any changes to X will only affect the local and not the 
// others process variable of x
int main(){
  
  int x = 100;
  printf("This is x before fork is called x:%d\n",x);

  int process = fork();


  if(process < 0){
    printf("Error");
    exit(0);
}
  else if(process == 0) {
    
    printf("This is the child process %d\n",getpid());
    printf("This is x for child(preincrement) x:%d\n",x);
    x= x+2;
    printf("this is the x for child(postincrement) x:%d\n",x);
}

  else{
    printf("this is the parent process %d\n",getpid());
    printf("this is x for the parent(Preincremented) x:%d \n",x);
    x= x+3;
    printf("this is the x for parent(postincremented) x:%d\n",x);
}


  printf("this is x:%d\n",x);
  
  return 0;
}
