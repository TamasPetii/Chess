#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

class Table;

class Pieces
{
protected:
	int pos;
	bool color;
	SDL_Rect from;
public:
	Pieces(int pos, bool color) : pos(pos), color(color) {
		this->from = { 0,0,0,0 };
	}
	virtual ~Pieces() {}
	virtual std::vector<int> legalMoves(Table* table) = 0;
	std::vector<int> possibleMoves(Table* table);
	//Setter
	void set_pos(int pos) { this->pos = pos; }
	void set_color(bool color) { this->color = color; }
	void set_from(SDL_Rect from) { this->from = from; }
	//Getter
	int get_pos() { return pos; }
	bool get_color() { return color; }
	SDL_Rect* get_from() { return &from; }
	virtual std::string get_name() = 0;
};

class King : public Pieces {
public:
	King(int pos, bool color) : Pieces(pos, color) {
		color ? from = { 0,0,100,100 } : from = { 0,100,100,100 };
	}
	~King() {}
	std::string get_name() override { return "KING"; }
	std::vector<int> legalMoves(Table* table) override;
};

class Queen : public Pieces {
public:
	Queen(int pos, bool color) : Pieces(pos, color) {
		color ? from = { 100,0,100,100 } : from = { 100,100,100,100 };
	}
	~Queen() {}
	std::string get_name() override { return "QUEEN"; }
	std::vector<int> legalMoves(Table* table) override;
};

class Rook : public Pieces {
public:
	Rook(int pos, bool color) : Pieces(pos, color) {
		color ? from = { 400, 0, 100, 100 } : from = { 400, 100, 100, 100 };
	}
	~Rook() {}
	std::string get_name() override { return "ROOK"; }
	std::vector<int> legalMoves(Table* table) override;
};

class Bishop : public Pieces {
public:
	Bishop(int pos, bool color) : Pieces(pos, color) {
		color ? from = { 200,0,100,100 } : from = { 200,100,100,100 };
	}
	~Bishop() {}
	std::string get_name() override { return "BISHOP"; }
	std::vector<int> legalMoves(Table* table) override;
};

class Knight : public Pieces {
public:
	Knight(int pos, bool color) : Pieces(pos, color) {
		color ? from = { 300, 0, 100, 100 } : from = { 300, 100, 100, 100 };
	}
	~Knight() {}
	std::string get_name() override { return "KNIGHT"; }
	std::vector<int> legalMoves(Table* table) override;
};

class Pawn : public Pieces {
public:
	Pawn(int pos, bool color) : Pieces(pos, color) {
		color ? from = { 500,0,100,100 } : from = { 500,100,100,100 };
	}
	~Pawn() {}
	std::string get_name() override { return "PAWN"; }
	std::vector<int> legalMoves(Table* table) override;
};





