cmake_minimum_required(VERSION 3.31.4)  # حداقل نسخه الزامی
project(ChessEngine)  # نام پروژه

# تعریف هدف اصلی (کتابخانه یا اجرایی)
add_executable(ChessEngine  # یا add_library
    src/main.cpp  # فایلهای منبع
    # سایر فایلها...
)

# اضافه کردن مسیر هدرها
target_include_directories(ChessEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)