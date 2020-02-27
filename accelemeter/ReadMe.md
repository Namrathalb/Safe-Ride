MPU6050 (Accelerometer+Gyroscope) Interfacing with Raspberry Pi

Introduction

1.MPU6050 sensor module is an integrated 6-axis Motion tracking device.
2.It has a 3-axis Gyroscope, 3-axis Accelerometer, Digital Motion Processor and a Temperature sensor, all in a single IC.
3.It can accept inputs from other sensors like 3-axis magnetometer or pressure sensor using its Auxiliary I2C bus.
4.If external 3-axis magnetometer is connected, it can provide complete 9-axis Motion Fusion output.
5.A microcontroller can communicate with this module using I2C communication protocol. Various parameters can be found by reading values 6.from addresses of certain registers using I2C communication.
7.Gyroscope and accelerometer reading along X, Y and Z axes are available in 2’s complement form.
8.Gyroscope readings are in degrees per second (dps) unit; Accelerometer readings are in g unit.

To interface MPU6050 using Raspberry Pi, we should ensure that I2C protocol on Raspberry Pi is turned on. So before going for interfacing MPU6050 with raspberry Pi, we need to make some I2C configurations on Raspberry Pi which you can refer Raspberry Pi I2C.

After configuring I2C on Raspberry Pi, let’s interface Raspberry Pi with MPU6050.

Interfacing Diagram:
![GitHub Logo](https://www.electronicwings.com/public/images/user_images/images/Raspberry%20Pi/RaspberryPi_Interface/RaspberryPi_MPU6050/MPU6050_interface_with_Raspberry%20Pi.png)

same configuration for PI 4 as we are using pi4

Example:
Here, we will interface MPU6050 module with Raspberry Pi to read Gyroscope and Accelerometer value and print them.

in terminal run:

sudo python MPU6050.py

We can interface MPU6050 module with Raspberry Pi using Python and C language. We will display the value of Accelerometer and Gyroscope on terminal which are read from MPU6050 module.

MPU6050 Output

Output window will show all values mentioned below

Gx  = Gyro X-axis data in degree/seconds
Gy  = Gyro Y-axis data in degree/seconds
Gz  = Gyro Z-axis data in degree/seconds

Ax  = Accelerometer X-axis data in g
Ay  = Accelerometer Y-axis data in g
Az  = Accelerometer Z-axis data in g


it will look something like this:

![GitHub Logo](https://www.electronicwings.com/public/images/user_images/images/Raspberry%20Pi/RaspberryPi_Interface/RaspberryPi_MPU6050/MPU6050%20Output.png)
