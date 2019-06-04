#pragma once
#include "game_base.h"

class game_automated : public game_base
{
	int pick_random(linked_list<int> list);
	void set_auto(player &plr);
	//void play(player& player1, player& player2) override;
	void move_automated(int player_id, int position);
	void remove_automated(player &plr, int length);
	void set_automated_field(player &plr);
public:
	game_automated();
};
