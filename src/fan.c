#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define FIFO "datos"

int main(int argc, char *argv[])
{
	int fd,
		temp;
	pid_t PID;
	char buffer[4];
	mkfifo(FIFO, 0777);

	if( (PID=fork()) < 0){
		perror("\nError en fork");
		exit(-1);
	}

	while(1){
		if(PID == 0){
			if( (fd = open(FIFO, O_RDWR, 0777)) < 0){
				printf("Se ha producido un error al intentar abrir el archivo fifo.\n");
				exit(-1);
			}

			dup2(fd, STDOUT_FILENO);
			system("./temp-fan.sh"); // mejor system("source - el script")
		}
		else{
			if( (fd = open(FIFO, O_RDONLY, 0777)) < 0){
				printf("Se ha producido un error al intentar abrir el archivo fifo.\n");
				exit(-1);
			}

			read(fd, buffer, 4);
			sscanf(buffer, "%d", &temp); // MEJOR STRTOL
			fflush(stdin);

			if(temp < 40)
				printf("La temperatura es buena (%d).\n", temp);
			else if(temp < 45)
				printf("La temperatura es media (%d).\n", temp);
			else
				printf("La temperatura es alta (%d).\n", temp);
		}

		sleep(5);
	}
}

//buscar en kerrisk 479 timers and sleeping