/* header sockets */

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


// Cria o socket de conexao
typedef void (*criar)(struct Server*);

// Aceita o socket na conexao
typedef void (*aceita)(struct Server*);

// Definição do socket Server
typedef struct ServerSocket
{
    char *HOST;
    int PORT;
    int meu_socket;
    int conexao;
    int cliente;
    int enviarMsg;
    char mensagem[256];
    struct sockaddr_in destino;

    //era pra ser um construtor da struct kk
   	void(*INIT)(struct Server*, char *host, int port);

   	//funcoes da struct
	criar CriarSocket;
	aceita AceitaConexao;

} Server;

// construtor de server
Server* Server_new(char *host, int port){
	Server* this = malloc(sizeof(Server));
  	this->HOST = host;
  	this->PORT = port;
  	return this;
}

//prototipos das funções
void Init(Server *this, char *host, int port);
void CriarSocket(Server *this);
void AceitaConexao(Server *this);
