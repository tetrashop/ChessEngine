cmake_minimum_required(VERSION 3.31.4)
project(ChessEngine LANGUAGES CXX)

# تنظیمات کامپایلر
set(CMAKE_CXX_STANDARD 17)

# افزودن زیرپروژهی تست
add_subdirectory(tests)

# ساخت اجرایی اصلی
add_executable(chess_engine
    src/main.cpp
    src/Board/Board.cpp
)

add_executable(chess_engine  
    src/Board/Board.cpp  
    src/Board/Board.h  
    # ...  
)  