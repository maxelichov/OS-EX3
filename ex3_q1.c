
#define _CRT_SECURE_NO_WARNINGS
#define MAX_ROW_SIZE 80
#define STDOUT 1
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <string.h>


/*void do_same_as_last_ex()
{


	do_stdin_redirection(my_argv[1]);
	
	if(fork() == 0)
	{
		my_argv[1] = argv[2];
		
		if(execv(my_argv[0], my_argv) < 0)
		{
		
			fprintf(stderr,"execv failed...terminating the program");
			exit(2);
		}
	}
	
	
	wait(NULL);
	
	//for(int i = 3; i < argc -1; i++)
	{
		
		do_stdin_redirection(my_argv[2]);
		my_argv[1] = argv[i];
		
		if(fork() == 0)
		{				  
			if(execv(my_argv[0], my_argv) < 0)
			{
				fprintf(stderr,"execv failed...terminating the program");
				exit(2);
			}
		}
			
		wait(NULL);
	}

}*/



int open_file(char* input_file)
{
  int fd;
  fd = open(input_file, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd < 0)  // open failed
  {
    fprintf(stderr, "ERROR: open \"%s\" failed (%d). Exiting\n", input_file, fd);
    exit(2);
  }
  //fprintf(stderr, "opened file %s, file descriptor is: %d\n",input_file, fd);
  return(fd);
}


void clean_if_file_exists(char* file_name)
{
	remove(file_name);
}


void do_stdin_redirection(char* first_file)
{

	close(0);
	int fd_stdin = open_file(first_file);
	dup2(0, fd_stdin);
}


int do_stdout_redirection(char* first_file)
{
	close(1);
	int fd_stdout = open_file(first_file);
	dup2(1, fd_stdout);
	return fd_stdout;
}

void redirect_stdin_to_read_end(int read_end_of_pipe)
{
	
	dup2(read_end_of_pipe,0); // now stdin point to pp[0]

}


void sigpipe_handler(int dummy)
{
 fprintf(stderr, "****** ===========> Got SIGPIPE *****\n");
}


void close_pipe_ends(int fd, int end)
{	

	int res;
	if(end == 0)
	{
		res = close(fd);
		if(res < 0)
		{
			fprintf(stderr,"120: failed to close reading end\n");
		}				
	}

	if(end == 1)
	{
		res = close(fd);
		if(res < 0)
		{
			fprintf(stderr,"129: failed to close writing end\n");
		}				
	}


}


char* my_argv[2];

int main(int argc, char* argv[])
{
	int saved_stdout = dup(1);
	int saved_stdin = dup(0);
	
	/*struct sigaction pipe_action = {0}; // set all members to NULL
 	pipe_action.sa_handler = sigpipe_handler;
 	sigaction(SIGPIPE, &pipe_action, NULL);*/
	
	
	clean_if_file_exists(argv[argc-1]);			
	my_argv[0] =  "merger";
	my_argv[1] = argv[2];
	
	
	int fd = open(argv[argc-1], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	
	if (fd < 0)  // open failed
  	{
 	   fprintf(stderr, "ERROR: open \"%s\" failed (%d). Exiting\n", argv[argc-1], fd);
  	  exit(2);
 	}
	
	
	printf("argc == %d\n", argc);
		
	if(argc <= 2) /*should be at least ./ex2_q1 in1 merged*/
	{
		
		fprintf(stderr, "Invalid input, expecting at least 2 input files");
		exit(1);
	}	
	
	
	
	if(argc <= 4)
	{
	
		//do_same_as_last_ex();
	}
	
	else 
	{
	
	
		int pp[2];
		pipe(pp);
		
		// more then 2 input files
		
		printf("process: %d is about to do fork..\n", getpid());
		
		if(fork() == 0)
		{
			
			do_stdin_redirection(argv[1]); //sending in1 to as stdin.
			dup2(pp[1], 1); //stdout points to writing end of the pipe.
			//close_pipe_ends(pp[0], 0); //closing the reading end
			//close_pipe_ends(pp[1], 1);
			fprintf(stderr,"204:process: %d is about to do exec..\n", getpid());
			
			
			if(execv(my_argv[0], my_argv) < 0)
			{
				fprintf(stderr,"209:execv failed...terminating the program");
				exit(2);
			}
		}
		
	else
	{
			
			wait(NULL);
			fprintf(stderr,"process: %d is awake..\n", getpid());
			//close(pp[1]);
		
		for(int i = 3; i < argc -1; i++)
		{
			char buff[500];
			redirect_stdin_to_read_end(pp[0]);
		
			if(i == argc-2)
			{
				//int pp1[2];
			
				
				/*fprintf(stderr, "205:about to read from the pipe: %s\n", buff); 
				int count = read(pp[0], buff, sizeof(buff));
				
				fprintf(stderr, "208:read from the pipe is: %s", buff);*/ 
				close_pipe_ends(pp[1], 1);
			
				
				if(fork() == 0)
				{		
				
					fprintf(stderr,"235:about to redirect stdout to outfile\n");
					//close_pipe_ends(pp[1], 1);
					
					//dup2(pp[0], 0);	
					
					dup2(argv[argc-1], stdout); // stdout point to outfile
			        	close_pipe_ends(pp[0], 0);
			        	close_pipe_ends(pp[1], 1);
			        	
			        	my_argv[1] = argv[i];				
					fprintf(stderr,"245 the argument file is: %s\n",
					 my_argv[1]);
					
					if(execv(my_argv[0], my_argv) < 0)
					{
					 fprintf(stderr,"execv failed...terminating the program");
					 exit(2);
					}
				}
			}
		
			/*else
			{
			
				do_stdin_redirection(my_argv[2]);
				my_argv[1] = argv[i];
		
				dup2(0,pp[0]);
			        pipe(pp);
				
				
				if(fork() == 0)
				{		
					dup2(pp[1], 1);
			   	        close(pp[0]);
				
					if(execv(my_argv[0], my_argv) < 0)
					{
					fprintf(stderr,"execv failed...terminating the program");
					exit(2);
					}
				}
			
			close(pp[1]);	
			
			}*/
				
			
			//close(pp[0]);
			//close(pp[1]);
			wait(NULL);
	
		}
		
	}
		
		
		
		if(execv(my_argv[0], my_argv) < 0)
		{
				fprintf(stderr,"execv failed...terminating the program");
				exit(2);
		}
	
	}
	
	return 0;
}

