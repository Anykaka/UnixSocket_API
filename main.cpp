//#include "src/tool/public.h"
//#include "src/tool/public_h.h"

#include <thread>
#include "src/SocketAdvance/GetTime.h"

void thread_func() {
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

int main(int argc, char** argv) {
//    printf("%s:%d begain.\n", __func__, __LINE__);

    std::thread fun(thread_func);

    SocketServer<int> ser;
    ser.start();

//    printf("%s:%d end.\n", __func__, __LINE__);
}