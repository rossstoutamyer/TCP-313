#include "common.h"
#include "TCPreqchannel.h"
#include <sys/socket.h>

using namespace std;

TCPRequestChannel::TCPRequestChannel(const string hostname, const string port_no) {

    if (hostname != ""){
        struct addrinfo c;
        struct addrinfo *p;
        memset(&c, 0, sizeof(c));

        c.ai_family = AF_UNSPEC;
        c.ai_socktype = SOCK_STREAM;
        int status;

        if((status = getaddrinfo((char*) hostname.c_str(), (char*) port_no.c_str(), &c, &p)) != 0) {
            cerr << "getaddrinfo" << endl;
            exit(-1);
        }

        if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            //perror("Failed socket client");
            close(sockfd);
            exit(-1);
        }
        if(connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("Failed connect client");
            close(sockfd);
            exit(-1);
        }

        freeaddrinfo(p);

        //cout << "Client Connected" << endl;
    } else {
        cout << "Hostname: " << hostname << endl;
        struct addrinfo c;
        struct addrinfo *p;
        struct sockaddr_storage info;
        socklen_t socksize;

        char buf[INET6_ADDRSTRLEN];
        int status;
        
        memset(&c, 0, sizeof(c));

        c.ai_family = AF_UNSPEC;
        c.ai_socktype = SOCK_STREAM;
        c.ai_flags = AI_PASSIVE;

        if((status = getaddrinfo(NULL, (char*) port_no.c_str(), &c, &p)) != 0) {
            cerr << "getaddrinfo" << endl;
            exit(-1);
        }

        if(sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol) == -1){
            cout << "Failed socket server" << endl;
            close(sockfd);
        }
        if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1){
            cout << "Failed bind server" << endl;
            close(sockfd);
        }

        freeaddrinfo(p);

        if(listen(sockfd, 20) == -1) {
            cout << "Failed listen server" << endl;
            close(sockfd);
        }
        cout << "Server Ready!" << endl;
    }
}

TCPRequestChannel::TCPRequestChannel(int isockfd) {
    //For after connection??
    sockfd = isockfd;
}

TCPRequestChannel::~TCPRequestChannel() {
    close(sockfd);
}

int TCPRequestChannel::cread(void* msgbuf, int buflen){
    return recv(sockfd, msgbuf, buflen, 0);
}

int TCPRequestChannel::cwrite(void* msgbuf, int msglen){
    return send(sockfd, msgbuf, msglen, 0);
}

int TCPRequestChannel::getfd(){
    return sockfd;
}