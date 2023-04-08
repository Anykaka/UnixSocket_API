//
// Created by ubuntu on 2023/4/8.
//

#include "src/SocketAdvance/GetTime.h"

int main() {
    SocketClient<int> client;
    while (true) {
        int request, response;

        std::cin >> request;

        client.sendMessage(request, response);

        std::cout << "send: " << request << " resp" << response << std::endl;

        request = response = 0;
    }
}
