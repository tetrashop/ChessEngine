cmake_minimum_required(VERSION 3.31.4)  # حداقل نسخه در تستها

# تعریف تستها
add_executable(test_board test_board.cpp)
target_link_libraries(test_board
    ChessEngine  # لینک به هدف اصلی
    gtest_main   # لینک به کتابخانه تست
)

# فعالسازی تستها
enable_testing()
add_test(NAME test_board COMMAND test_board)