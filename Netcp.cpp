#pragma region 
/**
 * @file Netcp.cpp
 * @author Cristo_García_González (cristo.code@gmail.com)
 * @brief Primer acercamiento a conexiones (S.S.O.O)
 * @version 0.2
 * @date 2019-12-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma endregion

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "Socket.h"
sockaddr_in make_ip_address(const std::string& ip_address, int port);
// int inet_aton(const char *cp, struct in_addr *inp);
int main(){

  

    return 0;
}

sockaddr_in make_ip_address(const std::string& ip_address, int port) { 
  // Dirección del socket local
  sockaddr_in local_address{};            // Así se inicializa a 0, como se recomienda
  local_address.sin_family = AF_INET;     // Pues el socket es de dominio AF_INET
  if (ip_address != "") {
    inet_aton (ip_address.c_str(), &local_address.sin_addr);
  }
  else local_address.sin_addr.s_addr = htonl(INADDR_ANY);
  local_address.sin_port = htons(0);
  return local_address;
}

