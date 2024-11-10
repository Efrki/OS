#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

#define MAX_NUMBERS 100

void handle_error(const char* msg) {
    write(STDERR_FILENO, msg, strlen(msg));
    exit(EXIT_FAILURE);
}

int main() {
    float numbers[MAX_NUMBERS];
    int count;

    
    if (read(STDIN_FILENO, &count, sizeof(int)) != sizeof(int)) {
        handle_error("read error\n");
    }

    
    if (read(STDIN_FILENO, numbers, count * sizeof(float)) != count * sizeof(float)) {
        handle_error("read error\n");
    }

    
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        handle_error("file open error\n");
    }

    float result = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] == 0.0) {
            write(fd, "Error: division by 0\n", (int) sizeof("Error: division by 0\n"));
            close(fd);
            exit(EXIT_FAILURE);
        }
        result /= numbers[i];
    }

    
    char buffer[50];
    int len = snprintf(buffer, sizeof(buffer), "Result: %f\n", result);
    write(fd, buffer, len);
    close(fd);
    exit(EXIT_SUCCESS);
}