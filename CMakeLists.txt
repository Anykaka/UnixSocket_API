# 指定cmake最小版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
# 指定工程
PROJECT(run C)
# 指定安装目录
SET (CMAKE_INSTALL_PREFIX
    ${PROJECT_SOURCE_DIR}/out
)
# 获取路径下全部文件
AUX_SOURCE_DIRECTORY(. ALL_LIST)
# 添加路径
ADD_SUBDIRECTORY(src/TCP_IP)
ADD_SUBDIRECTORY(src/SocketBase)
ADD_SUBDIRECTORY(src/SocketAdvance)
# 编译
ADD_EXECUTABLE( main
    ${ALL_LIST}
)
# 链接库
TARGET_LINK_LIBRARIES(main
    tcpip
    socketadv
    socketbase
)
# 指定安装路径
INSTALL(TARGETS main
    LIBRARY DESTINATION lib  # 动态库安装路径
    ARCHIVE DESTINATION lib  # 静态库安装路径
    RUNTIME DESTINATION bin  # 可执行文件安装路径
    PUBLIC_HEADER DESTINATION include  # 头文件安装路径
)