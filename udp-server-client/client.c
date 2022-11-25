#include <winsock2.h>
#include <stdio.h>
#include "../lib/date.h"

#define MAX_BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    WSADATA wsa_data;
    SOCKET sending_socket;
    SOCKADDR_IN receiver_addr;
    int port = 8888;
    char send_buf[MAX_BUFFER_SIZE];

    if (argc != 2)
    {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock version 2.2
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        printf("WSAStartup failed with error %ld\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    // Create a new socket to receive datagrams on.
    sending_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sending_socket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    // Set up a SOCKADDR_IN structure that will identify who we will send datagrams to
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(port);
    receiver_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // Send data packages to the receiver(Server).
    get_time(send_buf);

    // Print user's input and a progress message
    printf("Data to send: %s\n", send_buf);

    sendto(sending_socket, send_buf, MAX_BUFFER_SIZE, 0, (SOCKADDR *)&receiver_addr, sizeof(receiver_addr));

    // When your application is finished receiving datagrams close the socket.
    if (closesocket(sending_socket) != 0)
    {
        printf("closesocket() failed! Error code: %ld\n", WSAGetLastError());
    }

    // When your application is finished call WSACleanup.
    if (WSACleanup() != 0)
    {
        printf("WSACleanup() failed! Error code: %ld\n", WSAGetLastError());
    }

    // Back to the system
    return 0;
}