#ifndef HASH_BOARD_CPP_
#define HASH_BOARD_CPP_

#include "hash_board.h"
#include "board.cpp"
#include "positions.h"

#include <sstream>

namespace Hex {

#define GUARD 3

HashBoard::HashBoard() {

	_total_size = kBoardSizeAligned * kBoardSizeAligned;

	uint _init_hash[_total_size];

	FillArrays();

	memset(_hash_board, 0,  _total_size * sizeof(uint));
	memset(_init_hash, 0, _total_size * sizeof(uint));

	for (uint i = 0; i < kBoardSizeAligned; ++i)
		_hash_board[i] = _hash_board[_total_size - 1 - i] = 
			_init_hash[i] = _init_hash[_total_size - 1 - i] = GUARD;

	for (uint i = 1; i <= kBoardSize; ++i)
		_hash_board[i * kBoardSizeAligned] =
			_hash_board[(i + 1) * kBoardSizeAligned - 1] = 
			_init_hash[i * kBoardSizeAligned] = 
			_init_hash[(i + 1) * kBoardSizeAligned - 1] = GUARD;

	for (uint i = 1; i <= kBoardSize; ++i) {
		InitHash(_init_hash, kBoardSizeAligned + i);
		InitHash(_init_hash, i * kBoardSizeAligned + 1);
		InitHash(_init_hash, (i + 1) * kBoardSizeAligned - 2);
		InitHash(_init_hash, _total_size - kBoardSizeAligned - 1 - i);
	}

	memcpy(_hash_board, _init_hash, _total_size * sizeof(uint));
}

void HashBoard::InitHash(uint *init, uint position) {
	init[position] =
		_hash_board[position - kBoardSizeAligned + 1] * 1 +
		_hash_board[position + 1] * 4 +
		_hash_board[position + kBoardSizeAligned] * 16 +
		_hash_board[position + kBoardSizeAligned - 1] * 64 +
		_hash_board[position - 1] * 256 +
		_hash_board[position - kBoardSizeAligned] * 1024;
}

std::string HashBoard::ToAsciiArt() {
	std::stringstream result;

	for (uint i = 0; i < kBoardSizeAligned; ++i) {
		for (uint j = 0; j < kBoardSizeAligned; ++j)
			result << _hash_board[i * kBoardSizeAligned + j] << " ";
		result << "\n";
	}

	result <<std::endl;

	return result.str();
}

inline void HashBoard::Change(HashColor color, uint position) {
// position is in 0..(kBoardSize ^ 2)
	return Change(color, transf[position], true);
}

inline void HashBoard::Change(HashColor color, uint position, bool) {
// normal_position in 0..(kBoardSizeAligned ^ 2)
	_hash_board[position - kBoardSizeAligned + 1] += color * 64;
	_hash_board[position + 1] += color * 256;
	_hash_board[position + kBoardSizeAligned] += color * 1024;
	_hash_board[position + kBoardSizeAligned - 1] += color * 1;
	_hash_board[position - 1] += color * 4;
	_hash_board[position - kBoardSizeAligned] += color * 16;

	return;
}

inline void HashBoard::Change(HashColor color, uint row, uint column) {
//row, column in 0..(kBoardSize -1)
	return Change(color, transf[row * kBoardSizeAligned + column], true);
}

inline void HashBoard::Change(HashColor color, const std::string &position) {
	return Change(color, transf[ParsePosition(position)], true);
}


inline uint HashBoard::Hash(HashColor color, uint position) {
// position is in 0..(kBoardSize ^ 2)
	return (_hash_board[transf[position]] << 2) | color;
}

inline uint HashBoard::Hash(HashColor color, uint normal_position, bool) {
// normal_position in 0..(kBoardSizeAligned ^ 2)
	return (_hash_board[normal_position] << 2) | color;
}

inline uint HashBoard::Hash(HashColor color, uint row, uint column) {
//row, column in 0..(kBoardSize -1)
	return (_hash_board[transf[row * kBoardSize + column]] << 2) | color;
}

inline uint HashBoard::Hash(HashColor color, const std::string &position) {
	return (_hash_board[transf[ParsePosition(position)]] << 2) | color;
}

} // namespace Hex

#endif
