//#include <stdlib.h>
//#include <unistd.h>
//#include <signal.h>
//#include <string.h>
//#include <fcntl.h>
//#include <sys/wait.h>
//
//#define BUFFER_SIZE 1024
//
//void write_error(const char* msg) {
//    while (*msg) {
//        write(STDERR_FILENO, msg++, 1);
//    }
//}
//
//void float_to_string(float number, char* buffer) {
//    int int_part = (int)number;
//    float frac_part = number - int_part;
//
//    // Преобразуем целую часть
//    int length = 0;
//    if (int_part < 0) {
//        buffer[length++] = '-';
//        int_part = -int_part;
//    }
//
//    char temp[20];
//    int i = 0;
//    do {
//        temp[i++] = (int_part % 10) + '0';
//        int_part /= 10;
//    } while (int_part > 0);
//
//    // Записываем целую часть в обратном порядке
//    while (i > 0) {
//        buffer[length++] = temp[--i];
//    }
//
//    // Обрабатываем дробную часть
//    buffer[length++] = '.';
//    frac_part *= 10.0;  // Увеличиваем точность до одного знака после запятой
//    buffer[length++] = (int)frac_part + '0';
//
//    buffer[length] = '\0';  // Завершаем строку
//}
//
//void write_number_to_file(float number) {
//    int file = open("result.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
//    if (file < 0) {
//        write_error("Open file error\n");
//        exit(EXIT_FAILURE);
//    }
//
//    char buffer[100];
//    float_to_string(number, buffer);
//    write(file, "Result: ", 9);
//    write(file, buffer, strlen(buffer));
//    write(file, "\n", 1);
//    close(file);
//}
//
//void handle_division(float* numbers, int count) {
//    float result = numbers[0];
//    for (int i = 1; i < count; i++) {
//        if (numbers[i] == 0) {
//            kill(getppid(), SIGUSR1);
//            return;
//        }
//        result /= numbers[i];
//    }
//
//    write_number_to_file(result);
//}
//
//void sigusr1_handler(int signum) {
//    write_error("Error: division by zero.Deleting all process.\n");
//    exit(EXIT_FAILURE);
//}
//
//int main() {
//    signal(SIGUSR1, sigusr1_handler);
//
//    int pipe_fd[2];
//    if (pipe(pipe_fd) == -1) {
//        write_error("Create channel error\n");
//        exit(EXIT_FAILURE);
//    }
//
//    pid_t pid = fork();
//    if (pid < 0) {
//        write_error("Create proccess error\n");
//        exit(EXIT_FAILURE);
//    }
//
//    if (pid == 0) { // Дочерний процесс
//        close(pipe_fd[1]); // Закрываем запись в канале
//
//        float numbers[BUFFER_SIZE];
//        int count = 0;
//
//        // Читаем числа из канала
//        read(pipe_fd[0], numbers, sizeof(numbers));
//
//        // Подсчитываем количество считанных чисел
//        while (count < BUFFER_SIZE && numbers[count] != -1.0) {
//            count++;
//        }
//
//        handle_division(numbers, count);
//        close(pipe_fd[0]);
//        exit(EXIT_SUCCESS);
//    }
//    else { // Родительский процесс
//        close(pipe_fd[0]); // Закрываем чтение из канала
//
//        char input[BUFFER_SIZE];
//        float numbers[BUFFER_SIZE];
//        int count = 0;
//
//        // Ввод чисел
//        while (1) {
//            write(STDOUT_FILENO, "Input numbers (or exit for closing programm): ", 47);
//            read(STDIN_FILENO, input, BUFFER_SIZE);
//
//            if (strncmp(input, "exit", 4) == 0) {
//                break;
//            }
//
//            char* token = strtok(input, " ");
//            while (token != NULL && count < BUFFER_SIZE) {
//                numbers[count++] = atof(token);
//                token = strtok(NULL, " ");
//            }
//
//            // Отправляем числа в дочерний процесс
//            write(pipe_fd[1], numbers, sizeof(float) * count);
//            numbers[count++] = -1.0; // Отметка конца ввода
//            write(pipe_fd[1], &numbers[count - 1], sizeof(float)); // Завершаем ввод
//            count = 0; // Сброс счетчика для следующего ввода
//        }
//
//        close(pipe_fd[1]);
//        wait(NULL); // Ждем завершения дочернего процесса
//    }
//
//    return 0;
//}

//#include <stdlib.h>
//#include <unistd.h>
//#include <signal.h>
//#include <string.h>
//#include <fcntl.h>
//#include <sys/wait.h>
//
//#define BUFFER_SIZE 1024
//
//void write_error(const char* msg) {
//    while (*msg) {
//        write(STDERR_FILENO, msg++, 1);
//    }
//}
//
//void float_to_string(float number, char* buffer) {
//    int int_part = (int)number;
//    float frac_part = number - int_part;
//
//    int length = 0;
//    if (int_part < 0) {
//        buffer[length++] = '-';
//        int_part = -int_part;
//    }
//
//    char temp[20];
//    int i = 0;
//    do {
//        temp[i++] = (int_part % 10) + '0';
//        int_part /= 10;
//    } while (int_part > 0);
//
//    while (i > 0) {
//        buffer[length++] = temp[--i];
//    }
//
//    if (frac_part > 0) {
//        buffer[length++] = '.';
//        for (int j = 0; j < 6; j++) {
//            frac_part *= 10.0;
//            int frac_digit = (int)frac_part;
//            buffer[length++] = frac_digit + '0';
//            frac_part -= frac_digit;
//            if (frac_part <= 0) break;
//        }
//    }
//
//    buffer[length] = '\0';  // Завершение строки
//}
//
//void write_number_to_file(float number) {
//    int file = open("result.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
//    if (file < 0) {
//        write_error("Error opening file\n");
//        exit(EXIT_FAILURE);
//    }
//
//    char buffer[100];
//    float_to_string(number, buffer);
//    write(file, "Result of division: ", 20);
//    write(file, buffer, strlen(buffer));
//    write(file, "\n", 1);
//    close(file);
//}
//
//void handle_division(float* numbers, int count) {
//    float result = numbers[0];
//    for (int i = 1; i < count; i++) {
//        if (numbers[i] == 0) {
//            kill(getppid(), SIGUSR1);
//            return;
//        }
//        result /= numbers[i];
//    }
//
//    write_number_to_file(result);
//}
//
//void sigusr1_handler(int signum) {
//    write_error("Error: Division by zero. Terminating processes.\n");
//    exit(EXIT_FAILURE);
//}
//
//int main() {
//    signal(SIGUSR1, sigusr1_handler);
//
//    int pipe_fd[2];
//    if (pipe(pipe_fd) == -1) {
//        write_error("Error creating pipe\n");
//        exit(EXIT_FAILURE);
//    }
//
//    pid_t pid = fork();
//    if (pid < 0) {
//        write_error("Error creating process\n");
//        exit(EXIT_FAILURE);
//    }
//
//    if (pid == 0) { // Дочерний процесс
//        close(pipe_fd[1]); // Закрыть конец записи канала
//
//        float numbers[BUFFER_SIZE];
//        int count = 0;
//
//        // Чтение чисел из канала
//        while (read(pipe_fd[0], &numbers[count], sizeof(float)) > 0) {
//            if (numbers[count] == -1.0) break; // Проверка на маркер конца
//            count++;
//        }
//
//        handle_division(numbers, count);
//        close(pipe_fd[0]);
//        exit(EXIT_SUCCESS);
//    }
//    else { // Родительский процесс
//        close(pipe_fd[0]); // Закрыть конец чтения канала
//
//        char input[BUFFER_SIZE];
//        float numbers[BUFFER_SIZE];
//        int count = 0;
//
//        // Ввод чисел
//        while (1) {
//            write(STDOUT_FILENO, "Enter numbers (or 'exit' to quit): ", 36);
//            read(STDIN_FILENO, input, BUFFER_SIZE);
//
//            if (strncmp(input, "exit", 4) == 0) {
//                break;
//            }
//
//            char* token = strtok(input, " ");
//            while (token != NULL && count < BUFFER_SIZE) {
//                numbers[count++] = atof(token);
//                token = strtok(NULL, " ");
//            }
//
//            numbers[count] = -1.0; // Маркер конца
//            write(pipe_fd[1], numbers, sizeof(float) * (count + 1)); // Отправка чисел включая маркер
//            count = 0; // Сброс счетчика для следующего ввода
//            break;
//        }
//
//        close(pipe_fd[1]);
//        wait(NULL); // Ожидание завершения дочернего процесса
//    }
//
//    return 0;
//}

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_NUMBERS 100
#define BUFFER_SIZE 256

void handle_error(const char* msg) {
    write(STDERR_FILENO, msg, strlen(msg));
    exit(EXIT_FAILURE);
}

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        handle_error("pipe error\n");
    }

    pid_t pid = fork();
    if (pid < 0) {
        handle_error("fork error\n");
    }

    if (pid > 0) { 
        close(pipefd[0]); 

        float numbers[MAX_NUMBERS];
        int count = 0;

        
        char input[BUFFER_SIZE];
        while (1) {
            write(STDOUT_FILENO, "Input numbers: ", (int) sizeof("Input numbers: "));
            ssize_t bytes_read = read(STDIN_FILENO, input, sizeof(input) - 1);
            if (bytes_read <= 0) {
                break;
            }
            input[bytes_read] = '\0'; 

            
            char* token = strtok(input, " \n");
            while (token != NULL && count < MAX_NUMBERS) {
                numbers[count++] = atof(token);
                token = strtok(NULL, " \n");
            }
            break;
        }

        // Записываем числа в pipe
        write(pipefd[1], &count, sizeof(int)); 
        write(pipefd[1], numbers, count * sizeof(float)); 
        close(pipefd[1]); 

        
        wait(NULL);
    }
    else { 
        close(pipefd[1]); 

        
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); 

        // Замена процесса на дочерний
        execlp("./child", "child", NULL);
        handle_error("exec error\n");
    }

    return 0;
}