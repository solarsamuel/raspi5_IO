#include <gpiod.h>
#include <iostream>
#include <unistd.h>

int main() {
    gpiod_chip *chip;
    gpiod_line *input_line, *output_line;
    const char *chipname = "gpiochip4";
    const unsigned int input_line_offset = 16; // GPIO input 16
    const unsigned int output_line_offset = 25; // GPIO output 25

    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        std::cerr << "Could not open chip." << std::endl;
        return 1;
    }

    input_line = gpiod_chip_get_line(chip, input_line_offset);
    if (!input_line) {
        std::cerr << "Could not get input line." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    output_line = gpiod_chip_get_line(chip, output_line_offset);
    if (!output_line) {
        std::cerr << "Could not get output line." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    if (gpiod_line_request_input(input_line, "input-check") < 0 ||
        gpiod_line_request_output(output_line, "output-control", 0) < 0) {
        std::cerr << "Could not set line direction." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    while (true) {
        int val = gpiod_line_get_value(input_line);
        if (val == 1) {
            // If input is high, blink output every second
            gpiod_line_set_value(output_line, 1);
            usleep(500000); // 500ms on
            gpiod_line_set_value(output_line, 0);
            usleep(500000); // 500ms off
        } else {
            // If input is low, turn off output
            gpiod_line_set_value(output_line, 0);
        }
        usleep(10000); // 10ms delay between checks
    }

    gpiod_chip_close(chip);
    return 0;
}
