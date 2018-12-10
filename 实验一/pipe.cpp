#include<unistd.h>
#include<iostream>
#include<stdio.h> 
#include<stdlib.h> 
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string> 
using namespace std;
//typedef void (*sighandler_t)(int);
//sighandler_t signal(int signum, sighandler_t handler);
pid_t p1;
pid_t p2;
int fd[2];
void my_func(int sig_no);
void fp1();
void fp2();
void fp1_func(int sig_no);
void fp2_func(int sig_no);
void my_func(int sig_no)
{
	if(sig_no == SIGINT) 
	{ printf("Receive SIGINT.\n"); 
		kill(p1,SIGUSR1);
		kill(p2,SIGUSR2);
	}
}
void fp1()
{
	int count=0;	

	if(signal(SIGINT, (void (*)(int))1) == SIG_ERR) 
	printf("can't catch SIGINT.\n'"); 		
	if(signal(SIGUSR1, fp1_func) == SIG_ERR) 
	printf("can't catch SIGUSR1.\n'"); 
	while(1){
        close(fd[0]);  
	string w="I send you ";
	w=+count;
	w=+" times";
//	write(fd[1], w.c_str(), w.size());
	write(fd[1], &count, sizeof(int));
//        printf("I send you %d times\n",count);
		count++;
		sleep(1);
	}
}
void fp2()
{	
	char r[18];
	int count;
	if(signal(SIGINT, (void (*)(int))1) == SIG_ERR) 
	printf("can't catch SIGINT.\n'"); 		
	if(signal(SIGUSR2, fp2_func) == SIG_ERR) 
	printf("can't catch SIGUSR2.\n'"); 
	while(1){
        close(fd[1]);  
        if(read(fd[0],&count,sizeof(int)))
		printf("I send you %d times\n",count);
//        read(fd[0],r,18);
//		printf("%s\n",r);
	}	
}
void fp1_func(int sig_no)
{
	if(sig_no == SIGUSR1) 
	{ printf("Child Process 1 is Killed by Parent! \n"); 
        close(fd[1]);  		
		exit(0);
	}
}
void fp2_func(int sig_no)
{
	if(sig_no == SIGUSR2) 
	{ printf("Child Process 2 is Killed by Parent! \n"); 
        close(fd[0]);  		
		exit(0);
	}
}

int main()
{
	pipe(fd);
	int status1,status2;
	pid_t t1;
	pid_t t2;
	p1=fork();   

	if (p1 == 0) { 
	puts("sub1 created\n"); 
	fp1();
	 }
	else {
	p2=fork();
	if (p2 == 0) { 
	puts("sub2 created\n");
	fp2();
	  }      
	else {
	if(signal(SIGINT, my_func) == SIG_ERR) 
	printf("can't catch SIGUSR1.\n'"); 	
	t1=waitpid(p1,&status1,0);          
	t2=waitpid(p2,&status2,0);    
	close(fd[1]);
	close(fd[0]);
	printf("Parent Process is Killed!\n"); 		
	}
	}
	return 1;
} 

