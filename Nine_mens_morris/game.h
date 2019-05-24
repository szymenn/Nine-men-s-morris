#pragma once
#include "player.h"
class gamer;

typedef struct field{
	bool position;
	int id;
}field_t;
typedef struct available_field{
	int field;
	struct available_field *next;
}available_field_t;
class game{
	static field_t fields_[24];
	static void draw_color(player &player1, player &player2);
	static bool is_ended(player &player1, player &player2);
	static bool set_pawn(player &plr, int position);
	static void move(player &plr);
	static available_field_t *get_available_fields();
	static void set_field(player &plr);
	static void play(player &player1, player &player2);
public:
	game();
	static void print_board();
	void start_game();
	
};