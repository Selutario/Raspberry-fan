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
#define comprobar_cada 10

// NO MODIFIQUE ESTO SI NO ESTÁ SEGURO DE COMO HACERLO
#define PIN 4 // - > Numeración BCM; | Pin 7 en numeración BOARD


int main(int argc, char *argv[])
{
	bool fan_on = false;
	int temp, fd[2], errfi = -1;
	pid_t PID;
	char buffer[5];

	// REDIRIGIR SALIDA DE ERROR A ARCHIVO 
	//###################################################################
	
	// Editar ruta
	if((errfi=open("/home/osmc/Propios/Raspberry-fan/fan-error.txt", O_CREAT|O_WRONLY|O_APPEND, 0777)) < 0)
		printf("Se ha producido un error en la creación de registro de errores. No se podrán almacenar.\n\n");
	
	dup2(errfi, STDERR_FILENO);
	//###################################################################

	// Setup de salida GPIO
	wiringPiSetupGpio() ;
	pinMode(PIN, OUTPUT) ;

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
			if(system("/opt/vc/bin/vcgencmd measure_temp | cut -d\"=\" -f2 | cut -d\"'\" -f1") < 0)
				perror("Se ha producido un error al consultar la temperatura.\n");
		}	
		else{

			// Cierra descriptor de archivo de escritura
			close(fd[1]);

			// Duplica el de lectura en el fd restante (y cierra el original)
			dup2(fd[0], STDIN_FILENO);

			if(read(fd[0], buffer, 5) < 0)
				perror("Se ha producido un error al leer la temperatura.\n");

			temp = strtol(buffer, NULL, 10);
			if(temp == 0 ){
				perror("Error en strtol de temp");
				exit(EXIT_FAILURE);
			}

			if(temp < temp_encender){
					if(fan_on && temp_apagar > temp ){
						fan_on = false;
						digitalWrite (PIN, LOW) ;	// Off
					}
			}
			else{
				if(!fan_on){
					fan_on = true;
					digitalWrite (PIN, HIGH) ;	// On
				}
			}
		}

		sleep(comprobar_cada);
	}

	wait(NULL);
}