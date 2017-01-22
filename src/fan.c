#include <sys/types.h>
#include <sys/stat.h>
#include <wiringPi.h>
#include <wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define temp_encender 60
#define temp_apagar 56
#define comprobar_cada 5

int main(int argc, char *argv[])
{
	bool fan_on = false;
	int temp, fd[2], errfi = -1;
	pid_t PID;
	char buffer[4];

	// REDIRIGIR SALIDA DE ERROR A ARCHIVO 
	//###################################################################
	if((errfi=open("../fan-error.txt", O_CREAT|O_WRONLY|O_APPEND, 0777)) < 0)
		printf("Se ha producido un error en la creación de registro de errores. No se podrán almacenar.\n");
	
	dup2(errfi, STDERR_FILENO);
	//###################################################################

	// Setup de salida GPIO
	wiringPiSetup () ;
	pinMode (4, OUTPUT) ;

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

			temp = strtol(buffer, NULL, 10);
			if(temp == 0 ){
				perror("Error en strtol de temp");
				exit(EXIT_FAILURE);
			}

			if(temp < temp_encender){
				printf("La temperatura es media (%d).\n", temp);

					if(fan_on && temp_apagar > temp ){
						fan_on = false;
						printf("Apagar ventilador\n");
						digitalWrite (4, LOW) ;	// Off
					}
			}
			else{
				printf("La temperatura es alta (%d).\n", temp);
				if(!fan_on){
					fan_on = true;
					printf("Encender ventilador\n");
					digitalWrite (4, HIGH) ;	// On
				}
			}
		}

		sleep(comprobar_cada);
	}

	wait(NULL);
}

//buscar en kerrisk 479 timers and sleeping