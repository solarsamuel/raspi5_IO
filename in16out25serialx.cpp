#include <gpiod.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <cstring>
#include <errno.h>

int uart_fd;

void setup_uart() {
    // Open UART device for Raspberry Pi 5
    uart_fd = open("/dev/ttyAMA2", O_WRONLY | O_NOCTTY | O_NDELAY);
    if (uart_fd < 0) {
        std::cerr << "Failed to open UART device: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Configure UART
    struct termios options;
    tcgetattr(uart_fd, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart_fd, TCIFLUSH);
    tcsetattr(uart_fd, TCSANOW, &options);
}

void send_uart(char c) {
    if (write(uart_fd, &c, 1) < 0) {
        std::cerr << "Failed to write to UART device: " << strerror(errno) << std::endl;
    } else {
        std::cout << "Sent character '" << c << "' via UART" << std::endl;
    }
}

int main() {
    gpiod_chip *chip;
    gpiod_line *input_line, *output_line;
    int prev_val = 0; // Track previous input state
    
    // For Raspberry Pi 5 use gpiochip4
    const char *chipname = "gpiochip4";
    const unsigned int input_line_offset = 16; // GPIO input 16
    const unsigned int output_line_offset = 25; // GPIO output 25
    
    // Setup UART first
    setup_uart();
    
    // Setup GPIO
    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        std::cerr << "Could not open chip." << std::endl;
        close(uart_fd);
        return 1;
    }
    
    input_line = gpiod_chip_get_line(chip, input_line_offset);
    if (!input_line) {
        std::cerr << "Could not get input line." << std::endl;
        gpiod_chip_close(chip);
        close(uart_fd);
        return 1;
    }
    
    output_line = gpiod_chip_get_line(chip, output_line_offset);
    if (!output_line) {
        std::cerr << "Could not get output line." << std::endl;
        gpiod_line_release(input_line);
        gpiod_chip_close(chip);
        close(uart_fd);
        return 1;
    }
    
    // Using gpiod_line_request_input_flags function for pull-down
    if (gpiod_line_request_input_flags(input_line, "input-check", GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_DOWN) < 0) {
        std::cerr << "Could not configure input line with pull-down." << std::endl;
        gpiod_chip_close(chip);
        close(uart_fd);
        return 1;
    }
    
    // Configure output line
    if (gpiod_line_request_output(output_line, "output-control", 0) < 0) {
        std::cerr << "Could not set output line." << std::endl;
        gpiod_line_release(input_line);
        gpiod_chip_close(chip);
        close(uart_fd);
        return 1;
    }
    
    std::cout << "Monitoring GPIO input 16. Press Ctrl+C to exit." << std::endl;
    
    while (true) {
        int val = gpiod_line_get_value(input_line);
        
        // Set output based on input
        gpiod_line_set_value(output_line, val);
        
        // If input has gone from low to high, send 'x' via UART
        if (val == 1 && prev_val == 0) {
            send_uart('x');
        }
        
        prev_val = val; // Update previous state
        usleep(100000); // 100ms delay between checks
    }
    
    // Cleanup (this part will never execute due to the infinite loop unless Ctrl+C is pressed)
    gpiod_line_release(input_line);
    gpiod_line_release(output_line);
    gpiod_chip_close(chip);
    close(uart_fd);
    
    return 0;
}
