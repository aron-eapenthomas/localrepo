#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9002
#define BUFFER_SIZE 2048

// STEP 3: Structure and function to expand abbreviations
struct Mapping {
    const char *abbr;
    const char *expansion;
};

// List of predefined abbreviations from STEP 9
struct Mapping mappings[] = {
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

void replace_abbreviations(const char *src, char *dest) {
    char temp[BUFFER_SIZE];
    strcpy(temp, src);
    dest[0] = '\0';

    char *token = strtok(temp, " \t\n\r");
    while (token != NULL) {
        int replaced = 0;
        
        // Strip punctuation trailing the word for accurate matching
        char clean_word[256];
        char punctuation[256] = "";
        int len = strlen(token);
        int p_idx = 0;
        int w_len = 0;

        for (int i = 0; i < len; i++) {
            if (ispunct((unsigned char)token[i])) {
                punctuation[p_idx++] = token[i];
            } else {
                clean_word[w_len++] = token[i];
            }
        }
        clean_word[w_len] = '\0';
        punctuation[p_idx] = '\0';

        // Check if clean_word matches any abbreviation
        for (int i = 0; i < num_mappings; i++) {
            if (strcasecmp(clean_word, mappings[i].abbr) == 0) {
                strcat(dest, mappings[i].expansion);
                strcat(dest, punctuation);
                replaced = 1;
                break;
            }
        }

        // If no replacement, append original word
        if (!replaced) {
            strcat(dest, token);
        }

        strcat(dest, " ");
        token = strtok(NULL, " \t\n\r");
    }

    // Trim trailing space
    int final_len = strlen(dest);
    if (final_len > 0 && dest[final_len - 1] == ' ') {
        dest[final_len - 1] = '\0';
    }
}

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    char modified_buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // STEP 4: Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // STEP 5: Define server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // STEP 6: Bind socket to port 9002
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        memset(modified_buffer, 0, BUFFER_SIZE);

        // STEP 7 & 8: Receive message from client and store in buffer
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                         (struct sockaddr *)&client_addr, &addr_len);
        if (n < 0) {
            perror("Recvfrom failed");
            continue;
        }
        buffer[n] = '\0';

        printf("\nReceived Message: %s\n", buffer);

        // STEP 9: Replace abbreviations
        replace_abbreviations(buffer, modified_buffer);
        printf("Expanded Message: %s\n", modified_buffer);

        // STEP 10: Send modified message back to client
        sendto(sockfd, modified_buffer, strlen(modified_buffer), 0,
               (struct sockaddr *)&client_addr, addr_len);
    }

    // STEP 11 & 12: Close socket and stop program
    close(sockfd);
    return 0;
}
