#include "Table.h"
#include "Pieces.h"

void Table::set_default() {
	table[0] = new Rook(0, option ? BLACK : WHITE);
	table[1] = new Knight(1, option ? BLACK : WHITE);
	table[2] = new Bishop(2, option ? BLACK : WHITE);
	table[3] = new Queen(3, option ? BLACK : WHITE);
	table[4] = new King(4, option ? BLACK : WHITE);
	table[5] = new Bishop(5, option ? BLACK : WHITE);
	table[6] = new Knight(6, option ? BLACK : WHITE);
	table[7] = new Rook(7, option ? BLACK : WHITE);

	for (int i = 8; i < 16; i++) {
		table[i] = new Pawn(i, option ? BLACK : WHITE);
	}

	for (int i = 48; i < 56; i++) {
		table[i] = new Pawn(i, !option ? BLACK : WHITE);
	}

	table[56] = new Rook(56, !option ? BLACK : WHITE);
	table[57] = new Knight(57, !option ? BLACK : WHITE);
	table[58] = new Bishop(58, !option ? BLACK : WHITE);
	table[59] = new Queen(59, !option ? BLACK : WHITE);
	table[60] = new King(60, !option ? BLACK : WHITE);
	table[61] = new Bishop(61, !option ? BLACK : WHITE);
	table[62] = new Knight(62, !option ? BLACK : WHITE);
	table[63] = new Rook(63, !option ? BLACK : WHITE);

}

Table::Table(bool option) {
	this->option = option;
	table.resize(64);
	currentTable.resize(64);
	set_default();
	for (int i = 0; i < (int)table.size(); i++) {
		if (table[i] != nullptr) {
			allPieces.push_back(table[i]);
		}
	}
}

Table::~Table() {
	for (int i = 0; i < (int)allPieces.size(); i++) {
		delete allPieces[i];
	}
	
	allPieces.clear();
	table.clear();
	hitbyBlack.clear();
	hitbyWhite.clear();
	currentTable.clear();
}

Table* Table::_instance = nullptr;

Table* Table::instance(bool option) {
	if (_instance == nullptr) {
		_instance = new Table(option);
	}
	return _instance;
}

void Table::destroy() {
	if (_instance != nullptr) {
		delete _instance;
		_instance = nullptr;
	}
}

bool Table::checkMove(int from, int to) {
	if (table[from]->get_color() != player) return false;
	std::vector<int> moves = table[from]->possibleMoves(this);
	bool l = false;
	for (int i = 0; i < (int)moves.size() && !l; i++) {
		l = l || (moves[i] == to);
	}
	return l;
}

bool Table::checkCheckMove(int from, int to) {
	std::vector<int> moves = table[from]->legalMoves(this);
	bool l = false;
	for (int i = 0; i < (int)moves.size() && !l; i++) {
		l = l || (moves[i] == to);
	}
	return l;
}

int Table::checkKingPos() {
	for (int i = 0; i < (int)table.size(); i++) {
		if (table[i] != nullptr && table[i]->get_color() == player && table[i]->get_name() == "KING") return table[i]->get_pos();
	}
	return -1;
}

bool Table::checkCheck() {
	int pos = checkKingPos();
	bool l = false;
	for (int i = 0; i < (int)table.size() && !l; i++) {
		l = l || (table[i] != nullptr && table[i]->get_color() != player && checkCheckMove(i, pos));
	}
	return l;
}

bool Table::checkMate() {
	bool l = true;
	std::vector<int> vec;
	for (int i = 0; i < (int)currentTable.size() && l; i++) {
		l = l && (!(table[i] != nullptr) || (!(table[i]->get_color() == player) || table[i]->possibleMoves(this).size() == 0));
	}
	return l;
}

bool Table::isPresent() {
	return (int)steps.size() - 1 == stepsPos;
}
bool Table::canForward() {
	return (int)steps.size() != 0 && stepsPos < (int)steps.size() - 1;
}
bool Table::canBack() {
	return (int)steps.size() != 0 && stepsPos >= 0;
}

bool Table::onlyTwoPieces() {
	int c = 0;
	for (int i = 0; i < (int)currentTable.size(); i++) {
		if (currentTable[i] != nullptr) {
			c++;
		}
	}
	return c == 2;
}

void Table::printDatas() {
	std::cout << "----------------------\033[34mSTEP-" << moveCounter << "\033[0m----------------------" << std::endl;
	std::cout << "Current Table: ";
	for (int i = 0; i < (int)currentTable.size(); i++) {
		if (i % 8 == 0) std::cout << std::endl << "-----------------" << std::endl << "|";
		if (currentTable[i] == nullptr) std::cout << " |";
		else if (currentTable[i]->get_color() == WHITE) std::cout << "\033[33mo\033[0m|";
		else if (currentTable[i]->get_color() == BLACK) std::cout << "\033[31mx\033[0m|";
	}
	std::cout << std::endl << "-----------------" << std::endl;
	std::cout << "Coordinates: ";
	std::cout << "\033[32m" << (std::to_string(steps[moveCounter - 1].from) + " \033[0m" + (steps[moveCounter - 1].from_piece == nullptr ? "NULL" : steps[moveCounter - 1].from_piece->get_name()) + " \033[32m" + std::to_string(steps[moveCounter - 1].to) + " \033[0m" + (steps[moveCounter - 1].to_piece == nullptr ? "NULL" : steps[moveCounter - 1].to_piece->get_name())) + "\n\n";
}