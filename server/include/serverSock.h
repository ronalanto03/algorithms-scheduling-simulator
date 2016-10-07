/**
 @file servidorSTREAM.c
 @brief Prueba de sockets AF_INET usando SOCKSTREAM
 
 @author R. Rivas 
         rafael@ula.ve
*/
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include"eventData.h"
#include<cstdio>
///#include<pthread.h>

#define PUERTO 31040

void *hilo(void *);
int s;

class ServerSock{
	private:

		int t, n,  r;
		socklen_t tamNombreRemoto;
		struct sockaddr_in nombreLocal;
		struct sockaddr_in nombreRemoto;

	public:
		ServerSock(){
			nombreLocal.sin_family = AF_INET;
			nombreLocal.sin_port = htons(PUERTO);
			nombreLocal.sin_addr.s_addr = INADDR_ANY;
	
			if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
				std::cerr<<("abriendo socket");
				return;//(1);
			}

			//se vincula la direccion con el socket(puede fallar)
			if (bind(s, (struct sockaddr *)&nombreLocal,  sizeof(nombreLocal)) < 0) {
				perror("haciendo el bind");
				return;//(2);
			}

			if (listen(s, 1 ) < 0 ) {
				std::cerr<<("en el listen");
				return;//(3);
			}


			tamNombreRemoto = sizeof(struct sockaddr_in);
			if ((t = accept(s, (sockaddr *)&nombreRemoto, (socklen_t *)&tamNombreRemoto)) < 0) {
				std::cerr<<("en el accept");
				std::cout<<(" t = %d \n", t);
                return;;
			}

		}
		~ServerSock(){
			close (t);
			close(s);
		}


		struct EventData readSock(){
			struct EventData eventData;
			r = read(t, (char *)(&eventData), sizeof(struct EventData));
			return eventData; 
		}


		struct EventData writeSock(struct EventData eventData){
			r = write(t, (char *)(&eventData), sizeof(struct EventData));
			return eventData; 
		}

};
