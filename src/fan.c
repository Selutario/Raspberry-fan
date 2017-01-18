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
	int fd[2], temp;
	pid_t PID;
	char buffer[4];

	pipe(fd);

	if( (PID=fork()) < 0){
		perror("\nError en fork.");
		exit(-1);
	}

	while(1){
		if(PID == 0){
			// Cierra descriptor de archivo de lectura
			close(fd[0]);

			// Duplica el de escritura en el fd restante (y cierra el original)
			dup2(fd[1], STDOUT_FILENO);
			system("sensors | grep -m 1 temp1 | cut -d\" \" -f9 | cut -d\"+\" -f2 | cut -c 1-2"); // mejor system("source - el script")
		}
		else{

			// Cierra descriptor de archivo de escritura
			close(fd[1]);

			// Duplica el de lectura en el fd restante (y cierra el original)
			dup2(fd[0], STDIN_FILENO);

			read(fd[0], buffer, 4);
			sscanf(buffer, "%d", &temp); // MEJOR STRTOL

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