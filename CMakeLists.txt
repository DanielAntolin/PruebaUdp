cmake_minimum_required(VERSION 3.5)

project(pruebasServidor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pruebasServidor main.cpp
    clienteucp.h clienteucp.cpp

)

include(GNUInstallDirs)
install(TARGETS pruebasServidor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
