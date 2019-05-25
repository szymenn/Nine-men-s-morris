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
	static int field_moves_[24][4];
	static void draw_color(player &player1, player &player2);
	static bool is_ended(player &player1, player &player2);
	static bool set_pawn(int player_id, int position);
	static void move(int player_id, int position);
	static void print_available_for_position(int position);
	static bool pick_field(int position);
	static available_field_t *get_available_fields();
	static bool is_available(int field);
	static void set_field(int player_id);
	static available_field_t *get_available_for_position(int position);

	static void play(player &player1, player &player2);
public:
	game();
	static void print_board();
	void start_game();
	
};