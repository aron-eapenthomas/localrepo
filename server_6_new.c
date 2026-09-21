#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9002
#define BUFFER_SIZE 2048

// Predefined abbreviation mappings from the lab manual[cite: 3]
struct Mapping {
    const char *abbr;
    const char *expansion;
} mappings[] = {
    {"tbh", "to be honest"},
    {"ig", "I guess"},
    {"tbf", "to be fair"},
    {"atm", "at the moment"},
    {"irl", "in real life"},
    {"lol", "laughing out loud"},
    {"asap", "as soon as possible"},
    {"omg", "oh my God"},
    {"ttyl", "talk to you later"},
    {"idk", "I don't know"},
    {"nvm", "never mind"}
};

int num_mappings = sizeof(mappings) / sizeof(mappings[0]);

// Simple search-and-replace function
void replace_abbreviations(char *src, char *dest) {
    char temp[BUFFER_SIZE];
    strcpy(dest, src);

    for (int i = 0; i < num_mappings; i++) {
        char *pos;
        // Loop to find all occurrences of the abbreviation in the string
        while ((pos = strstr(dest, mappings[i].abbr)) != NULL) {
            // Store everything after the match in temp
            strcpy(temp, pos + strlen(mappings[i].abbr));
            
            // Replace abbreviation with its expansion
            strcpy(pos, mappings[i].expansion);
            
            // Append the rest of the string back
            strcat(dest, temp);
        }
    }
}

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    char modified_buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // STEP 4: Create UDP socket[cite: 3]
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // STEP 5: Define server address structure[cite: 3]
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // STEP 6: Bind socket[cite: 3]
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        // STEP 7 & 8: Receive message from client[cite: 3]
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                         (struct sockaddr *)&client_addr, &addr_len);
        if (n < 0) continue;
        buffer[n] = '\0';

        printf("\nOriginal Message: %s\n", buffer);

        // STEP 9: Replace abbreviations[cite: 3]
        replace_abbreviations(buffer, modified_buffer);
        printf("Expanded Message: %s\n", modified_buffer);

        // STEP 10: Send modified message back to client[cite: 3]
        sendto(sockfd, modified_buffer, strlen(modified_buffer), 0,
               (struct sockaddr *)&client_addr, addr_len);
    }

    close(sockfd);
    return 0;
}
