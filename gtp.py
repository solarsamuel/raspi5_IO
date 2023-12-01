from gpiozero import DigitalInputDevice, DigitalOutputDevice
from time import sleep

input_pin = 16  # GPIO input 16
output_pin = 25  # GPIO output 25

input_device = DigitalInputDevice(input_pin)
output_device = DigitalOutputDevice(output_pin)

while True:
    if input_device.value:
        # If input is high, blink output every second
        output_device.on()
        sleep(0.5)  # 500ms on
        output_device.off()
        sleep(0.5)  # 500ms off
    else:
        # If input is low, turn off output
        output_device.off()
    sleep(0.1)  # 100ms delay between checks
