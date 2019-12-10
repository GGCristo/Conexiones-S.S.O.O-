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
#include <array>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <exception>
#include <thread>
#include <new>

#include "Message_struct.h"
#include "Socket.h"

sockaddr_in make_ip_address (const std::string&, int);
// std::setlocale(LC_MESSAGES, "es_ES.utf8");
int main() {

    const sockaddr_in direccion = make_ip_address("127.0.0.1",0);
    const sockaddr_in servidor = make_ip_address("127.0.0.1",25000);
    Socket *conexion;
    try {
    conexion = new Socket (direccion);
    }
    catch (std::system_error &e) {
      std::cerr << e.what();
      return 1;
    }
    Message message;
    
    int file = open ("/home/cristo/Escritorio/Netcp/NetcpSend/prueba.txt", 0000);
    while ((read (file, message.text.data(), sizeof(&message))) != 0) {
      std::cout << message.text.data() << std::endl;
      try 
      {
        conexion -> send_to (message, servidor);
      } 
      catch (std::system_error &e) 
      {
        std::cerr << e.what();
        return 1;
      }
    } 
    delete conexion;
    return 0;
}

sockaddr_in make_ip_address (const std::string& ip_address, int port) { 
  
  // Dirección del socket local
  sockaddr_in local_address{};            // Así se inicializa a 0, como se recomienda
  local_address.sin_family = AF_INET;     // Pues el socket es de dominio AF_INET
  if (ip_address != "") 
  
    inet_aton (ip_address.c_str(), &local_address.sin_addr);
  
  else 
  
    local_address.sin_addr.s_addr = htonl(INADDR_ANY);

  local_address.sin_port = htons(port);
  return local_address;
}

