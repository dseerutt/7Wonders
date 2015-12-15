#include "MCTSImplementation.h"

#include "World.h"

#define set(bitboard, col, row) (bitboard |= (1LL << (((col) << 3) + (row))))

namespace game
{
	static std::vector<std::vector<uint64_t>> create_hash_values()
	{
		std::default_random_engine generator;
		std::uniform_int_distribution<uint64_t> distribution;
		std::vector<std::vector<uint64_t>> res(7, std::vector<uint64_t>(6, 0));
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				res[i][j] = distribution(generator);
			}
		}
		return res;
	}

	std::vector<std::vector<uint64_t>> MCTSImplementation::cross_hash_values = create_hash_values();
	std::vector<std::vector<uint64_t>> MCTSImplementation::circle_hash_values = create_hash_values();

	MCTSImplementation::MCTSImplementation()
	{
	}


	MCTSImplementation::~MCTSImplementation()
	{
	}

	void MCTSImplementation::set_state(const GameState& s)
	{
		state = s;
	}

	void MCTSImplementation::playout(std::mt19937& engine, int max_depth)
	{
		while (!end_of_game())
		{
			std::uniform_int_distribution<uint16_t> distribution(0, number_of_moves() - 1);
			uint16_t move = distribution(engine);
			play(move);
		}
	}

	bool MCTSImplementation::end_of_game() const
	{
		//return state.first_player_win || state.second_player_win || state.total_moves == 42;
		return world->m_age == (NUMBER_OF_AGES - 1) && world->m_players[0]->getHand().size() == 0;
	}

	bool MCTSImplementation::won(const Player& player) const
	{
		return world->hasWon(player);
	}

	bool MCTSImplementation::lost(const Player& player) const
	{
		return !world->hasWon(player);
	}

	bool MCTSImplementation::draw(const Player& player) const
	{
		return world->draw();
	}

	uint8_t MCTSImplementation::current_player() const
	{
		return 0;// state.total_moves & 1 ? CIRCLE : CROSS;
	}

	int MCTSImplementation::value(const Player& player) const
	{
		if (world->hasWon(player))
		{
			return 1;
		}
		else
		{
			return -1;
		}
		return 0;
	}

	uint16_t MCTSImplementation::number_of_moves() const
	{
		return state.moves.size();
	}

	std::set<int> MCTSImplementation::to_input_vector() const
	{
		std::set<int> res;
		/*int k = 0;
		if (current_player()) res.insert(k++);
		for (int col = 0; col < 7; ++col)
		{
			for (int row = 0; row < 6; ++row)
			{
				if (get(state.cross_bitboard, col, row)) res.insert(k++);
			}
		}
		for (int col = 0; col < 7; ++col)
		{
			for (int row = 0; row < 6; ++row)
			{
				if (get(state.circle_bitboard, col, row)) res.insert(k++);
			}
		}*/
		return res;
	}

	void MCTSImplementation::from_input_vector(const std::set<int>& input)
	{
		/*state = GameState();
		for (int index : input)
		{
			if (index == 1) continue;
			if (index <= 43)
			{
				index -= 2;
				state.cross_bitboard |= 1LL << (index + (index / 6) * 2);
			}
			else
			{
				index -= 44;
				state.circle_bitboard |= 1LL << (index + (index / 6) * 2);
			}
			state.total_moves += 1;
		}*/
	}

	void MCTSImplementation::play(uint16_t m)
	{
		/*uint8_t position = ((state.moves >> (m * 3)) & 7);
		uint8_t p = position * 3;
		uint8_t f = (state.free >> p) & 7;
		//    state.hash_value ^= current_player() == CIRCLE ? circle_hash_values[position][f] : cross_hash_values[position][f];
		//    state.board[position] |= current_player_representation() << (f << 1);
		if (current_player() == CROSS)
		{
			set(state.cross_bitboard, position, f);
		}
		else
		{
			set(state.circle_bitboard, position, f);
		}
		update_win();
		++f;
		state.free = (state.free & ~(((uint32_t)7) << p)) | (f << p);
		if (f == 6)
		{
			update_moves(m);
		}
		++state.total_moves;*/
		world->playout();
	}

	void MCTSImplementation::update_win()
	{
		/*if (has_won(state.cross_bitboard)) state.first_player_win = true;
		else if (has_won(state.circle_bitboard)) state.second_player_win = true;*/
	}

	void MCTSImplementation::update_moves(uint16_t move)
	{
		/*--state.nb_moves;
		uint32_t prefix = state.moves >> ((move + 1) * 3);
		uint8_t shift = 32 - move * 3;
		state.moves = (uint32_t)((uint64_t)state.moves << shift) >> shift;
		state.moves |= prefix << (move * 3);*/
	}

	bool MCTSImplementation::has_won(uint64_t bitboard)
	{
		int64_t y = bitboard & (bitboard >> 7);
		if (y & (y >> 2 * 7)) // check \ diagonal
			return true;
		y = bitboard & (bitboard >> 8);
		if (y & (y >> 2 * 8)) // check horizontal -
			return true;
		y = bitboard & (bitboard >> 9);
		if (y & (y >> 2 * 9)) // check / diagonal
			return true;
		y = bitboard & (bitboard >> 1);
		if (y & (y >> 2))     // check vertical |
			return true;
		return false;
	}

	bool MCTSImplementation::get(uint64_t bitboard, uint8_t col, uint8_t row) const
	{
		return bitboard & (1LL << ((col << 3) + row));
	}

	std::uint64_t MCTSImplementation::hash() const
	{
		return 0;// state.hash_value;
	}

	std::uint64_t MCTSImplementation::hash(std::uint16_t m) const
	{
		/*uint8_t position = ((state.moves   (m * 3)) & 7);
		uint8_t p = position * 3;
		uint8_t f = (state.free >> p) & 7;
		return state.hash_value ^ (current_player() == CIRCLE ? circle_hash_values[position][f] : cross_hash_values[position][f]);*/
		return 0;
	}

	GameState MCTSImplementation::get_state()
	{
		return state;
	}

	std::shared_ptr<game<GameState>> MCTSImplementation::do_copy() const
	{
		return std::shared_ptr<MCTSImplementation>(new MCTSImplementation(*this));
	}

	std::string MCTSImplementation::to_string() const
	{
		/*std::stringbuf buffer;
		std::ostream os(&buffer);
		for (int y = 5; y >= 0; --y)
		{
			for (int k = 0; k < 7; ++k) os << "+-";
			os << "+" << std::endl;
			for (int x = 0; x < 7; ++x)
			{
				os << "|" << (get(state.cross_bitboard, x, y) ? player_to_string(CROSS) : (get(state.circle_bitboard, x, y) ? player_to_string(CIRCLE) : " "));
			}
			os << "|" << std::endl;
		}
		for (int k = 0; k < 7; ++k) os << "+-";
		os << "+" << std::endl;
		for (int k = 0; k < 7; ++k) os << " " << k;
		os << std::endl;
		return buffer.str();*/
		return "";
	}

	std::string MCTSImplementation::player_to_string(const Player& player) const
	{
		//return player == CROSS ? "X" : (player == CIRCLE ? "O" : " ");
		return "";
	}

	std::string MCTSImplementation::move_to_string(uint16_t m) const
	{
		/*uint8_t position = ((state.moves >> (m * 3)) & 7);
		return std::to_string(position);*/
		return "";
	}
}