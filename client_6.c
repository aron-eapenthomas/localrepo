#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9002
#define BUFFER_SIZE 2048

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    // STEP 3: Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // STEP 4: Define server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // STEP 5: Read a sentence containing abbreviations from the user using fgets()
    printf("Enter sentence with abbreviations: ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        close(sockfd);
        return 0;
    }

    // Remove trailing newline
    buffer[strcspn(buffer, "\n")] = 0;

    // STEP 6: Send sentence to server
    sendto(sockfd, buffer, strlen(buffer), 0,
           (const struct sockaddr *)&server_addr, addr_len);

    // STEP 7: Receive expanded sentence from server
    memset(buffer, 0, BUFFER_SIZE);
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                     (struct sockaddr *)&server_addr, &addr_len);
    if (n > 0) {
        buffer[n] = '\0';
        // STEP 8: Display expanded sentence
        printf("\nExpanded Sentence from Server:\n%s\n", buffer);
    }

    // STEP 9 & 10: Close socket and stop program
    close(sockfd);
    return 0;
}
