//if input 16 gets connected to 3.3V then output 25 turns on and supplies 3.3V
#include <gpiod.h>
#include <iostream>
#include <unistd.h>

int main() {
    gpiod_chip *chip;
    gpiod_line *input_line, *output_line;
    //For Raspberry Pi 5 use gpiochip4 (For Raspberry Pi 4 use gpiochip0)
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

    // Using gpiod_line_request_input_flags function for pull-down
    if (gpiod_line_request_input_flags(input_line, "input-check", GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_DOWN) < 0) {
        std::cerr << "Could not configure input line with pull-down." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    // Configure output line
    if (gpiod_line_request_output(output_line, "output-control", 0) < 0) {
        std::cerr << "Could not set output line." << std::endl;
        gpiod_line_release(input_line);
        gpiod_chip_close(chip);
        return 1;
    }

    while (true) {
        int val = gpiod_line_get_value(input_line);
        gpiod_line_set_value(output_line, val); // Set output based on input
        usleep(100000); // 100ms delay between checks
    }

    // Cleanup (this part will never execute due to the infinite loop)
    gpiod_line_release(input_line);
    gpiod_line_release(output_line);
    gpiod_chip_close(chip);
    return 0;
}
