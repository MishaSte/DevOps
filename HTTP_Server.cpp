#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "FuncA.h"

#define PORT 8081

// HTTP headers
char HTTP_200_HEADER[] = "HTTP/1.1 200 OK\r\n";
char HTTP_404_HEADER[] = "HTTP/1.1 404 Not Found\r\n";

// Function to create and run the HTTP server
void CreateHTTPserver() {
    int connectionSocket, clientSocket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket
    if ((connectionSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configuring server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding socket to the port
    if (bind(connectionSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding failed");
        close(connectionSocket);
        exit(EXIT_FAILURE);
    }

    // Listening for incoming connections
    if (listen(connectionSocket, 10) < 0) {
        perror("Listening failed");
        close(connectionSocket);
        exit(EXIT_FAILURE);
    }

    printf("\n+++++++ Server is running on port %d ++++++++\n", PORT);

    while (1) {
        printf("\n+++++++ Waiting for a new connection ++++++++\n");

        // Accepting a new connection
        if ((clientSocket = accept(connectionSocket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }

        char buffer[30000] = {0};
        read(clientSocket, buffer, sizeof(buffer));
        printf("Request received:\n%s\n", buffer);

        // Check if the request path is "/compute"
        if (strstr(buffer, "/compute")) {
            auto start = std::chrono::high_resolution_clock::now();

            // Generate and process data
            std::vector<double> results;
            FuncA trigCalculator;
            int num_elements = 20000000; // Adjust to achieve ~20 seconds
            for (int i = 0; i < num_elements; ++i) {
                results.push_back(trigCalculator.calculate(i % 10));
            }
            std::sort(results.begin(), results.end());

            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            // Preparing response
            char response[1024];
            sprintf(response,
                    "%sContent-Type: text/plain\r\nContent-Length: %ld\r\n\r\nArray sorted. Time elapsed: %ld ms\n",
                    HTTP_200_HEADER, strlen(std::to_string(elapsed).c_str()) + 50, elapsed);

            write(clientSocket, response, strlen(response));
            printf("\nResponse sent: Time elapsed = %ld ms\n", elapsed);
        } else {
            // Handling unknown route
            sprintf(buffer, "%sContent-Type: text/plain\r\nContent-Length: 13\r\n\r\n404 Not Found", HTTP_404_HEADER);
            write(clientSocket, buffer, strlen(buffer));
        }

        // Close the connection
        close(clientSocket);
    }

    close(connectionSocket);
}

