#include "socket.h"

int main(){
    int client;
    const int buffer_size = 35;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client <= 0){
        std:: cerr << "Ошибка при создании сокета\n";
    }

    std::cout << "Сокет успешно создан\n";

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Некорректный ip адрес.\n";
        return -1;
    }

    // Подключ-ся к серв-у
    if (connect(client, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Ошибка подключения.\n";
        return -1;
    }

    std::cout << "Подключение к серверу прошло успешно.\n";

    char buffer[buffer_size] = {0};
    
    std::cout << "Введите сообщение: ";
    std::cin.getline(buffer, buffer_size);

    send(client, buffer, strlen(buffer), 0);

    char response[buffer_size] = {0};
    int bytesReceived = recv(client, response, sizeof(response), 0);
    if (bytesReceived > 0) {
        std::cout << "Ответ от сервера: " << response << std::endl;
    }

    close(client);
}

