#include "player.h"
player::player()
= default;

int player::get_id() const
{
	return id_;
}

void player::set_id(const int id)
{
	id_ = id;
}
