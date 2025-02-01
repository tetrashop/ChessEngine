# کتابخانه اصلی (Core)
add_library(ChessEngineCore STATIC
    Board/Board.cpp
    Bitboards/Bitboard.cpp
    Evaluation/Evaluator.cpp
    Search/Search.cpp
    Utils/Move.cpp
    Utils/Zobrist.cpp
    UCI/UCIHandler.cpp
)

# مسیرهای هدر
target_include_directories(ChessEngineCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Board
    ${CMAKE_CURRENT_SOURCE_DIR}/Bitboards
    ${CMAKE_CURRENT_SOURCE_DIR}/Evaluation
    ${CMAKE_CURRENT_SOURCE_DIR}/Search
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/UCI
)

# لینک به Boost
find_package(Boost REQUIRED)
target_link_libraries(ChessEngineCore PRIVATE Boost::boost)