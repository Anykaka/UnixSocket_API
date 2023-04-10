//
// Created by ubuntu on 2023/4/8.
//

#include "src/SocketAdvance/GetTime.h"

int main() {
    SocketClient<int> client;
    while (true) {
        int request, response;

        std::cout << "please input a int number: ";
        std::cin >> request;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "input error" << std::endl;
            continue;
        }

        client.sendMessage(request, response);

        std::cout << "send: " << request << " resp" << response << std::endl;
    }
}
