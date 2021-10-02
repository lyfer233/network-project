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
	int client_socket; 
	struct sockaddr_in server_address;
	char message[128];
	int str_len;
	
	// Judge the number of the parameters.
	if (argc < 3) {
		std::cout << "Usage : " << argv[0] << " <IP> <port>" << std::endl;
		exit(1);
	}
	
	// Start creating socket
	// If successfully called then return the file descriptor(int value), else return -1
	client_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (client_socket < 0) {
		error_handle("socket", "An error occurred while running the socket() function.");
	}

	// Initializes the structure information of the socket
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(argv[1]); 
	server_address.sin_port = htons(atoi(argv[2])); 

	// Establish a connection to the server 
	// If bind() successful bind then return 0, else return -1
	if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
		error_handle("bind", "An error occurred while running the bind() function.");
	}
	
	str_len = read(client_socket, message, sizeof(message) - 1);
	if (str_len < 0) {
		error_handle("read", "An error occurred while running the read() function.");
	}	

	// output message from server
	std::cout << "Recv Message : " << message << std::endl;

	// Close local socket
	close(client_socket);
	return 0;
}
