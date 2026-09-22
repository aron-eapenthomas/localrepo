#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    // Step 2: Create a TCP socket[span_14](start_span)[span_14](end_span)
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    // Step 3: Specify server IP address and port number[span_15](start_span)[span_15](end_span)
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address / Address not supported\n");
        return -1;
    }

    // Step 4: Establish connection with server using connect()[span_16](start_span)[span_16](end_span)
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    // Step 5: Display connection success message[span_17](start_span)[span_17](end_span)
    printf("Successfully connected to the server!\n");

    // Step 10: Repeat Steps 6-9 for continuous communication[span_18](start_span)[span_18](end_span)
    while (1) {
        // Step 6: Read a message from the user[span_19](start_span)[span_19](end_span)
        printf("\nEnter message (type 'exit' to quit): ");
        if (fgets(message, BUFFER_SIZE, stdin) == NULL) break;

        // Remove trailing newline
        message[strcspn(message, "\n")] = 0;

        if (strcmp(message, "exit") == 0) {
            break;
        }

        // Step 7: Send message using send()[span_20](start_span)[span_20](end_span)
        send(sock, message, strlen(message), 0);

        // Step 8: Receive response using recv()[span_21](start_span)[span_21](end_span)
        memset(buffer, 0, BUFFER_SIZE);
        int valread = recv(sock, buffer, BUFFER_SIZE - 1, 0);

        if (valread > 0) {
            buffer[valread] = '\0';
            // Step 9: Display received response[span_22](start_span)[span_22](end_span)
            printf("Server Echo: %s\n", buffer);
        } else {
            printf("Server disconnected.\n");
            break;
        }
    }

    // Step 11 & 12: Close socket and stop[span_23](start_span)[span_23](end_span)
    close(sock);
    printf("Connection closed.\n");
    return 0;
}
