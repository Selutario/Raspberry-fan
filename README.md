# Raspberry-fan

![Raspberry](https://upload.wikimedia.org/wikipedia/en/thumb/c/cb/Raspberry_Pi_Logo.svg/190px-Raspberry_Pi_Logo.svg.png)

[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/Selutario/Raspberry-fan/blob/master/LICENSE)


--------------------------------------------


<h3>INSTALL</h3>

1) Download the folder and open Raspberry-fan/src/fan.c.

2) Modify the route where specified with the one of your folder (Write "pwd" on shell inside the folder to meet it).

3) Write "make" (without the quotes) on Raspberry-fan/ (you will need g++ compiler installed).

4) Write on shell: sudo nano /etc/init.d/fan-init

5) Paste and save this: 
    
    <code>
        #! /bin/sh
        # /etc/init.d/fan-init
        
        ### BEGIN INIT INFO
        # Provides:          fan-init
        # Required-Start:    $all
        # Required-Stop:     $remote_fs $syslog
        # Default-Start:     2 3 4 5
        # Default-Stop:      0 1 6
        # Short-Description: Script for fan
        # Description:       Script for fan
        ### END INIT INFO
        
        case "$1" in
        start)
            echo "Starting fan-init"
            # MODIFY THE ROUTE HERE (WRITE pwd ON Raspberry-fan/. TO MEET IT). KEEP sudo WORD
            sudo /home/osmc/Propios/Raspberry-fan/bin/raspberry-fan
            ;;
        stop)
            echo "Stopping fan-init"
        
            ;;
        *)
            echo "How to use it: /etc/init.d/fan-init {start|stop}"
            exit 1
            ;;
        esac
        
        exit 0
    </code>

6) Write: sudo chmod 755 /etc/init.d/fan-init

7) Write: sudo /etc/init.d/fan-init start

8) Write: sudo update-rc.d fan-init defaults

If you want to make sure it is running, write: ps aux | grep "Raspberry-fan"

<br>

----------------------------------
<h3>WHAT YOU NEED (HARDWARE)</h3>

<h4>Components</h4>

1) One fan. <b>IMPORTANT: Following components are for a 5v 0,2A fan.</b>

2) One NPN 2222a transistor.

3) One 680 ohms OR one 560 ohms resistance.

<h4>How to plug them</h4>

1) Connect positive pole of the fan to 5v Raspberry pin (pin 2 or 4 in BOARD Numbering)

2) Connect ground of the fan to <b>collector</b> of transistor

3) Connect <b>base</b> of transistor to 680 or 560 ohms resistance.

4) Connect resistance to pin 7 of raspberry pi (board). [GPIO4]

5) Connect emitter to GND of your raspberry.

![Raspberry](http://robologs.net/wp-content/uploads/2014/09/npn.png)

<br>

--------------------------------------
If you need any help, contact me: selutario@gmail.com
