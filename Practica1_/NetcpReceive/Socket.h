#pragma region 
/**
 * @file Socket.h
 * @author Cisto_García_González (cgg.code@gmail.com)
 * @brief 
 * @version 0.2
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma endregion
#pragma once
#include <netinet/ip.h>
#include <unistd.h>

#include "Message_struct.h"

class Socket {
private:
  int fd_;
public:
  #pragma region 
  /**
   * @brief Crear un socket, mediante la llamada al sistema socket(), cuyo descriptor se almacena en el atributo privado “fd_” para que lo puedan utilizar otros métodos de la clase.
   *        Vincular dicho socket a la dirección de Internet especificada mediante el argumento ‘address’ del constructor, utilizando la llamada al sistema bind().
   * 
   */
  #pragma endregion
  Socket (const sockaddr_in&);
  #pragma region 
  /**
   * @brief Destroy the Socket object
   * 
   */
  #pragma endregion
  ~Socket();
  #pragma region 
  /**
   * @brief Enviar datos a otro proceso
   * 
   */
  #pragma endregion
  void send_to(const Message&, const sockaddr_in&);
  #pragma region 
  /**
   * @brief Recibir datos de otros procesos
   * 
   */
  #pragma endregion
  void receive_from(Message&, sockaddr_in&);
};