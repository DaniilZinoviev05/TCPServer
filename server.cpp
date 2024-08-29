#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>

#define PORT 3455

int main()
{
    // socket AF_INET - IPv4, SOCK_STREAM- для tcp
    int listen = socket(AF_INET, SOCK_STREAM, 0);
    //стр-а для сокета/ хранит порт 
    struct sockaddr_in sock_adr;

    if (listen < 0)
    {
        std::cerr << "Не удалось создать сокет.\n";
        return -1;
    }

    std::cout << "Сокет успешно создан.\n";

    sock_adr.sin_port = htons(PORT);
    sock_adr.sin_family = AF_INET; // ipv4
    sock_adr.sin_addr.s_addr = htons(INADDR_ANY); // Все ip 

    int socket_bind = bind(listen, (struct sockaddr*)&sock_adr, sizeof(sock_adr));

    if (socket_bind > 0)
    {
        std::cerr << "Проблема с подключением сокета.\n";
    }
} 