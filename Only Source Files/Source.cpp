#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include "Table.h"
#include "Pieces.h"

#define WIDTH 1000
#define HEIGHT 800
SDL_Rect copy_table = { 0,0,800,800 };
SDL_Rect GREEN  = { 0,200,100,100 };
SDL_Rect BEIGI  = { 100,200,100,100 };
SDL_Rect PURPLE = { 0,300,100,100 };
SDL_Rect GREY   = { 100,300,100,100 };
SDL_Rect WOOD_1 = { 0,100,100,100};
SDL_Rect WOOD_2 = { 100,100,100,100 };

SDL_Rect table_color = GREEN;
SDL_Rect table_color2 = BEIGI;
int color_option = 0;
bool draw_option_black = true;
bool draw_option_white = true;
bool draw = false;
bool resign_option_black = true;
bool resign_option_white = true;
bool show_play = true;
bool started = false;
bool ended = false;
bool checkmate = false;
bool saved = false;
bool blackPawnChange = false;
bool whitePawnChange = false;

void draw_table(SDL_Renderer*& render, SDL_Texture*& pieces, Table*& table, SDL_Texture*& map, SDL_Texture*& icons, SDL_Texture*& mate, SDL_Texture*& frames);
void draw_sidebar(SDL_Renderer*& render, SDL_Texture*& sidebar, SDL_Texture*& icons, SDL_Texture*& pieces, Table*& table);
void deletePieceMotion(SDL_Renderer*& render, SDL_Texture*& map, SDL_Texture*& icons, int i);
void draw_possibleMoves(SDL_Renderer*& render, SDL_Texture*& map, SDL_Texture*& blueframe, Table*& table, std::vector<int> vec);
void draw_Check(SDL_Renderer*& render, SDL_Texture*& blueframe, int pos);
void Initialize(SDL_Window*& window, SDL_Renderer*& render, SDL_Texture*& map, SDL_Texture*& pieces, SDL_Texture*& frames, SDL_Texture*& sidebar, SDL_Texture*& icons, SDL_Texture* &mate);
void writeStepsToFile(Table*& table);
void changeTablePawn(Table*& table, Pieces* changeTo);

int main(int argc, char** argv) {
	SDL_SetMainReady();
	SDL_Window* window = nullptr;
	SDL_Renderer* render = nullptr;
	SDL_Texture* map = nullptr;
	SDL_Texture* pieces = nullptr;
	SDL_Texture* frames = nullptr;
	SDL_Texture* sidebar = nullptr;
	SDL_Texture* icons = nullptr;
	SDL_Texture* mate = nullptr;
	Table* table = nullptr;
	Initialize(window, render, map, pieces, frames, sidebar, icons, mate);
	table = Table::instance(true);
	table->set_currentTable(table->get_table());
	draw_table(render, pieces, table, map, icons, mate, frames);
	draw_sidebar(render, sidebar, icons, pieces, table);

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				Table::destroy();
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.x < 800 && table->isPresent() && started && !show_play) {
					int down_x = event.button.x / 100;
					int down_y = event.button.y / 100;
					if (table->get_tableElement(down_x + down_y * 8) != nullptr) {
						if (table->get_tableElement(down_x + down_y * 8)->get_color() == table->get_player() && !(blackPawnChange || whitePawnChange)) draw_possibleMoves(render, map, frames, table, table->get_tableElement(down_x + down_y * 8)->possibleMoves(table));
						SDL_Rect to;
						bool end_move = false;
						bool deleteRect = true;
						while (!end_move && (SDL_PollEvent(&event) || event.type != SDL_MOUSEBUTTONUP)) {
							switch (event.type)
							{
							case SDL_QUIT:
								quit = true;
								break;
							case SDL_MOUSEMOTION:
								to = { event.motion.x - 40,event.motion.y - 40,80,80 };
								if (deleteRect) { deletePieceMotion(render, map, icons, event.motion.x / 100 + event.motion.y / 100 * 8); deleteRect = false; }
								SDL_RenderCopy(render, map, &copy_table, &copy_table);
								SDL_RenderCopy(render, pieces, table->get_tableElement(down_x + down_y * 8)->get_from(), &to);
								if (event.motion.x >= 700) draw_sidebar(render, sidebar, icons, pieces, table);
								SDL_RenderPresent(render);
								break;
							case SDL_MOUSEBUTTONUP:
								int fromRect = down_x + down_y * 8;
								int targetRect = event.button.x / 100 + event.button.y / 100 * 8;
								if (table->checkMove(fromRect, targetRect) && !(blackPawnChange || whitePawnChange) && (!(table->get_tableElement(targetRect) != nullptr) || table->get_tableElement(targetRect)->get_name() != "KING")) {
									if (table->get_tableElement(targetRect) != nullptr && table->get_tableElement(targetRect)->get_color() == WHITE) table->addto_hitbyBlack(table->get_tableElement(targetRect));
									if (table->get_tableElement(targetRect) != nullptr && table->get_tableElement(targetRect)->get_color() == BLACK) table->addto_hitbyWhite(table->get_tableElement(targetRect));
									table->addto_steps({ fromRect, targetRect, table->get_tableElement(fromRect), table->get_tableElement(targetRect) });
									table->get_table()[targetRect] = table->get_table()[fromRect];
									table->get_table()[targetRect]->set_pos(targetRect);
									table->get_table()[down_x + down_y * 8] = nullptr;
									table->set_currentTable(table->get_table());
									if (table->get_currentTable()[targetRect]->get_name() == "PAWN" && (targetRect >= 0 && targetRect < 8)) whitePawnChange = true;
									if (table->get_currentTable()[targetRect]->get_name() == "PAWN" && (targetRect >= 56 && targetRect < 64)) blackPawnChange = true;
									table->addto_moveCounter();
									table->addto_stepsPos(1);
									table->set_player(table->get_moveCounter() % 2 == 0);
									if (table->checkMate()) {
										checkmate = true;
										ended = true;	
										show_play = true;
									}
									table->printDatas();
								}
								draw_table(render, pieces, table, map, icons, mate, frames);
								draw_sidebar(render, sidebar, icons, pieces, table);
								end_move = true;
								break;
							}
						}
					}
				}
				else if (event.button.x >= 810 && event.button.x < 990 && event.button.y >= 355 && event.button.y < 445) {
					if (!started) {
						Table::destroy();
						table = Table::instance(true);
						table->set_currentTable(table->get_table());
						started = true;
						ended = false;
						checkmate = false;
						show_play = false;
						draw = false;
						saved = false;
						draw_table(render, pieces, table, map, icons, mate, frames);
						draw_sidebar(render, sidebar, icons, pieces, table);
					}
				}
				//---------------Above new game icon---------------//
				//up resign
				else if (started && resign_option_black != 0 && event.button.x >= 810 && event.button.x < 840 && event.button.y >= 310 && event.button.y < 340) {
					resign_option_black = false;
					draw_sidebar(render, sidebar, icons, pieces, table);
				}
				//up green-beigi
				else if (color_option != 0 && event.button.x >= 847 && event.button.x < 877 && event.button.y >= 310 && event.button.y < 340) {
					color_option = 0;
					table_color = GREEN;
					table_color2 = BEIGI;
					draw_table(render, pieces, table, map, icons, mate, frames);
					draw_sidebar(render, sidebar, icons, pieces, table);
				}
				//up purple-gray
				else if (color_option != 1 && event.button.x >= 885 && event.button.x < 915 && event.button.y >= 310 && event.button.y < 340) {
					color_option = 1;
					table_color = PURPLE;
					table_color2 = GREY;
					draw_table(render, pieces, table, map, icons, mate, frames);
					draw_sidebar(render, sidebar, icons, pieces, table);
				}
				//up wood texture
				else if (color_option != 2 && event.button.x >= 923 && event.button.x < 953 && event.button.y >= 310 && event.button.y < 340) {
					color_option = 2;
					table_color = WOOD_1;
					table_color2 = WOOD_2;
					draw_table(render, pieces, table, map, icons, mate, frames);
					draw_sidebar(render, sidebar, icons, pieces, table);
				}
				//up resign
				else if (started && draw_option_black && event.button.x >= 960 && event.button.x < 990 && event.button.y >= 310 && event.button.y < 340) {
					draw_option_black = false;
					draw_sidebar(render, sidebar, icons, pieces, table);
				}
				//---------------Below new game icon---------------//
				//down resign
				else if (started &&  resign_option_white != 0 && event.button.x >= 810 && event.button.x < 840 && event.button.y >= 460 && event.button.y < 490) {
					resign_option_white = false;
					draw_sidebar(render, sidebar, icons, pieces, table);
				}
				//down left arrow
				else if (started && table->canBack() && event.button.x >= 847 && event.button.x < 877 && event.button.y >= 460 && event.button.y < 490) {
					int from = table->get_steps()[table->get_stepsPos()].from;
					int to = table->get_steps()[table->get_stepsPos()].to;
					table->get_table()[from] = table->get_steps()[table->get_stepsPos()].from_piece;
					if(to != from) table->get_table()[to] = table->get_steps()[table->get_stepsPos()].to_piece;;
					table->addto_stepsPos(-1);
					draw_sidebar(render, sidebar, icons, pieces, table);
					draw_table(render, pieces, table, map, icons, mate, frames);
				}
				//down reset
				else if (started && !table->isPresent() && event.button.x >= 885 && event.button.x < 915 && event.button.y >= 460 && event.button.y < 490) {
					table->set_stepsPos((int)table->get_steps().size() - 1);
					table->set_table();
					draw_sidebar(render, sidebar, icons, pieces, table);
					draw_table(render, pieces, table, map, icons, mate, frames);

				}
				//down right arrow
				else if (started && table->canForward() && event.button.x >= 923 && event.button.x < 953 && event.button.y >= 460 && event.button.y < 490) {
					table->addto_stepsPos(1);
					int from = table->get_steps()[table->get_stepsPos()].from;
					int to = table->get_steps()[table->get_stepsPos()].to;
					Pieces* temp = table->get_steps()[table->get_stepsPos()].to_piece;
					table->get_table()[to] = table->get_steps()[table->get_stepsPos()].from_piece;
					if (from == to) {
						table->get_table()[from] = temp;
					}
					else {
						table->get_table()[from] = nullptr;
					}
					draw_sidebar(render, sidebar, icons, pieces, table);
					draw_table(render, pieces, table, map, icons, mate, frames);
				}
				//down resign
				else if (started && draw_option_white && event.button.x >= 960 && event.button.x < 990 && event.button.y >= 460 && event.button.y < 490) {
					draw_option_white = false;
					draw_sidebar(render, sidebar, icons, pieces, table);
				}
				else if ((checkmate || draw) && event.button.x >= 300 && event.button.x < 500 && event.button.y >= 400 && event.button.y < 500) {
					saved = true;
					writeStepsToFile(table);
					draw_table(render, pieces, table, map, icons, mate, frames);
				}
				else if (blackPawnChange && event.button.x >= 810 && event.button.x < 890 && event.button.y >= 110 && event.button.y < 190) {
					changeTablePawn(table, new Queen(-1, BLACK));
					blackPawnChange = false;
					draw_sidebar(render, sidebar, icons, pieces, table);
					draw_table(render, pieces, table, map, icons, mate, frames);
				}
				else if (blackPawnChange && event.button.x >= 910 && event.button.x < 990 && event.button.y >= 110 && event.button.y < 190) {
					changeTablePawn(table, new Bishop(-1, BLACK));
					blackPawnChange = false;
					draw_sidebar(render, sidebar, icons, pieces, table);
					draw_table(render, pieces, table, map, icons, mate, frames);
				}
				else if (blackPawnChange && event.button.x >= 810 && event.button.x < 890 && event.button.y >= 210 && event.button.y < 290) {
					changeTablePawn(table, new Knight(-1, BLACK));
					blackPawnChange = false;
					draw_sidebar(render, sidebar, icons, pieces, table);
					draw_table(render, pieces, table, map, icons, mate, frames);
				}
				else if (blackPawnChange && event.button.x >= 910 && event.button.x < 990 && event.button.y >= 210 && event.button.y < 290) {
					changeTablePawn(table, new Rook(-1, BLACK));
					blackPawnChange = false;
					draw_sidebar(render, sidebar, icons, pieces, table);
					draw_table(render, pieces, table, map, icons, mate, frames);
				}
				else if (whitePawnChange && event.button.x >= 810 && event.button.x < 890 && event.button.y >= 510 && event.button.y < 590) {
				changeTablePawn(table, new Queen(-1, WHITE));
				whitePawnChange = false;
				draw_sidebar(render, sidebar, icons, pieces, table);
				draw_table(render, pieces, table, map, icons, mate, frames);
				}
				else if (whitePawnChange && event.button.x >= 910 && event.button.x < 990 && event.button.y >= 510 && event.button.y < 590) {
				changeTablePawn(table, new Bishop(-1, WHITE));
				whitePawnChange = false;
				draw_sidebar(render, sidebar, icons, pieces, table);
				draw_table(render, pieces, table, map, icons, mate, frames);
				}
				else if (whitePawnChange && event.button.x >= 810 && event.button.x < 890 && event.button.y >= 610 && event.button.y < 690) {
				changeTablePawn(table, new Knight(-1, WHITE));
				whitePawnChange = false;
				draw_sidebar(render, sidebar, icons, pieces, table);
				draw_table(render, pieces, table, map, icons, mate, frames);
				}
				else if (whitePawnChange && event.button.x >= 910 && event.button.x < 990 && event.button.y >= 610 && event.button.y < 690) {
				changeTablePawn(table, new Rook(-1, WHITE));
				whitePawnChange = false;
				draw_sidebar(render, sidebar, icons, pieces, table);
				draw_table(render, pieces, table, map, icons, mate, frames);
				}
				break;
			}
		}
		if (ended && started) {
			draw_option_black = true;
			draw_option_white = true;
			resign_option_black = true;
			resign_option_white = true;
			started = false;
			draw_table(render, pieces, table, map, icons, mate, frames);
			draw_sidebar(render, sidebar, icons, pieces, table);
		}
		if (started && ((!draw_option_black && !draw_option_white) || table->onlyTwoPieces()) ) { // Draw
			ended = true;
			show_play = true;
			draw = true;
			draw_sidebar(render, sidebar, icons, pieces, table);
			draw_table(render, pieces, table, map, icons, mate, frames);
		}
		if (started && !resign_option_black) { // White won
			table->set_player(false);
			checkmate = true;
			ended = true;
			show_play = true;
			draw_sidebar(render, sidebar, icons, pieces, table);
			draw_table(render, pieces, table, map, icons, mate, frames);
		}
		if (started && !resign_option_white) { // Black won
			table->set_player(true);
			checkmate = true;
			ended = true;
			show_play = true;
			draw_sidebar(render, sidebar, icons, pieces, table);
			draw_table(render, pieces, table, map, icons, mate, frames);
		}
	}
	SDL_DestroyTexture(map);
	SDL_DestroyTexture(pieces);
	SDL_DestroyTexture(mate);
	SDL_DestroyTexture(sidebar);
	SDL_DestroyTexture(icons);
	SDL_DestroyTexture(frames);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_Quit();
	return 0;

}

void Initialize(SDL_Window*& window, SDL_Renderer*& render, SDL_Texture*& map, SDL_Texture*& pieces, SDL_Texture*& frames, SDL_Texture*& sidebar, SDL_Texture*& icons, SDL_Texture*& mate){
	SDL_Init(SDL_INIT_EVERYTHING);
	//Window
	window = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) { std::cout << "Cannot create window!" << std::endl; SDL_Quit();  exit(1); }
	//Renderer
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (render == nullptr) { std::cout << "Cannot create renderer" << std::endl; SDL_DestroyWindow(window); SDL_Quit();  exit(1); }
	//Textures
	map = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 800);
	sidebar = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 800);
	pieces = IMG_LoadTexture(render, "./media/Piecess.png");
	frames = IMG_LoadTexture(render, "./media/Frames.png");
	icons = IMG_LoadTexture(render, "./media/Sidebar_Icons.png");
	mate = IMG_LoadTexture(render, "./media/Checkmate.png");
}


void draw_table(SDL_Renderer*& render, SDL_Texture*& pieces, Table*& table, SDL_Texture*& map, SDL_Texture*& icons, SDL_Texture*& mate, SDL_Texture*& frames) {
	SDL_SetRenderTarget(render, map);
	SDL_Rect from;
	SDL_Rect to;
	for (int i = 0; i < 64; i++) {

		//Background rects and colors
		(i + i / 8) % 2 == 0 ? from = table_color : from = table_color2;
		to = { 100 * (i % 8), 100 * (i / 8), 100, 100 };
		SDL_RenderCopy(render, icons, &from, &to);

		//Pieces on the board
		to = { 10 + (100 * (i % 8)),10 + (100 * (i / 8)),80,80 };
		if (table->get_tableElement(i) != nullptr) {
			SDL_RenderCopy(render, pieces, table->get_tableElement(i)->get_from(), &to);
		}

	}

	//if check draw red unfilled rect around the King
	if (table->checkCheck()) draw_Check(render, frames, table->checkKingPos());

	//Draw text in the middle
	if (draw) {
		from = { 0,300,199,100 };
		to = { 300,300,200,100 };
		SDL_RenderCopy(render, mate, &from, &to);
	}

	//Black-White Won text int the middle
	if (checkmate) {
		table->get_player() ? from = { 0,0,400,100 } : from = { 0,100,400,100 };
		to = { 200,300,400,100 };
		SDL_RenderCopy(render, mate, &from, &to);
	}

	//Save text in the middle
	if (draw || checkmate) {
		!saved ? from = { 0,200,199,100 } : from = { 200,200,199,100 };
		to = { 300,400,200,100 };
		SDL_RenderCopy(render, mate, &from, &to);
	}

	SDL_SetRenderTarget(render, NULL);
	SDL_RenderCopy(render, map, &copy_table, &copy_table);
	SDL_RenderPresent(render);
}

void draw_sidebar(SDL_Renderer*& render, SDL_Texture*& sidebar, SDL_Texture*& icons, SDL_Texture*& pieces, Table*& table) {
	SDL_SetRenderTarget(render, sidebar);
	SDL_Rect from;
	SDL_Rect to;
	std::vector<Pieces*> vec;

	//Background
	SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
	from = { 0,0,200,800 };
	SDL_RenderFillRect(render, &from);

	//Hit by black
	vec = table->get_hitbyBlack();
	for (int i = 0; i < (int)vec.size(); i++) {
		to = { 3 + 33 * (i % 6),3 + 33 * (i / 6),30,30 };
		SDL_RenderCopy(render, pieces, vec[i]->get_from(), &to);
	}

	//Hit by White
	vec = table->get_hitbyWhite();
	for (int i = 0; i < (int)vec.size(); i++) {
		to = { 2 + 25 * (i % 8),773 - 25 * (i / 8),20,20 };
		SDL_RenderCopy(render, pieces, vec[i]->get_from(), &to);
	}

	//New game icon
	show_play ? from = { 0,0,200,100 } : from = { 200,0,200,100 };
	to = { 10,355, 180,90 };
	SDL_RenderCopy(render, icons, &from, &to);

	//---------------Below new game icon---------------//
	//Resign
	resign_option_white && started ? from = { 400,150,50,50 } : from = { 450,150,50,50 };
	to = { 10, 460, 30,30 };
	SDL_RenderCopy(render, icons, &from, &to);

	//Left arrow
	table->canBack() && started ? from = {400,0,50,50} : from = { 450,0,50,50 };
	to = { 47, 460, 30,30 };
	SDL_RenderCopy(render, icons, &from, &to);

	//Reset arrow
	!table->isPresent() && started ? from = {400,100,50,50} : from = { 450,100,50,50 };
	to = { 85, 460, 30,30 };
	SDL_RenderCopy(render, icons, &from, &to);

	//Right arrow
	table->canForward() && started ? from = { 400,50,50,50 } : from = { 450,50,50,50 };
	to = { 123, 460, 30,30 };
	SDL_RenderCopy(render, icons, &from, &to);

	//Tie / Draw
	draw_option_white&& started ? from = { 400,200,50,50 } : from = { 450,200,50,50 };
	to = { 160, 460, 30,30 };
	SDL_RenderCopy(render, icons, &from, &to);

	//---------------Above new game icon---------------//

	//Resign
	resign_option_black&& started ? from = { 400,150,50,50 } : from = { 450,150,50,50 };
	to = { 10, 310, 30,30 };
	SDL_RenderCopy(render, icons, &from, &to);

	//Color-1
	color_option != 0 ? from = { 400,250,50,50 } : from = { 450,250,50,50 };
	to = { 47, 310, 30,30 };
	SDL_RenderCopy(render, icons, &from, &to);

	//Color-
	color_option != 1 ? from = { 400,300,50,50 } : from = { 450, 300, 50, 50 };
	to = { 85, 310, 30,30 };
	SDL_RenderCopy(render, icons, &from, &to);

	//TextureColor
	color_option != 2 ? from = { 400,350,50,50 } : from = { 450,350,50,50 };
	to = { 123, 310, 30,30 };
	SDL_RenderCopy(render, icons, &from, &to);

	//Tie / Draw
	draw_option_black && started ? from = { 400,200,50,50 } : from = { 450,200,50,50 };
	to = { 160, 310, 30,30 };
	SDL_RenderCopy(render, icons, &from, &to);

	//If pawn can be changed to better piece
	if (whitePawnChange) {
		//white queen
		from = { 100, 0, 100, 100 };
		to = { 10, 510, 80, 80 };
		SDL_RenderCopy(render, pieces, &from, &to);
		//white bishop
		from = { 200, 0, 100, 100 };
		to = { 110, 510, 80, 80 };
		SDL_RenderCopy(render, pieces, &from, &to);
		//white knight
		from = { 300, 0, 100, 100 };
		to = { 10, 610, 80, 80 };
		SDL_RenderCopy(render, pieces, &from, &to);
		//white rook
		from = { 400, 0, 100, 100 };
		to = { 110, 610, 80, 80 };
		SDL_RenderCopy(render, pieces, &from, &to);
	}
	else if(blackPawnChange) {
		//black queen
		from = { 100, 100, 100, 100 };
		to = { 10, 110, 80, 80 };
		SDL_RenderCopy(render, pieces, &from, &to);
		//black bishop
		from = { 200, 100, 100, 100 };
		to = { 110, 110, 80, 80 };
		SDL_RenderCopy(render, pieces, &from, &to);
		//black knight
		from = { 300, 100, 100, 100 };
		to = { 10, 210, 80, 80 };
		SDL_RenderCopy(render, pieces, &from, &to);
		//black rook
		from = { 400, 100, 100, 100 };
		to = { 110, 210, 80, 80 };
		SDL_RenderCopy(render, pieces, &from, &to);
	}

	from = { 0,0,200,800 };
	to = { 800,0,200,800 };
	SDL_SetRenderTarget(render, NULL);
	SDL_RenderCopy(render, sidebar, &from, &to);
	SDL_RenderPresent(render);
}

void deletePieceMotion(SDL_Renderer*& render, SDL_Texture*& map, SDL_Texture*& icons, int i) {
	SDL_Rect from;
	SDL_Rect to;
	SDL_SetRenderTarget(render, map);
	(i + i / 8) % 2 == 0 ? from = table_color : from = table_color2;
	to = { 100 * (i % 8), 100 * (i / 8), 100, 100 };
	SDL_RenderCopy(render, icons, &from, &to);
	SDL_SetRenderTarget(render, NULL);
	SDL_RenderCopy(render, map, &copy_table, &copy_table);
	SDL_RenderPresent(render);
}

void draw_possibleMoves(SDL_Renderer*& render, SDL_Texture*& map, SDL_Texture*& blueframe, Table*& table, std::vector<int> vec) {

	SDL_SetRenderTarget(render, map);
	SDL_Rect from;
	SDL_Rect to;
	for (int i = 0; i < (int)vec.size(); i++) {
		if (table->get_tableElement(vec[i]) != nullptr && table->get_tableElement(vec[i])->get_name() == "KING") continue;
		table->get_tableElement(vec[i]) == nullptr ? from = { 0,0,100,100 } : from = { 100,0,100,100 };
		to = { vec[i] % 8 * 100,vec[i] / 8 * 100,100,100 };
		SDL_RenderCopy(render, blueframe, &from, &to);
	}
	SDL_SetRenderTarget(render, NULL);
	SDL_RenderCopy(render, map, &copy_table, &copy_table);
	SDL_RenderPresent(render);
}

void draw_Check(SDL_Renderer*& render, SDL_Texture*& blueframe, int pos) {
	SDL_Rect from = { 100,100,100,100 };
	SDL_Rect to = { pos % 8 * 100, pos / 8 * 100,100,100 };
	SDL_RenderCopy(render, blueframe, &from, &to);
}

void writeStepsToFile(Table*& table) {
	std::ofstream file("Steps.txt");
	for (int i = 0; i < (int)table->get_steps().size(); i++) {
		file << (std::to_string(table->get_steps()[i].from) + " " + (table->get_steps()[i].from_piece == nullptr ? "NULL" : table->get_steps()[i].from_piece->get_name()) + " " + std::to_string(table->get_steps()[i].to) + " " + (table->get_steps()[i].to_piece == nullptr ? "NULL" : table->get_steps()[i].to_piece->get_name())) + "\n";
	}
	file.close();
}

void changeTablePawn(Table* &table, Pieces* changeTo) {
	table->get_table() = table->get_currentTable();
	table->set_stepsPos((int)table->get_steps().size() - 1);
	int target = table->get_steps()[table->get_steps().size() - 1].to;
	changeTo->set_pos(target);
	table->addto_allPieces(changeTo);
	table->addto_steps({target, target, table->get_table()[target], changeTo});
	table->addto_stepsPos(1);
	table->get_table()[target] = changeTo;
	table->set_currentTable(table->get_table());
}
