#pragma once
class game{
	bool positions_[24]{};
public:
	game();
	void print_state();
	void set_position(int position);
	bool get_position_info();
};