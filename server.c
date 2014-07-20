/*
  Create by Lucas Marques
*/

/* Server Socket*/
#include "server.h"

int main(int argc, char const *argv[])
{
	printf("I'm here\n");
	
	Server* server = Server_new("127.0.0.1", 1234);
	
	//inicializa as funcoes
	server->INIT = Init;
	server->CriarSocket = CriarSocket;
	server->AceitaConexao = AceitaConexao;

	server->CriarSocket(server);
	server->AceitaConexao(server);
	return 0;
}

void Init(Server *this, char *host, int port){
	this->HOST = host;
	this->PORT = port;
}

void CriarSocket(Server *this){
	printf("Host: %s - port: %d\n", this->HOST, this->PORT );

	this->meu_socket = socket(AF_INET,SOCK_STREAM,0);

	if(this->meu_socket == -1)
	{
		printf("Erro ao criar o socket!\n");
		exit(-1);
	}

    this->destino.sin_family = AF_INET;
    this->destino.sin_port = htons(this->PORT);
    this->destino.sin_addr.s_addr = inet_addr(this->HOST);
    bzero(&(this->destino.sin_zero),8);

	
	if(bind(this->meu_socket,(struct sockaddr*)&this->destino,sizeof(this->destino)) == -1)
	{
		printf("Erro na funcao bind()\n");
		exit(-1);
	}

	//listen() - para ouvir as conexões
	if(listen(this->meu_socket,1) == -1)
	{
		printf("Erro na funcao listen()\n");
		exit(-1);
	}
}

void AceitaConexao(Server *this){
	//parte do codigo para aceitar conexão de cliente
	printf("Aguardando cliente...\n");
	while(1)
	{
		//accept é usada para aceitar a conexão
		this->cliente = accept(this->meu_socket,0,0);

		if(this->cliente == -1)
		{
			printf("Erro na funcao accept()\n");
			exit(-1);
		}

		printf("Cliente conectado!\n\n");
	
		do{ 
		//sem esse loop, so seria possivel enviar uma mensagem
		fgets(this->mensagem,256,stdin);                                  
		/* Obtém uma mensagem digitada */
		this->mensagem[strlen(this->mensagem)-1] = '\0'; /*Finaliza a string */

		this->enviarMsg = send(this->cliente,this->mensagem,strlen(this->mensagem),0);
		} while(1);
            //close(cliente);
	}

}
