#include <iostream>
#include <cstring>
#include <cassert>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <clocale>
#include <exception>

#include "Message_struct.h"
#include "Socket.h"

Socket::Socket(const sockaddr_in& address){
  
  fd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd_ < 0) {
    throw std::system_error(errno,std::system_category(), std::strerror(errno));
  }

  int result = bind(fd_, reinterpret_cast<const sockaddr*>(&address),
                    sizeof(address));
  if (result < 0) {
    throw std::system_error(errno,std::system_category(), std::strerror(errno));
  }
  
}

Socket::~Socket(){
  close(fd_);
  std::cout << "Memoria liberada" << std::endl;
}

int Socket::get_fd() {
  return fd_;
}

void Socket::send_to(const Message& message, const sockaddr_in& address){
  
  int result = sendto(fd_, &message, sizeof(message), 0,
                      reinterpret_cast<const sockaddr*>(&address),
                      sizeof(address));
  if (result < 0) {
    throw std::system_error(errno,std::system_category(), std::strerror(errno));
  }

}
void Socket::receive_from(Message& message, sockaddr_in& address){
  
  socklen_t src_len = sizeof(address);
  int result = recvfrom(fd_, &message, sizeof(message), 0,
    reinterpret_cast<sockaddr*>(&address), &src_len);
  if (result < 0) {
    std::cerr << "falló recvfrom: " << std::strerror(errno) << '\n';
    assert(false);
  }
}
