# raspi5_IO
push button goes to input16 and LED goes output25
install gpiod (copy 2 lines below to terminal)
1. sudo apt-get install libgpiod2 libgpiod-dev
2. sudo apt install gpiod

compile

3. g++ in16out25.cpp -o in_out -lgpiod

run (CNTRL+C to exit)

4. ./in_out




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

