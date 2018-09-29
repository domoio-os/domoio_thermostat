Thermostat Domoio firmware for ESP8266
===========================================
[Domoio](https://domoio.com) is a framework for home automation. This project shows the power of domoio implementing a simple thermostat using the [Domoio client for ESP8266](https://github.com/domoio-os/domoio_esp8266)

# Upload the firmware
## Requirements
- Arduino IDE. Get the latest version from the [Arduino website](http://www.arduino.cc/en/main/software)
- The [ESP8266 core for Arduino](https://github.com/esp8266/Arduino)
- The [Domoio client for ESP8266](https://github.com/domoio-os/domoio_esp8266) (Optional, the repository already include a precompiled version, libdomoio.a)

## Setup the Makefile
Copy and edit Makefile.sample. Visit [https://github.com/plerup/makeEspArduino](https://github.com/plerup/makeEspArduino) for more information about the parameters.

    cp Makefile.sample Makefile

## Upload certificates
Each domoio device require unique pair of rsa keys. You have to generte and flash these keys just one time per device.


     mkdir root_fs && cd root_fs
     openssl genrsa -out server.pem 1024
     openssl rsa -in server.pem -outform PEM -pubout -out server.pub.pem

     # Convert them to DER format
     openssl rsa -in server.pem -outform DER -pubout -out server.pub.der
     openssl rsa -in server.pem -outform DER -out server.der
     rm server.pem server.pub.pem
     cd ..

     #Then, flash the new fs
     make flash_fs FS_DIR=./root_fs


## Flash the firmware

    make flash
