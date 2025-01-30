cmake_minimum_required(VERSION 3.15)
project(ChessEngine LANGUAGES CXX)

# تنظیمات استاندارد
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# افزودن زیرپروژه‌ها
add_subdirectory(core)
add_subdirectory(tests)
add_subdirectory(gui)