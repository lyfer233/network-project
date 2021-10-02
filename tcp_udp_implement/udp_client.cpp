#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>


constexpr size_t BUF_SIZE = 128;

void error_handle(std::string opt, std::string message) {
    // Obtain the failure reason according to the errno value and print it to the terminal
    perror(opt.c_str());
    std::cout << message << std::endl;
    exit(1);
}

int main(int argc, char *argv[])
{
    int current_socket;
    char message[BUF_SIZE];
    int str_len;
    socklen_t address_size;
    struct sockaddr_in server_address, from_address;

	// Judge the number of the parameters.
    if (argc < 3) {
        std::cout << "Usage : " << argv[0] << " <IP> <port>" << std::endl;
        exit(0);
    }

	// Start creating socket
    // If successfully called then return the file descriptor(int value), else return -1
    current_socket = socket(PF_INET, SOCK_DGRAM, 0);
    if (current_socket < 0) {
		error_handle("socket", "An error occurred while running the socket() function.");
    }

	// Initializes the structure information of the socket
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(atoi(argv[2]));

    while (true) {
		// input your transport message 
        std::cin >> message;
		// If input q then stop connect 
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        }

        // send message
        sendto(current_socket, message, strlen(message), 0, (struct sockaddr*)&server_address, sizeof(server_address));

		// clear the message
        memset(message, 0, BUF_SIZE);
		// calc size of struct socket size
        address_size = sizeof(from_address);
		// receive data from server
        str_len = recvfrom(current_socket, message, BUF_SIZE, 0, (struct sockaddr*)&from_address, &address_size);
		// add '0' into back of data
        message[str_len + 1] = 0;
		// output the message from receive
        std::cout << "Recv message : " << message << std::endl;

    }

	// Close the socket
	close(current_socket);

	return 0;
}
