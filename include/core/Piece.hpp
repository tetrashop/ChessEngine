#pragma once

enum class PieceType {
	None = 0,
	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King
};

enum class Color {
	White,
	Black,
	None
};

struct Piece {
	PieceType type = PieceType::None;
	Color color = Color::None;

	// تبدیل نوع مهره به کاراکتر نمادین (اختیاری)
	char symbol() const {
		const char symbols[] = { ' ', 'P', 'N', 'B', 'R', 'Q', 'K' };
		char c = symbols[static_cast<int>(type)];
		return (color == Color::White) ? c : tolower(c);
	}
};