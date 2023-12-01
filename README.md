# raspi5_IO
push button goes to input16 and LED goes output25
install gpiod (copy 2 lines below to terminal)
1. sudo apt-get install libgpiod2 libgpiod-dev
2. sudo apt install gpiod
3. Manually test with lines below. Copy and paste into terminal. 
check gpio line configuration (copy line below to terminal)
gpioinfo

set output 25 high (copy line below to terminal)

gpioset gpiochip4 25=1

set output 25 low (copy line below to terminal)

gpioset gpiochip4 25=0

monitor input 16 state (copy line below to terminal)

gpioset gpiochip4 16

USEFUL LINKS:

Video: https://youtu.be/koUr7oOyUXY

Access gpio with gpiod:
https://www.ics.com/blog/gpio-programming-exploring-libgpiod-library

https://lloydrochester.com/post/hardware/libgpiod-blink-led-rpi/

https://adafruit-playground.com/u/MakerMelissa/pages/comparing-libgpiod-and-gpiozero-speeds-on-the-raspberry-pi-5

old way sysfs, deprecated
https://www.ics.com/blog/gpio-programming-using-sysfs-interface

Pi pinout: https://vilros.com/pages/raspberry-pi-5-pinout

