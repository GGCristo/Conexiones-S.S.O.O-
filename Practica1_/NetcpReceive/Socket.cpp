#include <iostream>
#include <cstring>
#include <cassert>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Socket.h"

Socket::Socket(const sockaddr_in& address){
  
  fd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd_ < 0) {
    throw std::system_error(errno,std::system_category(), "No se pudó crear el Socket");
  }
  int result = bind (fd_, reinterpret_cast<const sockaddr*>(&address),
              sizeof(address));
  if (result < 0) {
    throw std::system_error(errno,std::system_category(), "Falló el bind");
  }
}

Socket::~Socket(){
  close(fd_);
  std::cout << "Memoria del receptor liberada" << std::endl;
}

void Socket::send_to (const Message& message, const sockaddr_in& address){
  
  int result = sendto (fd_, &message, sizeof(message), 0,
                      reinterpret_cast<const sockaddr*>(&address),
                      sizeof(address));
  if (result < 0) {
    throw std::system_error(errno,std::system_category(), "falló sendto");
  }
}

void Socket::receive_from (Message& message, sockaddr_in& address){
  socklen_t src_len = sizeof(address);
  int result = recvfrom (fd_, &message, sizeof(message), 0,
                         reinterpret_cast<sockaddr*>(&address), &src_len);
  if (result < 0) {
    throw std::system_error(errno,std::system_category(), "falló recvfrom");
  }

  // Vamos a mostrar el mensaje recibido en la terminal

  // Primero convertimos la dirección IP como entero de 32 bits
  // en una cadena de texto.
  char* remote_ip = inet_ntoa(address.sin_addr);

  // Recuperamos el puerto del remitente en el orden adecuado para nuestra CPU
  int remote_port = ntohs(address.sin_port);

  // Imprimimos el mensaje y la dirección del remitente
  message.text[1023] = '\0';
  std::cout << "El sistema " << remote_ip << ":" << remote_port <<
  " envió el mensaje '" << message.text.data() << "'\n";
}
