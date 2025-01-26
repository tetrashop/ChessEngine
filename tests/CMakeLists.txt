# فعال‌سازی Google Test  
find_package(GTest REQUIRED)  
include(GoogleTest)  

# تست‌ها  
add_executable(ChessEngineTests  
    BoardTests.cpp  
    MoveGeneratorTests.cpp  
)  

target_link_libraries(ChessEngineTests PRIVATE  
    ChessEngineCore  
    GTest::GTest  
    GTest::Main  
)  

# افزودن تست به CTest  
gtest_discover_tests(ChessEngineTests)  

# کپی فایل‌های تست  
file(COPY ${PROJECT_SOURCE_DIR}/tests/test_positions DESTINATION ${CMAKE_BINARY_DIR})  