#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	bool fan_on = false;
	int fd[2], errfi = 0, temp;
	pid_t PID;
	char buffer[4];
	char *ptr;

	// REDIRIGIR SALIDA DE ERROR A ARCHIVO 
	dup2(errfi, STDERR_FILENO);

	if(pipe(fd) < 0){
		perror("Se ha producido un error al intentar generar el cauce\n");
		exit(EXIT_FAILURE);
	}

	if( (PID=fork()) < 0){
		perror("\nError en fork.");
		exit(EXIT_FAILURE);
	}

	while(1){
		if(PID == 0){
			// Cierra descriptor de archivo de lectura
			close(fd[0]);

			// Duplica el de escritura en el fd restante (y cierra el original)
			dup2(fd[1], STDOUT_FILENO);

			 // mejor system("source - el script")
			if(system("sensors | grep -m 1 temp1 | cut -d\" \" -f9 | cut -d\"+\" -f2 | cut -c 1-2") < 0)
				perror("Se ha producido un error al consultar la temperatura.\n");
		}	
		else{

			// Cierra descriptor de archivo de escritura
			close(fd[1]);

			// Duplica el de lectura en el fd restante (y cierra el original)
			dup2(fd[0], STDIN_FILENO);

			if(read(fd[0], buffer, 4) < 0)
				perror("Se ha producido un error al leer la temperatura.\n");

			temp = strtol(buffer, &ptr, 10);
			if(temp == 0 ){
				perror("Error en strtol de temp");
				exit(EXIT_FAILURE);
			}

			if(temp < 58){
				printf("La temperatura es media (%d).\n", temp);

					if(fan_on && 55 > temp ){
						fan_on = false;
						printf("Apagar ventilador\n");
					}
			}
			else{
				printf("La temperatura es alta (%d).\n", temp);
				if(!fan_on){
					fan_on = true;
					printf("Encender ventilador\n");
				}
			}
		}

		sleep(5);
	}
}

//buscar en kerrisk 479 timers and sleeping