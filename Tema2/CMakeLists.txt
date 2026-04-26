cmake_minimum_required(VERSION 4.1)
project(Tema2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tema2 main.cpp
        cards.h
        Card.cpp
        entity.h
        cardCollection.h
        cardCollection.cpp
        entity.cpp)
