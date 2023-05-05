cmake_minimum_required(VERSION 3.25)
project(untitled3 C)

set(CMAKE_C_STANDARD 99)

add_executable(jackpotfinal main.c )
target_link_libraries(jackpotfinal -lmingw32 allegro-4.4.2-monolith-md-debug.dll)