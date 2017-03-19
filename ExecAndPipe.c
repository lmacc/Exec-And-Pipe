#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

//Leslie McCarthy DNET 3

int main(){

 pid_t pid = getpid();
 pid_t childpid, childpid2;
 int c1Toc2[2];
 pipe(c1Toc2);
 
 
 printf("STARTING PROCESS PID %d\n",pid);

 // Add the code for the two children here
  
    childpid = fork();
   
 
    if (childpid < 0){
        perror("fork failed");
        exit(-1);
    }
    
    else if (childpid == 0){
       
        dup2(c1Toc2[1], STDOUT_FILENO);
        close(c1Toc2[0]);
        execlp("ps", "ps", "-ef",(char *)0);       
        exit(0);
    }
    
    
    
    else {//Parent process       
      
        childpid2 = fork();
        if (childpid2 < 0){
            perror("fork failed for child 2");
            exit(-1);
        }
        
        else if (childpid2 == 0){                
            dup2(c1Toc2[0], STDIN_FILENO);
            close(c1Toc2[1]);
            execlp("grep","grep","init", (char *)0);           
            exit(0);
        }      
         
    }
    
    close(c1Toc2[0]);
    close(c1Toc2[1]);
    
    for(int i = 0; i < 2; i++)//Wait for the two children to finish
        wait(NULL);
           
    printf("\nPARENT: PROCESS Waiting on children to complete\n");    
    
    printf("\nFinal Print Statement before exit\n");
       
        
 exit(0);
 
}