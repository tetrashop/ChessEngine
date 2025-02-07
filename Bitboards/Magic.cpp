// оя Magic.cpp
Bitboard getBishopAttacks(Square sq, Bitboard occupancy) {
	occupancy &= bishopMasks[sq];
	occupancy *= bishopMagics[sq];
	occupancy >>= 64 - bishopBits[sq];
	return bishopAttacks[sq][occupancy];
}