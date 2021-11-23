#ifndef _FIFOreqchannel_H_
#define _FIFOreqchannel_H_
#include "common.h"
#include <string>
#include <iostream>
#include <netdb.h>

class TCPRequestChannel{
private:
    int sockfd;

public:
    TCPRequestChannel(const string hostname, const string port_no);
    TCPRequestChannel(int isockfd);
    ~TCPRequestChannel();
    int cread(void* msgbuf, int buflen);
    int cwrite(void* msgbuf, int msglen);
    int getfd();
};

#endif