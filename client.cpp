//
// Created by Cyril on 12-Aug-24.
//

#include "winsock2.h"
#include <iostream>
#include <thread>

void sendPacket(std::string data);
void receiveOutput();
char * translateEncryptionKey(std::string encryptionKey);
std::string XOR(std::string data, const char key[]);

int main() {

    std::thread receiveOutputThread(receiveOutput);

    while (true) {

        // Initialize WinSock
        WSAData wsaData{};

        // Start WSA
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cout << "An error occurred when starting WSA." << std::endl;
            return 1;
        }

        // Create ClientSocket
        auto clientSocket = INVALID_SOCKET;

        clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            std::cout << "An error occurred when creating client socket." << std::endl;
            WSACleanup();
            return 1;
        }

        // Allow for broadcast sending
        char broadcast = '1';
        if (setsockopt(clientSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
            std::cout << "An error occurred when changing broadcast settings." << std::endl;
            closesocket(clientSocket);
            WSACleanup();
        }

        // Configure for broadcast send on port 888
        struct sockaddr_in clientSocketConfig{};

        clientSocketConfig.sin_family = AF_INET;
        clientSocketConfig.sin_port = htons(666);
        clientSocketConfig.sin_addr.s_addr = inet_addr("192.168.1.255");

        std::string userMessage;
        std::getline(std::cin, userMessage);

        std::string message = userMessage; //TODO: fix encryption being too big aka not fitting in UDP :skull:

        // Send UDP packet to broadcast
        sendto(clientSocket, message.c_str(), strlen(message.c_str()) + 1, 0, (sockaddr *) &clientSocketConfig,
               sizeof(clientSocketConfig));

        // Cleanup
        closesocket(clientSocket);
        WSACleanup();
    }
}

void receiveOutput() {

    while (true) {

        // Initialize WinSock
        WSAData wsaData{};

        // Start WSA
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cout << "An error occurred when starting WSA." << std::endl;
        }

        // Create ServerSocket
        auto serverSocket = INVALID_SOCKET;

        serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            std::cout << "An error occurred when creating server socket." << std::endl;
            WSACleanup();
        }

        // Allow for broadcast receiving
        char broadcast = '1';
        if (setsockopt(serverSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
            std::cout << "An error occurred when changing broadcast settings." << std::endl;
            closesocket(serverSocket);
            WSACleanup();
        }

        // Configure for broadcast receive on port 666
        struct sockaddr_in serverSocketConfig{};
        struct sockaddr_in clientSocketConfig{};

        int len = sizeof(struct sockaddr_in);
        char recvbuff[65535];
        int recvbufflen = 65535;

        serverSocketConfig.sin_family = AF_INET;
        serverSocketConfig.sin_port = htons(667);
        serverSocketConfig.sin_addr.s_addr = INADDR_ANY;

        // Bind client socket to listen for broadcasts
        if (bind(serverSocket, (sockaddr *) &serverSocketConfig, sizeof(serverSocketConfig)) < 0) {
            std::cout << "An error occurred when binding server socket." << std::endl;
            closesocket(serverSocket);
            WSACleanup();
        }

        // Receive incoming data from ClientSocket
        recvfrom(serverSocket, recvbuff, recvbufflen, 0, (sockaddr *) &clientSocketConfig, &len);

        std::string decryptedString = recvbuff; //TODO: fix encryption being too big aka not fitting in UDP :skull:

        // Show output received
        std::cout << "\n"
        << decryptedString << std::endl;

        // Cleanup
        closesocket(serverSocket);
        WSACleanup();
    }
}

char * translateEncryptionKey(std::string encryptionKey) { const int length = encryptionKey.length(); char* char_array = new char[length + 1]; strcpy(char_array, encryptionKey.c_str()); return char_array; }

std::string XOR(std::string data, const char key[]) { std::string xorstring = data; for (int i = 0; i < xorstring.size(); i++) { xorstring[i] = data[i] ^ key[i % (sizeof(key) / sizeof(char))]; } return xorstring; }
