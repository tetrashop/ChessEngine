cmake_minimum_required(VERSION 3.15)
project(ChessEngine LANGUAGES CXX)

# تنظیمات استاندارد
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# مسیر کتابخانه‌های خارجی
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# افزودن زیرپروژه‌ها
add_subdirectory(src)
add_subdirectory(tests)
cmake -DCMAKE_TOOLCHAIN_FILE="D:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake" ..