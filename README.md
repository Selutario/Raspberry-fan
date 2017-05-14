# Raspberry-fan

![Raspberry](https://upload.wikimedia.org/wikipedia/en/thumb/c/cb/Raspberry_Pi_Logo.svg/190px-Raspberry_Pi_Logo.svg.png)

[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/Selutario/Raspberry-fan/blob/master/LICENSE)


--------------------------------------------


<h3>INSTALL</h3>

1) Download the folder and open Raspberry-fan/src/fan.c.

2) Modify the route where specified with the one of your folder (Write "pwd" on shell inside the folder to meet it).

3) Write "make" (without the quotes) on Raspberry-fan/ (you will need gcc compiler installed).

4) Write on shell: sudo nano /etc/systemd/system/fan.service

5) Paste and save this: 

        [Unit]
        Description=Turn on/off the fan depending on the temperature.

        [Service]
        Type=simple
        ExecStart=<span style="color:red">EDIT-WITH-FULL-ROUTE-TO-YOUR-EXECUTABLE*</span> start
        Restart=Always
        TimeoutStopSec=300

        [Install]
        WantedBy=multi-user.target

*Example: ExecStart=/home/osmc/Propios/Raspberry-fan/bin/raspberry-fan start

6) Write: sudo chmod 755 /etc/systemd/system/ventilador.service

7) Write: sudo systemctl enable fan.service

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
