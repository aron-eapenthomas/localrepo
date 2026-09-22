#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    // Step 2: Create TCP socket[span_1](start_span)[span_1](end_span)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 3: Define address structure and bind[span_2](start_span)[span_2](end_span)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Step 4: Put socket into listening mode[span_3](start_span)[span_3](end_span)
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d (Parent PID: %d)...\n", PORT, getpid());

    // Step 14: Loop to serve multiple clients simultaneously[span_4](start_span)[span_4](end_span)
    while (1) {
        // Step 5 & 6: Accept a client connection[span_5](start_span)[span_5](end_span)
        new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        // Step 7: Create a new child process using fork()[span_6](start_span)[span_6](end_span)
        pid_t pid = fork();

        if (pid == 0) {
            // --- CHILD PROCESS ---
            close(server_fd); // Child doesn't need listening socket

            // Display Child PID when client connects
            printf("\n[Child PID: %d] New client connected!\n", getpid());

            while (1) {
                memset(buffer, 0, BUFFER_SIZE);

                // Step 8: Receive message from client[span_7](start_span)[span_7](end_span)
                int valread = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
                if (valread <= 0) {
                    // Step 11: Display disconnect message with Child PID[span_8](start_span)[span_8](end_span)
                    printf("[Child PID: %d] Client disconnected.\n", getpid());
                    break;
                }

                buffer[valread] = '\0';

                // Step 9: Display message along with Child PID[span_9](start_span)[span_9](end_span)
                printf("[Child PID: %d] Client says: %s\n", getpid(), buffer);

                // Step 10: Echo message back to client[span_10](start_span)[span_10](end_span)
                send(new_socket, buffer, strlen(buffer), 0);
            }

            // Step 12: Close client socket in child process[span_11](start_span)[span_11](end_span)
            close(new_socket);
            exit(0); // Terminate child process
        } 
        else if (pid > 0) {
            // --- PARENT PROCESS ---
            // Step 13: Parent closes client socket and continues listening[span_12](start_span)[span_12](end_span)
            close(new_socket);
        } 
        else {
            perror("Fork failed");
        }
    }

    // Step 15 & 16: Close server socket and stop[span_13](start_span)[span_13](end_span)
    close(server_fd);
    return 0;
}
