cmake_minimum_required(VERSION 3.15)
project(ChessEngine LANGUAGES CXX)

# تنظیمات استاندارد
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# افزودن پوشه include
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")

# افزودن سورس‌کدها
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# فعال‌سازی تست‌ها (اگر پوشه tests وجود دارد)
if(EXISTS "${PROJECT_SOURCE_DIR}/tests")
    add_subdirectory(tests)
endif()