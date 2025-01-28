# سرآیندهای عمومی را به پروژه اضافه کنید
target_include_directories(ChessEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# اگر هدرها به صورت ماژولار سازماندهی شده‌اند:
add_subdirectory(MoveGenerator)
add_subdirectory(UCI)
add_subdirectory(OpeningBook)