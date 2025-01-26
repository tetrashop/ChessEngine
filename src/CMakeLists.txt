# کتابخانه هسته موتور  
add_library(ChessEngineCore STATIC  
    Board.cpp  
    MoveGenerator.cpp  
    Evaluator.cpp  
    Search.cpp  
    ${PROJECT_SOURCE_DIR}/include/ChessEngine/Board.h  
    ${PROJECT_SOURCE_DIR}/include/ChessEngine/MoveGenerator.h  
)  

# اجرایی CLI  
add_executable(ChessEngineCLI main.cpp)  
target_link_libraries(ChessEngineCLI PRIVATE ChessEngineCore)  

# تنظیمات هدرها  
target_include_directories(ChessEngineCore PUBLIC  
    ${PROJECT_SOURCE_DIR}/include  
)  

# فعال‌سازی UCI  
if(ENABLE_UCI)  
    target_compile_definitions(ChessEngineCore PUBLIC -DENABLE_UCI)  
    target_sources(ChessEngineCore PRIVATE UCIHandler.cpp)  
endif()  

# یکپارچه‌سازی Syzygy  
if(ENABLE_SYZYGY)  
    add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/syzygy)  
    target_link_libraries(ChessEngineCore PRIVATE Syzygy)  
    target_compile_definitions(ChessEngineCore PUBLIC -DENABLE_SYZYGY)  
endif()  

# بهینه‌سازی برای حالت Release  
if(CMAKE_BUILD_TYPE STREQUAL "Release")  
    target_compile_options(ChessEngineCore PRIVATE /O2 /GL)  
    target_link_libraries(ChessEngineCore PRIVATE -LTCG)  
endif()  