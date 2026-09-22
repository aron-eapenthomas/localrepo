#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/ethernet.h>  // Ethernet header (struct ethhdr)
#include <netinet/ip.h>    // IP header (struct iphdr)

#define BUFFER_SIZE 65536

int main() {
    int raw_socket;
    unsigned char buffer[BUFFER_SIZE];
    struct sockaddr saddr;
    socklen_t saddr_len = sizeof(saddr);

    // STEP 3: Create a raw socket using socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))
    raw_socket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    // STEP 4: Check whether the socket is created successfully
    if (raw_socket < 0) {
        perror("Socket creation failed (Make sure you run as root / sudo)");
        exit(EXIT_FAILURE);
    }

    // STEP 5: Display "Packet Capturing Started..."
    printf("Packet Capturing Started...\n");
    printf("----------------------------------------\n");

    // STEP 10: Repeat Steps 6-9 continuously
    while (1) {
        // STEP 6: Receive packets continuously using recvfrom()
        int data_size = recvfrom(raw_socket, buffer, BUFFER_SIZE, 0, &saddr, &saddr_len);
        if (data_size < 0) {
            perror("Failed to get packets");
            close(raw_socket);
            exit(EXIT_FAILURE);
        }

        // STEP 7: Extract the Ethernet header from the received packet
        struct ethhdr *eth = (struct ethhdr *)buffer;

        // Check if packet contains an IP packet (ETH_P_IP)
        if (ntohs(eth->h_proto) == ETH_P_IP) {
            // STEP 8: Extract the IP header from the packet (starts right after ethernet header)
            struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));

            // Setup structure to hold readable IP strings
            struct in_addr src_ip, dest_ip;
            src_ip.s_addr = iph->saddr;
            dest_ip.s_addr = iph->daddr;

            // STEP 9: Obtain and display Source IP, Destination IP, and Protocol number
            printf("Source IP      : %s\n", inet_ntoa(src_ip));
            printf("Destination IP : %s\n", inet_ntoa(dest_ip));
            printf("Protocol       : %d\n", iph->protocol);
            printf("----------------------------------------\n");
        }
    }

    // STEP 11 & 12: Close the socket and stop the program
    close(raw_socket);
    return 0;
}
