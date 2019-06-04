#pragma once
#include "player.h"
#include "linked_list.h"
#include "game_base.h"

//typedef struct field{
//	bool is_taken;
//	int id;
//}field_t;
//
//typedef struct field_line{
//	int line[3];
//	bool is_changed;
//	int id;
//}field_line_t;

class game : public game_base{
	void move(int player_id, int position) override;
	void play(player &player1, player &player2) override;
	void remove(player &plr) override;
public:
	game();
	~game();
	
};