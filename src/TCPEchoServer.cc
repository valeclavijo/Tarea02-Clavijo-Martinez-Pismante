/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "YASL.h"      // For Socket, ServerSocket, and SocketException
#include <iostream>    // For cerr and cout
#include <cstdlib>     // For atoi()

const uint32_t RCVBUFSIZE = 32;    // Size of receive buffer

// TCP client handling function
void HandleTCPClient(TCPSocket *sock) {
  std::cout << "Handling client ";
  try {
    std::cout << sock->getForeignAddress() << ":";
  } catch (SocketException e) {
    std::cerr << "Unable to get foreign address" << std::endl;
  }
  try {
    std::cout << sock->getForeignPort();
  } catch (SocketException e) {
    std::cerr << "Unable to get foreign port" << std::endl;
  }
  std::cout << std::endl;
//*MODIFICACIÓN*//

  sock->send("HTTP/1.1 200 OK\r\n", 17);
  sock->send("Content - Type: text/html\r\n\r\n",27);
  

  //lee archivo HTML//

  std::string linea;
  std::string html == "";
  std::ifstream archivo ("../www-data/pagina1.html");

  if (archivo.is_open()){
    while(getLine(archivo,linea)){
      html = html + linea + "\n";
    }
    archivo.close();
  }else{
    std::cout <<"no se puede abrir">>;
  }

//se envia el HTML//
  sock-> send(html.c_src(), html.length());
  delete sock;
}

int main(int argc, char *argv[]){

  checkArgs* argumentos = new checkArgs(argc. argv);
  uint16_t echoServPort;
  echoServPort = argumentos-> getArgs().PORT;  // First arg: local port


  try {
    TCPServerSocket servSock(echoServPort);     // Server Socket object
  
    for (;;) {   // Run forever
      HandleTCPClient(servSock.accept());       // Wait for a client to connect
    }
  } catch (SocketException &e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  // NOT REACHED

  return EXIT_SUCCESS;
}
