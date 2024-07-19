cmake_minimum_required(VERSION 3.30)
project(LMS)

set(CMAKE_CXX_STANDARD 17)

add_executable(LMS main.cpp
        src/Display.cpp
        src/Display.h
        main.cpp
        src/Book.h
        src/Book.cpp
        src/cursor.h
        src/User.cpp
        src/Tag.cpp
        src/User.h)
