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

int main(int argc, char *argv[]) {
	int server_socket;
	char message[BUF_SIZE];
	int str_len;
	socklen_t client_address_size;
	struct sockaddr_in server_address, client_address;
	
	// Judge the number of the parameters.
    if (argc < 2) {
        std::cout << "Usage : " << argv[0] << " <port>" << std::endl;
        exit(0);
    }

	// Start creating socket
    // If successfully called then return the file descriptor(int value), else return -1
    server_socket = socket(PF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        error_handle("socket", "An error occurred while running the socket() function.");
    }

	// Initializes the structure information of the socket
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);;
    server_address.sin_port = htons(atoi(argv[1]));

	
	// Binding the port number and socket
	// If bind() successful bind then return 0, else return -1
	if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
		error_handle("bind", "An error occurred while running the bind() function.");
	}
	
    while (true) {
		// clear the message to receive next message
		memset(message, 0, BUF_SIZE);
		
		// calc client struct size and receive data in future
		client_address_size = sizeof(client_address);
		
		// It not only receives the data sent by the other party, but also 
		// records the IP address and port number of the other party 
		 str_len = recvfrom(server_socket, message, BUF_SIZE, 0, (struct sockaddr*)&client_address, &client_address_size);
		
		// output receive message
		std::cout << "Recv message :" << message << std::endl;
		
		// The IP address and port number information of the sender returned by recvfrom 
		// is sent back again by SendTo. 
		sendto(server_socket, message, str_len, 0, (struct sockaddr*)&client_address, client_address_size);
	}

	return 0;
}
