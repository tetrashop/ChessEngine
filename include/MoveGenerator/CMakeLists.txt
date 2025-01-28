# اگر MoveGenerator یک ماژول مستقل است
add_library(MoveGenerator STATIC
    MoveGenerator.h
    MoveGenerator.cpp
)

target_include_directories(MoveGenerator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)