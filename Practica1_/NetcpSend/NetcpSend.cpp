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
int protected_main();
int comandos (std::exception_ptr& eptr, std::thread::id&);

int main() 
{
    try 
    {
      return protected_main();
    }    
    catch(std::bad_alloc& e) 
    {
        std::cerr << "mytalk" << ": memoria insuficiente\n";
        return 1;
    }
    catch(std::system_error& e) 
    {
      std::cerr << "mitalk" << ": " << e.what() << '\n';
      return 2;
    }
    catch (...) 
    {
      std::cout << "Error desconocido\n";
      return 99;
    }
   
}
int protected_main()
{
  const sockaddr_in direccion = make_ip_address("127.0.0.1",0);
  const sockaddr_in servidor = make_ip_address("127.0.0.1",25000);
  
  Socket conexion(direccion);

  std::thread::id main_id = std::this_thread::get_id();
  std::exception_ptr eptr {};
  std::thread hilo1(&comandos, std::ref(eptr), std::ref(main_id)); 
  
  Message message;
    
  int file = open ("/home/cristo/Escritorio/Netcp/NetcpSend/prueba.txt", 0000);
  while ((read (file, message.text.data(), sizeof(&message))) != 0) 
  {
      std::cout << message.text.data() << std::endl;
      conexion.send_to (message, servidor); 
  } 

  if (eptr) // Echar un ojo
    std::rethrow_exception(eptr);
  
  hilo1.join();
  return 0;
}

// Función hilo

int comandos(std::exception_ptr& eptr, std::thread::id& main_id)
{
  std::thread::id comandos_id = std::this_thread::get_id();

  std::cout << "Id_main: " << main_id << std::endl;
  std::cout << "Id_hilo: " << comandos_id << std::endl;

  std::string eleccion;
  while (eleccion != "Quit") 
  {
    std::cin >> eleccion;
    std::this_thread::sleep_for (std::chrono::seconds(1));
  }
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

