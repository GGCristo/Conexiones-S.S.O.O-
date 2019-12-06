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

  // Enviar un mensaje "¡Hola, mundo!" al socket remoto
  std::string message_text("¡Hola, mundo!");

  Message message;
  message_text.copy (message.text.data(), message.text.size() - 1, 0);
  send_to (message, address);
}
}

}

Socket::~Socket(){
  close(fd_);
}
void Socket::send_to(const Message& message, const sockaddr_in& address){
  
  

  int result = sendto(fd_, &message, sizeof(message), 0,
                      reinterpret_cast<const sockaddr*>(&address),
                      sizeof(address));
  if (result < 0) {
  std::cerr << "falló sendto: " << std::strerror(errno) << '\n';
  }
}