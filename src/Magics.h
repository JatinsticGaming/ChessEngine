#pragma once
typedef unsigned long long U64;

struct SMagic {
	U64* aptr;  // Pointer to attack_table for each square
	U64 mask;  // For masking relevant squares of both lines (no outer squares)
	U64 magic; // Magic 64-bit factor
	int shift; // Shift right
};

SMagic mBishopTbl[64];
SMagic mRookTbl[64];
