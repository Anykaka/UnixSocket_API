//#include "src/tool/public.h"
//#include "src/tool/public_h.h"

#include "src/SocketAdvance/GetTime.h"

void thread_func() {
    SocketClient<int> client;
    while (true) {
        int request, response;

        std::cin >> request;

        client.sendMessage(request, response);

        std::cout << "send: " << request << " resp" << response << std::endl;

        request = response = 0;
    }
}

int main(int argc, char** argv) {
//    printf("%s:%d begain.\n", __func__, __LINE__);

    SocketServer<int> ser;
    ser.start();

//    printf("%s:%d end.\n", __func__, __LINE__);
}