#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9002
#define BUFFER_SIZE 4096

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char filename[256];
    char buffer[BUFFER_SIZE];

    // Step 2: Create a TCP socket using socket()[span_24](start_span)[span_24](end_span)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        return -1;
    }

    // Step 3: Initialize server address structure[span_25](start_span)[span_25](end_span)
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // Step 4: Establish connection using connect()[span_26](start_span)[span_26](end_span)
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // Step 5: Prompt user for filename[span_27](start_span)[span_27](end_span)
    printf("Enter filename to request from server: ");
    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        // Step 6: Read filename into buffer[span_28](start_span)[span_28](end_span)
        filename[strcspn(filename, "\r\n")] = 0;

        // Step 7: Send filename to server using send()[span_29](start_span)[span_29](end_span)
        send(sock, filename, strlen(filename), 0);

        // Step 8 & 9: Wait and receive response containing PID and contents/error[span_30](start_span)[span_30](end_span)
        memset(buffer, 0, BUFFER_SIZE);
        int valread = recv(sock, buffer, BUFFER_SIZE - 1, 0);

        if (valread > 0) {
            buffer[valread] = '\0';
            // Step 10: Display received information[span_31](start_span)[span_31](end_span)
            printf("\n%s\n", buffer);
        } else {
            printf("No response from server.\n");
        }
    }

    // Step 11 & 12: Close socket and stop[span_32](start_span)[span_32](end_span)
    close(sock);
    return 0;
}
