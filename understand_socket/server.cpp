#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>


void error_handle(std::string opt, std::string message) {
	// Obtain the failure reason according to the errno value and print it to the terminal
	perror(opt.c_str());
	std::cout << message << std::endl;
	exit(1);
}

int main(int argc, char *argv[]) {
	int server_socket;
	int client_socket;
	
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	
	socklen_t client_addr_size;
	char message[] = "The successfully connection~";

	// Judge the number of the parameters.
	if (argc < 2) {
		std::cout << "Usage : " << argv[0] << " <port>" << std::endl;
		exit(1);
	}
	
	// Start creating socket
	// If successfully called then return the file descriptor(int value), else return -1
	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		error_handle("socket", "An error occurred while running the socket() function.");
	}

	// Initializes the structure information of the socket
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY); // Select any network card currently available
	server_address.sin_port = htons(atoi(argv[1])); // Select the port number to receive message

	// Binding the port number and socket
	// If bind() successful bind then return 0, else return -1
	if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
		error_handle("bind", "An error occurred while running the bind() function.");
	}
	
	// Listening port and set the number of waiting queues.
	// If listen() successful call then return 0, else return -1
	if (listen(server_socket, 5) < 0) {
		error_handle("listen", "An error occurred while running the listen() function.");	
	} 
	
	// Printing output and waiting for connection
	std::cout << "Waiting Client......" << std::endl;

	client_addr_size = sizeof(client_address);

	// Wait for the receiving client to establish a connection
	client_socket = accept(server_socket, (struct sockaddr*)&client_socket, &client_addr_size);
	if (client_socket < 0) {
		error_handle("accept", "An error occurred while running the accept() function.");
	}

	// After the accpet() is successfully called, the server will get the IP address
    // and port number of the client. then print client IP address and port
	std::cout << "Client Ip : " << inet_ntoa(client_address.sin_addr) << ", port : " << \
	ntohs(client_address.sin_port) << std::endl;
	
	// Send message to client 
	write(client_socket, message, sizeof(message)); 
	
	// Close the TCP connection
	close(client_socket);

	// Close the socket 
	close(server_socket);

	return 0;
}
