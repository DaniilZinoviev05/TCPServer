#include "socket.h"

int main(void){
    int server, bind_socket, listen_socket; // дескриптор сокета
    int connection;

    // созд-м сок-т AF_INET - IPv4, SOCK_STREAM - потоковое соедин-е 
    //0 - протокол по умолч. для соединения
    server = socket(AF_INET, SOCK_STREAM, 0);

    if (server <= 0){
        std::cerr << "Ошибка с сокетом.\n";
    } 

    std::cout << "Сокет успешно создан.\n";

    // указываем ip и порт 
    struct sockaddr_in adr;
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = INADDR_ANY; // подключения со всех ip
    adr.sin_port = htons(PORT);

    int addr_len = sizeof(adr);

    // подвязываем сок-т к ip и порту 
    bind_socket = bind(server, (struct sockaddr*) &adr, addr_len);

    if(bind_socket == -1){
        std::cerr << "Ошибка при привязываении сокета.\n";
    }

    // прослушиваем 
    listen_socket = listen(server, 5);

    if(listen_socket == -1){
        std::cerr << "Ошибка при прослушке.\n";
    }

    std::cout << "Сервер прослушивает. Порт - " << PORT << std::endl;

    connection = accept(server, (struct sockaddr *)&adr, (socklen_t *)&addr_len);

    if(connection == -1){
        std::cerr << "Ошибка соединения.\n";
    }

    std::cout << "Соединение установлено.\n";

    char buffer[1024] = {0};
    int bytesReceived = recv(connection, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        std::cout << "Получено сообщение: " << buffer << std::endl;
        send(connection, buffer, bytesReceived, 0);
        std::cout << "Ответ отправлен.\n";
    }

    close(connection);
    close(server);
}





