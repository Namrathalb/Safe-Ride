Hardware Part:
So at first lets talk about the hardware part. Here I will use Raspberry Pi 3 B+, but You can also use other varients like Raspberry Pi Zero, Raspberry Pi 4 etc. I am using Neo 6M as GPS module because it’s quite cheap and also very much accurate.

Connections:
Here we only need to connect the Neo 6M module with Raspberry Pi which is quite easy. The connections are shown below:


    Neo 6M VCC -----> Raspberry pi 5v
		Neo 6M GND -----> Raspberry pi GND
		Neo 6M  RX -----> Raspberry pi TX (gpio 14) //Not required in our case
		Neo 6M  TX -----> Raspberry pi RX (gpio 15)
    
    
So we need the VCC of Neo 6M to be connected with 5v of Raspberry pi, GND of Neo 6M with GND of Raspberry pi and TX of Neo 6M with RX of Raspberry Pi so that the gps module can send data to raspberry pi through the serial connection. Thats all about the hardware part and now lets go for the software part.


Software Part:

Getting data from the GPS module:
1) Install the lastest Rasbian OS in a memory card. For details visit www.raspberrypi.org/documentation/installation/installing-images/.
2)Insert the memory card into raspberry pi and power it up.

Now here we need to modify few things. At first we need to edit the /boot/config.txt file. Now you need to open this file in any text editor. Here I am using nano:

In terminal type:
sudo nano /boot/config.txt

At the end of the file add the follwing lines:

dtparam=spi=on
dtoverlay=pi3-disable-bt
core_freq=250
enable_uart=1
force_turbo=1

It will look something like this:

























