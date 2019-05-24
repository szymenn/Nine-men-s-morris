#pragma once
#include "player.h"
class gamer;

typedef struct field{
	bool position;
	int id;
}field_t;
class game{
	field_t fields[24];
	static void draw_color(player &player1, player &player2);
public:
	game();
	static void print_board();
	void set_position(int position);
	void start_game();
	void move(player &player1, player &player2);
};