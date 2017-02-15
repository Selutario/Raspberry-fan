principal:
	g++ src/fan.c -o bin/raspberry-fan -O2 -Wall -Iinclude -std=c++11
	@	 echo ">> Compilation completed."

clean: 
	rm bin/raspberry-fan
	rm ./fan-error.txt
	@	echo ">> Directory clean."	
