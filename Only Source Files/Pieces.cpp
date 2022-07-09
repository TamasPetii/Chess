#include "Table.h"
#include "Pieces.h"

std::vector<int> Pieces::possibleMoves(Table* table) {
	std::vector<int> possible;
	std::vector<int> vec = this->legalMoves(table);
	int from = this->pos;
	int to;
	Pieces* target;
	for (unsigned int i = 0; i < vec.size(); i++) {
		to = vec[i];
		target = table->get_tableElement(to);
		table->get_table()[from] = nullptr;
		table->get_table()[to] = this;
		table->get_table()[to]->set_pos(to);
		if (!table->checkCheck()) possible.push_back(to);
		table->get_table()[from] = this;
		table->get_table()[from]->set_pos(from);
		table->get_table()[to] = target;
	}
	return possible;
}

std::vector<int> King::legalMoves(Table* table) {
	std::vector<int> vec;
	int x = pos % 8;
	int y = pos / 8;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((i != 0 || j != 0) && x + i >= 0 && x + i < 8 && y + j >= 0 && y + j < 8 && (!(table->get_table()[x + i + (y + j) * 8] != nullptr) || table->get_table()[x + i + (y + j) * 8]->get_color() != this->get_color())) vec.push_back(x + i + (y + j) * 8);
		}
	}
	return vec;
}

std::vector<int> Queen::legalMoves(Table* table) {
	std::vector<int> vec;
	int x = pos % 8;
	int y = pos / 8;
	bool a = true, b = true, c = true, d = true;
	for (int i = 1; i < 8; i++) {
		if (a && x - i >= 0 && y - i >= 0 && ((a = !(table->get_table()[x - i + (y - i) * 8] != nullptr)) || table->get_table()[x - i + (y - i) * 8]->get_color() != this->get_color()))  vec.push_back(x - i + (y - i) * 8);
		if (b && x + i < 8 && y - i >= 0 && ((b = !(table->get_table()[x + i + (y - i) * 8] != nullptr)) || table->get_table()[x + i + (y - i) * 8]->get_color() != this->get_color()))  vec.push_back(x + i + (y - i) * 8);
		if (c && x - i >= 0 && y + i < 8 && ((c = !(table->get_table()[x - i + (y + i) * 8] != nullptr)) || table->get_table()[x - i + (y + i) * 8]->get_color() != this->get_color()))  vec.push_back(x - i + (y + i) * 8);
		if (d && x + i < 8 && y + i < 8 && ((d = !(table->get_table()[x + i + (y + i) * 8] != nullptr)) || table->get_table()[x + i + (y + i) * 8]->get_color() != this->get_color()))  vec.push_back(x + i + (y + i) * 8);
	}
	a = true, b = true, c = true, d = true;
	for (int i = 1; i < 8; i++) {
		if (a && x - i >= 0 && ((a = !(table->get_table()[x - i + y * 8] != nullptr)) || table->get_table()[x - i + y * 8]->get_color() != this->get_color()))    vec.push_back(x - i + y * 8);
		if (b && x + i < 8 && ((b = !(table->get_table()[x + i + y * 8] != nullptr)) || table->get_table()[x + i + y * 8]->get_color() != this->get_color()))    vec.push_back(x + i + y * 8);
		if (c && y - i >= 0 && ((c = !(table->get_table()[x + (y - i) * 8] != nullptr)) || table->get_table()[x + (y - i) * 8]->get_color() != this->get_color()))  vec.push_back(x + (y - i) * 8);
		if (d && y + i < 8 && ((d = !(table->get_table()[x + (y + i) * 8] != nullptr)) || table->get_table()[x + (y + i) * 8]->get_color() != this->get_color()))  vec.push_back(x + (y + i) * 8);
	}
	return vec;
}

std::vector<int> Bishop::legalMoves(Table* table) {
	std::vector<int> vec;
	int x = pos % 8;
	int y = pos / 8;
	bool a = true, b = true, c = true, d = true;
	for (int i = 1; i < 8; i++) {
		if (a && x - i >= 0 && y - i >= 0 && ((a = !(table->get_table()[x - i + (y - i) * 8] != nullptr)) || table->get_table()[x - i + (y - i) * 8]->get_color() != this->get_color()))  vec.push_back(x - i + (y - i) * 8);
		if (b && x + i < 8 && y - i >= 0 && ((b = !(table->get_table()[x + i + (y - i) * 8] != nullptr)) || table->get_table()[x + i + (y - i) * 8]->get_color() != this->get_color()))  vec.push_back(x + i + (y - i) * 8);
		if (c && x - i >= 0 && y + i < 8 && ((c = !(table->get_table()[x - i + (y + i) * 8] != nullptr)) || table->get_table()[x - i + (y + i) * 8]->get_color() != this->get_color()))  vec.push_back(x - i + (y + i) * 8);
		if (d && x + i < 8 && y + i < 8 && ((d = !(table->get_table()[x + i + (y + i) * 8] != nullptr)) || table->get_table()[x + i + (y + i) * 8]->get_color() != this->get_color()))  vec.push_back(x + i + (y + i) * 8);
	}
	return vec;
}

std::vector<int> Rook::legalMoves(Table* table) {
	std::vector<int> vec;
	int x = pos % 8;
	int y = pos / 8;
	bool a = true, b = true, c = true, d = true;
	for (int i = 1; i < 8; i++) {
		if (a && x - i >= 0 && ((a = !(table->get_table()[x - i + y * 8] != nullptr)) || table->get_table()[x - i + y * 8]->get_color() != this->get_color()))  vec.push_back(x - i + y * 8);
		if (b && x + i < 8 && ((b = !(table->get_table()[x + i + y * 8] != nullptr)) || table->get_table()[x + i + y * 8]->get_color() != this->get_color()))  vec.push_back(x + i + y * 8);
		if (c && y - i >= 0 && ((c = !(table->get_table()[x + (y - i) * 8] != nullptr)) || table->get_table()[x + (y - i) * 8]->get_color() != this->get_color()))  vec.push_back(x + (y - i) * 8);
		if (d && y + i < 8 && ((d = !(table->get_table()[x + (y + i) * 8] != nullptr)) || table->get_table()[x + (y + i) * 8]->get_color() != this->get_color()))  vec.push_back(x + (y + i) * 8);
	}
	return vec;
}

std::vector<int> Knight::legalMoves(Table* table) {
	std::vector<int> vec;
	int x = pos % 8;
	int y = pos / 8;
	if (x - 1 >= 0 && y - 2 >= 0 && (!(table->get_table()[x - 1 + (y - 2) * 8] != nullptr) || table->get_table()[x - 1 + (y - 2) * 8]->get_color() != this->get_color())) vec.push_back(x - 1 + (y - 2) * 8);
	if (x + 1 < 8 && y - 2 >= 0 && (!(table->get_table()[x + 1 + (y - 2) * 8] != nullptr) || table->get_table()[x + 1 + (y - 2) * 8]->get_color() != this->get_color())) vec.push_back(x + 1 + (y - 2) * 8);
	if (x + 2 < 8 && y - 1 >= 0 && (!(table->get_table()[x + 2 + (y - 1) * 8] != nullptr) || table->get_table()[x + 2 + (y - 1) * 8]->get_color() != this->get_color())) vec.push_back(x + 2 + (y - 1) * 8);
	if (x + 2 < 8 && y + 1 < 8 && (!(table->get_table()[x + 2 + (y + 1) * 8] != nullptr) || table->get_table()[x + 2 + (y + 1) * 8]->get_color() != this->get_color())) vec.push_back(x + 2 + (y + 1) * 8);
	if (x + 1 < 8 && y + 2 < 8 && (!(table->get_table()[x + 1 + (y + 2) * 8] != nullptr) || table->get_table()[x + 1 + (y + 2) * 8]->get_color() != this->get_color())) vec.push_back(x + 1 + (y + 2) * 8);
	if (x - 1 >= 0 && y + 2 < 8 && (!(table->get_table()[x - 1 + (y + 2) * 8] != nullptr) || table->get_table()[x - 1 + (y + 2) * 8]->get_color() != this->get_color())) vec.push_back(x - 1 + (y + 2) * 8);
	if (x - 2 >= 0 && y + 1 < 8 && (!(table->get_table()[x - 2 + (y + 1) * 8] != nullptr) || table->get_table()[x - 2 + (y + 1) * 8]->get_color() != this->get_color())) vec.push_back(x - 2 + (y + 1) * 8);
	if (x - 2 >= 0 && y - 1 >= 0 && (!(table->get_table()[x - 2 + (y - 1) * 8] != nullptr) || table->get_table()[x - 2 + (y - 1) * 8]->get_color() != this->get_color())) vec.push_back(x - 2 + (y - 1) * 8);
	return vec;
}

std::vector<int> Pawn::legalMoves(Table* table) {
	std::vector<int> vec;
	int x = pos % 8;
	int y = pos / 8;
	if (this->get_color() == WHITE) {
		if (table->get_moveCounter() < 2) vec.push_back(x + (y - 2) * 8);
		if (y - 1 >= 0 && table->get_table()[x + (y - 1) * 8] == nullptr) vec.push_back(x + (y - 1) * 8);
		if (y - 1 >= 0 && x - 1 >= 0 && table->get_table()[x - 1 + (y - 1) * 8] != nullptr && table->get_table()[x - 1 + (y - 1) * 8]->get_color() != this->get_color()) vec.push_back(x - 1 + (y - 1) * 8);
		if (y - 1 >= 0 && x + 1 < 8 && table->get_table()[x + 1 + (y - 1) * 8] != nullptr && table->get_table()[x + 1 + (y - 1) * 8]->get_color() != this->get_color()) vec.push_back(x + 1 + (y - 1) * 8);
	}
	else {
		if (table->get_moveCounter() < 2) vec.push_back(x + (y + 2) * 8);
		if (y + 1 < 8 && table->get_table()[x + (y + 1) * 8] == nullptr) vec.push_back(x + (y + 1) * 8);
		if (y + 1 < 8 && x - 1 >= 0 && table->get_table()[x - 1 + (y + 1) * 8] != nullptr && table->get_table()[x - 1 + (y + 1) * 8]->get_color() != this->get_color()) vec.push_back(x - 1 + (y + 1) * 8);
		if (y + 1 < 8 && x + 1 < 8 && table->get_table()[x + 1 + (y + 1) * 8] != nullptr && table->get_table()[x + 1 + (y + 1) * 8]->get_color() != this->get_color()) vec.push_back(x + 1 + (y + 1) * 8);
	}
	return vec;
}