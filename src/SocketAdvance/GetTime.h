//
// Created by ubuntu on 2023/4/8.
//
#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

template<typename T>
class SocketServer {
public:
    SocketServer() = default;
    ~SocketServer() = default;

    void thread_func() {
        int fd = 0;
        struct sockaddr_in client_addr{};
        socklen_t client_addr_size = sizeof(client_addr);

        while (true) {

            fd = accept(m_server_sock, (struct sockaddr*)&client_addr, &client_addr_size);

            if (fd) {
                bool ret = false;
                T request, response;
                if (receiveMessage(fd, request)) {
                    ret = ProcessRequests(request, response);
                }
                if (sendMessage(fd, response)) {
                    close(fd);
                    fd = 0;
                }
            }
            std::cout << "running" << std::endl;
            usleep(1000);
        }
    }

    bool start() {
        m_server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (m_server_sock == -1) {
            std::cerr << "Failed to create socket" << std::endl;
            return false;
        }

        // 绑定端口号和地址
        struct sockaddr_in serv_addr{};
        bzero(&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(port);
        if (bind(m_server_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
            std::cerr << "Failed to bind socket" << std::endl;
            close(m_server_sock);
            return false;
        }

        // 监听连接请求
        if (listen(m_server_sock, MAX_CONNECTIONS) == -1) {
            std::cerr << "Failed to listen for connections" << std::endl;
            close(m_server_sock);
            return false;
        }

        thread_func();

        return true;
    }



private:
    bool sendMessage(int fd, T& message) {
        // 发送响应
        if (send(fd, &message, sizeof(message), MSG_NOSIGNAL) == -1) {
            std::cerr << "Failed to send response" << std::endl;
            return false;
        }

        return true;
    }

    bool receiveMessage(int fd, T& message) {
        // 接收消息
        if (recv(fd, &message, sizeof(message), 0) == -1) {
            return false;
        }

        return true;
    }

    bool ProcessRequests(const T& request, T& response) {
        std::cout << "request " << request << std::endl;

        response = request;

        std::cout << "response" << response << std::endl;

        return false;
    }

private:
    const int port = 10086;
    const int MAX_CONNECTIONS = 1;

    int m_server_sock;
};

template<typename T>
class SocketClient {
public:
    SocketClient() = default;
    ~SocketClient() = default;

    int Connect() {
        // 创建套接字
        int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == -1) {
            std::cerr << "Failed to create socket" << std::endl;
            return sock;
        }

        // 定义服务器地址结构体
        struct sockaddr_in serv_addr{};
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(m_address.c_str());
        serv_addr.sin_port = htons(m_port);

        // 连接到服务器
        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
            std::cerr << "Failed to connect to server" << std::endl;
            return -1;
        }

        return sock;
    }

    bool sendMessage(const T& request, T& response) {
        std::cout << "sendMessage" << std::endl;
        int sock = Connect();
        // 发送消息
        if (send(sock, &request, sizeof(request), MSG_NOSIGNAL) == -1) {
            std::cerr << "Failed to send request" << std::endl;
            close(sock);
            return false;
        }

        // 接收响应
        if (recv(sock, &response, sizeof(response), 0) == -1) {
            std::cerr << "Failed to receive response" << std::endl;
            close(sock);
            return false;
        }
        // 关闭套接字
        close(sock);

        return true;
    }

private:
    const std::string m_address = "127.0.0.1";
    const int m_port = 10086;
};

 template<>
 class SocketServer<std::string> {



 };