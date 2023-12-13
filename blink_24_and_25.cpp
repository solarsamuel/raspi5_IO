#include <gpiod.h>
#include <iostream>
#include <unistd.h>

int main() {
    gpiod_chip *chip;
    gpiod_line *line_24, *line_25;
    const char *chipname = "gpiochip4"; // Modify this if needed for your Pi version
    const unsigned int line_offset_24 = 24;
    const unsigned int line_offset_25 = 25;

    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        std::cerr << "Could not open chip." << std::endl;
        return 1;
    }

    line_24 = gpiod_chip_get_line(chip, line_offset_24);
    line_25 = gpiod_chip_get_line(chip, line_offset_25);
    if (!line_24 || !line_25) {
        std::cerr << "Could not get line." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    if (gpiod_line_request_output(line_24, "blinktest", 0) < 0 || gpiod_line_request_output(line_25, "blinktest", 0) < 0) {
        std::cerr << "Could not set line as output." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    while (true) {
        gpiod_line_set_value(line_24, 1);
        gpiod_line_set_value(line_25, 1);
        usleep(500000); // 500ms delay
        gpiod_line_set_value(line_24, 0);
        gpiod_line_set_value(line_25, 0);
        usleep(500000); // 500ms delay
    }

    gpiod_chip_close(chip);
    return 0;
}
