#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9002
#define BUFFER_SIZE 4096

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    // Step 2: Create a TCP socket using socket()[span_3](start_span)[span_3](end_span)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 3: Initialize server address structure (AF_INET, INADDR_ANY, Port 9002)[span_4](start_span)[span_4](end_span)
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Step 4: Bind socket to the specified port[span_5](start_span)[span_5](end_span)
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Step 5: Put socket into listening mode[span_6](start_span)[span_6](end_span)
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Step 6: Display ready message[span_7](start_span)[span_7](end_span)
    printf("Server ready and waiting for client requests on port %d...\n", PORT);

    // Step 18: Loop for incoming client requests[span_8](start_span)[span_8](end_span)
    while (1) {
        // Step 7: Accept a client connection[span_9](start_span)[span_9](end_span)
        new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        // Step 8: Create child process using fork()[span_10](start_span)[span_10](end_span)
        pid_t pid = fork();

        if (pid == 0) {
            // --- CHILD PROCESS ---
            // Step 9: Close listening socket in child process[span_11](start_span)[span_11](end_span)
            close(server_fd);

            char filename[256] = {0};
            char response[BUFFER_SIZE] = {0};

            // Step 9: Receive filename sent by client[span_12](start_span)[span_12](end_span)
            int bytes_read = recv(new_socket, filename, sizeof(filename) - 1, 0);
            if (bytes_read > 0) {
                filename[bytes_read] = '\0';
                
                // Trim trailing newline if present
                filename[strcspn(filename, "\r\n")] = 0;

                printf("[Child PID: %d] Requested file: %s\n", getpid(), filename);

                // Step 10: Attempt to open the requested file using fopen()[span_13](start_span)[span_13](end_span)
                FILE *file = fopen(filename, "r");

                // Step 11: Check whether file exists[span_14](start_span)[span_14](end_span)
                if (file != NULL) {
                    // Step 12: File exists[span_15](start_span)[span_15](end_span)
                    char file_buffer[BUFFER_SIZE - 256] = {0};
                    char line[512];

                    // Read file line by line and store in buffer[span_16](start_span)[span_16](end_span)
                    while (fgets(line, sizeof(line), file) != NULL) {
                        strcat(file_buffer, line);
                    }

                    // Obtain PID and prepare response[span_17](start_span)[span_17](end_span)
                    snprintf(response, sizeof(response), 
                             "--- Response from Server Process ID (PID): %d ---\n%s", 
                             getpid(), file_buffer);

                    // Step 15: Close file[span_18](start_span)[span_18](end_span)
                    fclose(file);
                } else {
                    // Step 13: File does not exist[span_19](start_span)[span_19](end_span)
                    snprintf(response, sizeof(response), 
                             "--- Response from Server Process ID (PID): %d ---\nError: File not found", 
                             getpid());
                }

                // Step 14: Send prepared response to client[span_20](start_span)[span_20](end_span)
                send(new_socket, response, strlen(response), 0);
            }

            // Step 16: Close client socket and terminate child process[span_21](start_span)[span_21](end_span)
            close(new_socket);
            exit(0);
        } else if (pid > 0) {
            // --- PARENT PROCESS ---
            // Step 17: Close connected socket in parent and continue waiting[span_22](start_span)[span_22](end_span)
            close(new_socket);
        } else {
            perror("Fork failed");
        }
    }

    // Step 19 & 20: Close server socket and stop[span_23](start_span)[span_23](end_span)
    close(server_fd);
    return 0;
}
