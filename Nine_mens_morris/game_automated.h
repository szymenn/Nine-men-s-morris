#pragma once
#include "game_base.h"

class game_automated : public game_base
{
	game_automated();
	int pick_random(linked_list<int> list);
	void play(player& player1, player& player2) override;
	void move(int player_id, int position) override;
	void remove(player& plr) override;
};
