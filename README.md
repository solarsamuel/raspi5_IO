# raspi5_IO

RUN PUSH BUTTON TO LED PROGRAM (push button goes to input16 and LED goes output25)

1. Copy in16out25.cpp to your Desktop and then navigate there

install gpiod (copy 2 lines below to terminal)

2. sudo apt-get install libgpiod2 libgpiod-dev
   
3. sudo apt install gpiod

compile

4. g++ in16out25.cpp -o in_out -lgpiod

run (CNTRL+C to exit)

5. ./in_out

RUN SERIAL CHARACTER TRANSMIT PROGRAM. Use the TXD (Pi GPIO pin 14) and GND. These go to either a micro-controller RXD and GND (like Seeed Xiao) or a FTDI serial to USB cable (https://www.amazon.com/FTDI-TTL-232R/dp/B08PW7HHCD?th=1). 

1. Copy c_send.cpp to your Desktop and then navigate there

compile

2. g++ c_send.cpp -o cs

run (CNTRL+X to exit)

3. ./cs


Manually test with lines below. Copy and paste into terminal. 
check gpio line configuration (copy line below to terminal)
gpioinfo

For Raspberry Pi 5 use gpiochip4 (For Raspberry Pi 4 use gpiochip0)

set output 25 high (copy line below to terminal)

gpioset gpiochip4 25=1

set output 25 low (copy line below to terminal)

gpioset gpiochip4 25=0

monitor input 16 state (copy line below to terminal)

gpioset gpiochip4 16

USEFUL LINKS:

Video of IO testing [PART 2 of 2]: https://youtu.be/koUr7oOyUXY
Video, IO with GPIOD [PART 1 of 2]: https://youtu.be/cBXBhVYnU5Q

Access gpio with gpiod:
https://www.ics.com/blog/gpio-programming-exploring-libgpiod-library

https://lloydrochester.com/post/hardware/libgpiod-blink-led-rpi/

https://adafruit-playground.com/u/MakerMelissa/pages/comparing-libgpiod-and-gpiozero-speeds-on-the-raspberry-pi-5

old way sysfs, deprecated
https://www.ics.com/blog/gpio-programming-using-sysfs-interface

Pi pinout: https://vilros.com/pages/raspberry-pi-5-pinout

