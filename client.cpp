#include "client.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <arpa/inet.h>


using namespace std;

void receiveMessages(int clientSock) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSock, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            cout << "Message: " << buffer << endl;
        }
    }
}

// void runClient() {
//     int clientSock = socket(AF_INET, SOCK_STREAM, 0);
//     sockaddr_in serverAddr;

//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_port = htons(8080);
//     serverAddr.sin_addr.s_addr = INADDR_ANY;

//     connect(clientSock, (sockaddr*)&serverAddr, sizeof(serverAddr));

//     thread receiver(receiveMessages, clientSock);
//     receiver.detach();

//     while (true) {
//         string message;
//         cout << "Enter message: ";
//         getline(cin, message);
//         send(clientSock, message.c_str(), message.length(), 0);
//     }

//     close(clientSock);
// }
void runClient() {
    int clientSock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(clientSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("connect failed");
        return;
    }

    string message;
    while (true) {
        cout << "Enter message: ";
        getline(cin, message);

        if (send(clientSock, message.c_str(), message.length(), 0) == -1) {
            perror("send failed");
        }
    }
    close(clientSock);
}