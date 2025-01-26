cmake_minimum_required(VERSION 3.10)  
project(ChessEngineCLI  
    VERSION 1.0.0  
    LANGUAGES CXX  
    DESCRIPTION "A UCI-Compatible Chess Engine"  
)  

# تنظیمات کلی  
set(CMAKE_CXX_STANDARD 17)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
set(CMAKE_CXX_EXTENSIONS OFF)  

# فعال‌سازی هشدارهای کامپایلر  
if(MSVC)  
    add_compile_options(/W4 /WX)  
else()  
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)  
endif()  

# گزینه‌های ساخت  
option(ENABLE_UCI "Enable UCI Protocol Support" ON)  
option(ENABLE_SYZYGY "Integrate Syzygy Tablebases" OFF)  
option(BUILD_TESTS "Build Unit Tests" ON)  

# کتابخانه اصلی  
add_subdirectory(src)  

# تست‌ها  
if(BUILD_TESTS)  
    add_subdirectory(tests)  
endif()  

# نصب اجرایی  
install(TARGETS ChessEngineCLI  
    RUNTIME DESTINATION bin  
    LIBRARY DESTINATION lib  
    ARCHIVE DESTINATION lib  
)  