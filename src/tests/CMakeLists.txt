enable_testing()

# افزودن Google Test
find_package(GTest REQUIRED)
include(GoogleTest)

# تست‌های بیتبرد
add_executable(BitboardTests BitboardTests.cpp)
target_link_libraries(BitboardTests PRIVATE ChessEngineCore GTest::GTest GTest::Main)

# تست‌های صفحه شطرنج
add_executable(BoardTests BoardTests.cpp)
target_link_libraries(BoardTests PRIVATE ChessEngineCore GTest::GTest GTest::Main)

# تست‌های جستجو
add_executable(SearchTests SearchTests.cpp)
target_link_libraries(SearchTests PRIVATE ChessEngineCore GTest::GTest GTest::Main)

# ثبت تمام تست‌ها
gtest_discover_tests(BitboardTests)
gtest_discover_tests(BoardTests)
gtest_discover_tests(SearchTests)