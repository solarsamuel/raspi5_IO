//Blink raspberry pi gpio output 25. Connect a LED to the pin in series with a 200 ohm resistor. The other end of the LED connects to ground. 
//Works for raspberry pi 4 or 5. Change the gpiochip number for the appropriate board. 

#include <gpiod.h>
#include <iostream>
#include <unistd.h>

int main() {
    gpiod_chip *chip;
    gpiod_line *line;
	//For Raspberry Pi 5 use gpiochip4 (For Raspberry Pi 4 use gpiochip0)
    const char *chipname = "gpiochip4";
    const unsigned int line_offset = 25;
    
    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        std::cerr << "Could not open chip." << std::endl;
        return 1;
    }

    line = gpiod_chip_get_line(chip, line_offset);
    if (!line) {
        std::cerr << "Could not get line." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    if (gpiod_line_request_output(line, "blinktest", 0) < 0) {
        std::cerr << "Could not set line as output." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    while (true) {
        gpiod_line_set_value(line, 1);
        usleep(500000); // 500ms delay
        gpiod_line_set_value(line, 0);
        usleep(500000); // 500ms delay
    }

    gpiod_chip_close(chip);
    return 0;
}
