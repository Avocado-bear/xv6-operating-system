#include "kernel/types.h"
#include "user/user.h"

void runprocess(int listenfd){
	int my_num = 0;
	int passed_num = 0;
	int pipes[2];
	int hasChild = 0;
	pipe(pipes);
	while(1){
		int read_bytes = read(listenfd, &passed_num, 4);

		if(read_bytes == 0){
			close(listenfd);
			close(pipes[1]);
			if(hasChild){
				runprocess(pipes[0]);
				wait(0);
			}
			exit(0);
		}

		if(my_num == 0){
			my_num = passed_num;
			printf("prime %d\n", my_num);
			continue;
		}

		if(passed_num % my_num != 0){
			hasChild = 1;
			write(pipes[1], &passed_num, 4);
		}
	}
}

int main(int argc, char *argv[]){
	int pipes[2];
	pipe(pipes);
	for(int i = 2; i <= 35; i++){
		write(pipes[1], &i, 4);
	}
	close(pipes[1]);
	runprocess(pipes[0]);
	exit(0);
}
