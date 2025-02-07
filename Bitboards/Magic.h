// در Magic.h
struct Magic {
	uint64_t magic;
	uint64_t mask;
	uint64_t* attacks;
};

extern Magic bishopMagics[64];
extern Magic rookMagics[64];

void initMagics() {
	// مقادیر از پیش محاسبه‌شده برای فیل
	bishopMagics[0] = { 0x123456789ABCDEF0, 0x007E7E7E7E7E00, /*...*/ };
	// ...
}
Bitboard getBishopAttacks(Square sq, Bitboard occupancy) {
	occupancy &= bishopMagics[sq].mask;
	occupancy *= bishopMagics[sq].magic;
	occupancy >>= 64 - 9; // 9 بیت برای فیل
	return bishopMagics[sq].attacks[occupancy];
}