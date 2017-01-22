principal:
	g++ src/fan.c -o bin/raspberry-fan -lwiringPi -O2 -Wall -Iinclude -lpthread -lrt -std=c++11
	@	 echo ">> Compilation completed."

clean: 
	rm bin/raspberry-fan
	rm ./fan-error.txt
	@	echo ">> Directory clean."	
