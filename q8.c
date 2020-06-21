#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
The parent is sending the message through the created pipe
 using file descriptor[4](fd[1]) while
child is listening through the pipe using file descriptor[3](fd[0])
and then printing out the message of the sent message.
 **/


int main(){
  int fd[2];
  pipe(fd);
  int n;
  int process1 = fork();
  char line[100];


  if(process1 < 0){
    printf("ERROR");
    exit(0);

}


  else if(process1 == 0){

    int process2 = fork();

    if(process2 < 0){printf("ERROR"); exit(1);}

    else if(process2 == 0){}

    else{
      close(fd[1]);
      n = read(fd[0],line,100);
      printf("%s",line);
}
  }
  else{
    close(fd[0]);
    write(fd[1],"Luke, I am your father!\n",100);
  }





  return 0;
}
