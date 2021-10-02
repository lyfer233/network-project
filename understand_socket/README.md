# Implementation ideas
When I want to simulate a C/S communication mode in linux environment(TCP mode), I should:
- Establish the socket related content of the server
- Establish the socket related content of the client 

## Server details
1. Create the socket in local.
2. Initialize the IP address and port of the socket.
3. Turn the socket socket into a state that can receive requests.
4. Receive the connection request and return the file descriptor.

## Client details
1. Create the socket in local.
2. Config IP address and port of the server into socket
3. Send the socket connection request, then receive return content.

# API function in linux
**"Everything is a file" in linux**

## socket() function
`int socket(int domain, int type, int protocal);`

creates an endpoint for communication and returns a file descriptor that refers to that endpoint.  The file descriptor returned by a successful call will be the lowest-numbered file descriptor not currently open for the process.
The domain argument specifies a communication domain;this selects the protocol family which will be used for communication. examples: `AF_INET`(Ipv4 protocols), `AF_INET6`(Ipv6 protocols), `AF_UNIX`(local communication) 

The socket has the indicated type, which specifies the communication semantics.  Currently defined types are: `SOCK_STREAM`(TCP), `SOCK_DGRAM`(UDP)

Most case the protocal can be specified as 0.

## bind() function
`int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);`

When a socket is created with socket, it exists in a name space but has no address assigned to it.So bind() assigns the address specified by `addr` to the socket referred to by the file descriptor *sockfd*, *addrlen*
specifies the size, the address structure pointed to by *addr*


## listen() function
`int listen(int sockfd, int backlog);`

`int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`

## connect() function
`int connect`

## open() function
`int open(const char *path, int flag);`

## close() function
`int close(int fd);`

## write() function
`ssize_t write(int fd, const void *buf, size_t nbytes);`

## read() function
`ssize_t read(int fd, void *buf, size_t nbytes);`

## another details

### File Descriptor
a file descriptor (FD, less frequently fildes) is a unique identifier (handle) for a file or other input/output resource, such as a pipe or network socket.
File descriptors typically have non-negative integer values, with negative values being reserved to indicate "no value" or error conditions.
If FD is 0 then obj is standard input,
If FD is 1 then obj is standard outpu,
If FD is 2 then obj is standard Error.

### sockaddr_in


# Reference Linked:
- https://man7.org/linux/man-pages/man2/socket.2.html
- https://man7.org/linux/man-pages/man2/bind.2.html
