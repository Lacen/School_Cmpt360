#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
When you close the stdout_fileno file descriptor
The file connection to the terminal  is terminate thus
nothing will be printed out to the terminal
therefore child will have nothing printed out
 **/

int main(){

  int process = fork();

  if(process < 0){
    printf("ERROR");
    exit(0);

}
  else if(process == 0){
    close(STDOUT_FILENO);
    printf("Hello i am child");


}
  else{
   



}




  return 0;
}
