#pragma MAIN_H
#include "src/public/public.h"
#include "src/public/public_h.h"

int main(int argc, char **argv) {
    printf("%s:%d begain.\n", __func__, __LINE__);

    GetClientTime(argc, argv);
    SocketBase();
    SocketAdvance();

    printf("%s:%d end.\n", __func__, __LINE__);
}