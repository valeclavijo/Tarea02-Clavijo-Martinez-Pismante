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
#include "checkArgs.h"  //agregamos la libreria check args para poder utilizar sus funciones
#include <iostream>    // For cerr and cout
#include <cstdlib>     // For atoi()
#include <iostream>			//utilizamos esta libreria para poder leer los archivos
#include <fstream>			//utilizamos esta libreria para poder leer los archivos

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
	char echoBuffer[RCVBUFSIZE];
	uint32_t recvMsgSize;
	
	recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE); 
	std::cout << recvMsgSize + "\n";
	//SE ENVIA A TRAVES DEL SOCKET EL RESPONSE AL REQUEST INICIAL
	
	sock ->send("HTTP/1.1 200 OK\r\n",32);
	sock ->send("Content-Type: text/html\r\n\r\n",27);
	
	//sock->send(status.c_str(),status.length());

  //lee archivo HTML//
  std::string linea;
  std::string html = "";
	std::string rqe(echoBuffer, 5,12);
	std::string a1 = "pagina1.html";
	std::string a2 = "pagina2.html";
	std::string a3 = "pagina3.html";

  std::ifstream archivo ("../www-data/pagina1.html");
//crear una variable para c/u y compararlla con strings dentro de unos if else
	std::ifstream archivo1 ("../www-data/pagina2.html");
	std::ifstream archivo2 ("../www-data/pagina3.html");
	std::ifstream archivoE ("../www-error/error404.html");

	if (rqe==a1){
		if (archivo.is_open()){
    	while(getline(archivo,linea)){
     	 html = html + linea + "\n";
    	}
    	archivo.close();
  	}else{
    	std::cout << "no se puede abrir" << "\n";
  	}
	  sock->send(html.c_str(), html.length());
  	delete sock;
	}


	if else (rqe==a2){
		if (archivo1.is_open()){
    	while(getline(archivo1,linea)){
     	 html = html + linea + "\n";
    	}
    	archivo1.close();
  	}else{
    	std::cout << "no se puede abrir" << "\n";
  	}
		sock->send(html.c_str(), html.length());
  	delete sock;
	}

	if else (rqe==a3){
		if (archivo2.is_open()){
    	while(getline(archivo2,linea)){
     	 html = html + linea + "\n";
    	}
    	archivo2.close();
  	}else{
    	std::cout << "no se puede abrir" << "\n";
  	}
		sock->send(html.c_str(), html.length());
  	delete sock;
	}
 else{
			if (errorE.is_open()){
    	while(getline(errorE,linea)){
     	 html = html + linea + "\n";
    	}
    	errorE.close();
  	}else{
    	std::cout << "no se puede abrir" << "\n";
  	}
		sock->send(html.c_str(), html.length());
  	delete sock;
	}

}


int main(int argc, char *argv[]){

  checkArgs* argumentos = new checkArgs(argc, argv);
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
