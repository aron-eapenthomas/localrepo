#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9002
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    int n;
    char buffer[BUFFER_SIZE];

    // STEP 3: Create a TCP socket using socket()[span_4](start_span)[span_4](end_span)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        return -1;
    }

    // STEP 4: Define server address structure[span_5](start_span)[span_5](end_span)
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // STEP 5: Establish connection with the server using connect()[span_6](start_span)[span_6](end_span)
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }
    printf("Connected to server successfully.\n");

    // STEP 6: Read the order n of the square matrix from the user[span_7](start_span)[span_7](end_span)
    printf("Enter order n of the square matrix: ");
    scanf("%d", &n);

    int matrix[n][n];

    // Read the n x n matrix elements from the user[span_8](start_span)[span_8](end_span)
    printf("Enter the elements of the %dx%d matrix:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    // STEP 7: Display the generated matrix[span_9](start_span)[span_9](end_span)
    printf("\nInput Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    // STEP 8: Send the order n to the server using send()[span_10](start_span)[span_10](end_span)
    send(sock, &n, sizeof(n), 0);

    // STEP 9: Send the matrix elements to the server using send()[span_11](start_span)[span_11](end_span)
    send(sock, matrix, sizeof(int) * n * n, 0);

    // STEP 10: Receive the matrix type from the server using recv()[span_12](start_span)[span_12](end_span)
    memset(buffer, 0, BUFFER_SIZE);
    recv(sock, buffer, BUFFER_SIZE - 1, 0);

    // STEP 11: Display the received matrix type[span_13](start_span)[span_13](end_span)
    printf("\nResult from Server: Matrix Type = %s\n", buffer);

    // STEP 12 & 13: Close socket connection and stop[span_14](start_span)[span_14](end_span)
    close(sock);
    return 0;
}
