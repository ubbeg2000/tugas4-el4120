#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_LENGTH 1024

int main(int argc, char **argv)
{

    WSADATA wsa_data;
    SOCKET receiving_socket;
    SOCKADDR_IN receiver_addr;
    SOCKADDR_IN sender_addr;

    int port = 8888;
    char receive_buf[MAX_BUFFER_LENGTH];
    int sender_addr_size = sizeof(sender_addr);
    int byte_recieved = 5;

    // Initialize Winsock version 2.2
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        printf("WSAStartup failed with error: %ld\n", WSAGetLastError());
        return -1;
    }

    // Create a new socket to receive datagrams on.
    receiving_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (receiving_socket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    // Set up a SOCKADDR_IN structure that will tell bind that we want to receive datagrams from
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(port);
    receiver_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Associate the address information with the socket using bind.
    // At this point you can receive datagrams on your bound socket.
    if (bind(receiving_socket, (SOCKADDR *)&receiver_addr, sizeof(receiver_addr)) == SOCKET_ERROR)
    {
        printf("Error! bind() failed!\n");
        closesocket(receiving_socket);
        WSACleanup();
        return -1;
    }

    // Print some info on the receiver(Server) side...
    getsockname(receiving_socket, (SOCKADDR *)&receiver_addr, (int *)sizeof(receiver_addr));

    printf("Receiving IP(s) used: %s\n", inet_ntoa(receiver_addr.sin_addr));
    printf("Receiving port used: %d\n", htons(receiver_addr.sin_port));
    printf("I\'m ready to receive data packages. Waiting...\n\n");

    // At this point you can receive datagrams on your bound socket.
    while (1)
    {
        byte_recieved = recvfrom(receiving_socket, receive_buf, MAX_BUFFER_LENGTH, 0, (SOCKADDR *)&sender_addr, &sender_addr_size);
        if (byte_recieved > 0)
        {
            printf("Data Recieved: %s\n", receive_buf);
        }
        else if (byte_recieved <= 0)
        {
            printf("Connection closed with error code: %ld\n", WSAGetLastError());
        }
        else
        {
            printf("recvfrom() failed with error code: %d\n", WSAGetLastError());
        }
    }

    if (closesocket(receiving_socket) != 0)
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