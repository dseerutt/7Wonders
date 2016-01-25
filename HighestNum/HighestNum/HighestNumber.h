#pragma once
#include "game.hpp"

namespace game
{
	struct hn_state
	{
		uint8_t current_player = 0;
		uint8_t player1_value;
		uint8_t player2_value;
		uint16_t nb_moves = 10;
		uint8_t turn = 0;
		/*bool first_player_win = false;
		bool second_player_win = false;*/
	};

	class HighestNumber : public game<hn_state>
	{
	private:
		hn_state state;

	public:
		HighestNumber();
		~HighestNumber();

		bool end_of_game() const;
		int value(std::uint8_t player) const;
		bool won(std::uint8_t player) const;
		bool lost(std::uint8_t player) const;
		bool draw(std::uint8_t player) const;
		uint8_t current_player() const;
		std::uint16_t number_of_moves() const;
		void play(std::uint16_t m);
		void undo(std::uint16_t m) {};
		std::string player_to_string(std::uint8_t player) const;
		std::string move_to_string(std::uint16_t m) const;
		std::string to_string() const;
		//virtual void playout(std::mt19937& engine, int max_depth = -1);
		std::set<int> to_input_vector() const;
		void from_input_vector(const std::set<int>& input);
		hn_state get_state();
		void set_state(const hn_state& state);
		std::shared_ptr<game<hn_state>> do_copy() const;
		std::uint64_t hash(std::uint16_t m) const;
		std::uint64_t hash() const;

	private:
		int move_to_value(uint16_t m) const;
		uint16_t value_to_move(int v) const;
	};
	std::ostream& operator<<(std::ostream& os, const HighestNumber& c4);
}

