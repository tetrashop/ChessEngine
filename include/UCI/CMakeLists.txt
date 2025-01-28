# مدیریت ماژول UCI
add_library(UCIHandler STATIC
    UCIHandler.h
    UCIHandler.cpp
)

target_include_directories(UCIHandler PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)