#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdlib>
#include <cstdio>
#include <error.h>

const int one = 1;

int main(int argc, char ** argv){
    if(argc!=2)
        error(1,0,"Usage: %s <port>", argv[0]);
    
    sockaddr_in localAddress{
        .sin_family = AF_INET,
        .sin_port   = htons(atoi(argv[1])),
        .sin_addr   = {htonl(INADDR_ANY)}
    };
    
    int servSock = socket(PF_INET, SOCK_STREAM, 0);
    setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    
    if(bind(servSock, (sockaddr*) &localAddress, sizeof(localAddress)))
        error(1,errno,"Bind failed!");
    
    listen(servSock, 1);

    while(true) {
        accept(servSock, nullptr, nullptr);
        printf("Accepted a new connection, ignoring it.\n");
    }
}
