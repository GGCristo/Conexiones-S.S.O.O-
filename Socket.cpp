#include <iostream>
#include <cstring>
#include <cassert>
#include "Socket.h"

Socket::Socket(const sockaddr_in& address){
  
  int fd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd_ < 0) {
  std::cerr << "no se pudo crear el socket: " <<    
  std::strerror(errno) << '\n';
  assert(false);

  int result = bind(fd_, reinterpret_cast<const sockaddr*>(&address),
              sizeof(address));
  if (result < 0) {
  std::cerr << "falló bind: \n";
  assert(false);
}
}

}

Socket::~Socket(){
  close(fd_);
}