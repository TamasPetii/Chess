#pragma once
#include <vector>

#define WHITE true
#define BLACK false

class Pieces;

struct Step {
	int from;
	int to;
	Pieces* from_piece;
	Pieces* to_piece;
};


class Table
{
private:
	//Singleton
	static Table* _instance;
	Table(bool option);
	~Table();
	//Data members
	std::vector<Pieces*> table;
	std::vector<Pieces*> currentTable;
	std::vector<Pieces*> hitbyWhite;
	std::vector<Pieces*> hitbyBlack;
	std::vector<Pieces*> allPieces;
	std::vector<Step> steps;
	bool option = true;
	bool player = true;
	int moveCounter = 0;
	int stepsPos = -1;
public:
	//Singleton
	static Table* instance(bool option);
	static void destroy();
	//Methodes
	int  checkKingPos();
	void set_default();
	void printDatas();
	bool checkMove(int from, int to);
	bool checkCheckMove(int from, int to);
	bool checkCheck();
	bool isPresent();
	bool canForward();
	bool canBack();
	bool checkMate();
	bool onlyTwoPieces();
	//Setter
	void addto_moveCounter() { this->moveCounter++; }
	void set_player(bool player) { this->player = player; }
	void addto_hitbyWhite(Pieces* piece) { this->hitbyWhite.push_back(piece); }
	void addto_hitbyBlack(Pieces* piece) { this->hitbyBlack.push_back(piece); }
	void addto_steps(Step step) { this->steps.push_back(step); }
	void addto_stepsPos(int i) { this->stepsPos += i; }
	void addto_allPieces(Pieces* piece) { this->allPieces.push_back(piece); }
	void set_stepsPos(int i) { this->stepsPos = i; }
	void set_currentTable(std::vector<Pieces*> table) { this->currentTable = table; }
	void set_table() { this->table = this->currentTable; }
	//Getter
	int get_moveCounter() { return moveCounter; }
	int get_stepsPos() { return stepsPos; }
	bool get_player() { return player; }
	bool get_option() { return option; }
	Pieces* get_tableElement(int i) { return table[i]; }
	std::vector<Pieces*>& get_table() { return table; }
	std::vector<Step> get_steps() { return steps; }
	std::vector<Pieces*> get_hitbyWhite() { return hitbyWhite; }
	std::vector<Pieces*> get_hitbyBlack() { return hitbyBlack; }
	std::vector<Pieces*> get_currentTable() { return currentTable; }
};


