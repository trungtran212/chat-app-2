#include "server.h"
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>

using namespace std;

vector<int> clients;

void broadcastMessage(const string& message, int senderSock) {
    ofstream logFile("chat_log.txt", ios::app);
    logFile << message << endl;  // Lưu tin nhắn vào file
    logFile.close();  // Đảm bảo đóng file sau khi ghi

    for (int clientSock : clients) {
        if (clientSock != senderSock) {
            if (send(clientSock, message.c_str(), message.length(), 0) == -1) {
                perror("send failed");
            }
        }
    }
}

// void broadcastMessage(const string& message, int senderSock) {
//     ofstream logFile("chat_log.txt", ios::app);
//     logFile << message << endl;  // Lưu tin nhắn vào file
//     for (int clientSock : clients) {
//         if (clientSock != senderSock) {
//             send(clientSock, message.c_str(), message.length(), 0);
//         }
//     }
// }

void handleClient(int clientSock) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSock, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            close(clientSock);
            // clients.erase(remove(clients.begin(), clients.end(), clientSock), clients.end());
            break;
        }
        cout << "Tin nhắn từ client" << clientSock << ": " << buffer << endl;
        send(clientSock, buffer, bytesRead, 0);
        string message = string(buffer);
        broadcastMessage(message, clientSock);
    }
}

void runServer() {
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr, clientAddr;
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSock, 5);

    while (true) {
        socklen_t clientLen = sizeof(clientAddr);
        int clientSock = accept(serverSock, (sockaddr*)&clientAddr, &clientLen);
        clients.push_back(clientSock);
        thread clientThread(handleClient, clientSock);
        clientThread.detach();
    }

    close(serverSock);
}
