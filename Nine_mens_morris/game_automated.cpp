#include "game_automated.h"

game_automated::game_automated()
= default;

int game_automated::pick_random(linked_list<int> list)
{
	if(list.is_empty())
	{
		return -1;
	}
	const int rand_pick = rand() % list.length() + 0;
	return list[rand_pick];
}

