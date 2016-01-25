#include "MCTSImplementation.h"

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

	MCTSImplementation::MCTSImplementation() : game(), world(new World(1, 2))
	{
	}
	MCTSImplementation::MCTSImplementation(World* w) : world(w)
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

	bool MCTSImplementation::won(uint8_t player) const
	{
		if (player == 0)
		{
			for (Player* p : players)
			{
				if (world->hasWon(*p))
					return true;
			}
			return false;
		}
		else
		{
			for (Player* p : players)
			{
				if (world->hasWon(*p))
					return false;
			}
			return true;
		}
	}

	bool MCTSImplementation::lost(uint8_t player) const
	{
		return !won(player);
	}

	bool MCTSImplementation::draw(uint8_t player) const
	{
		return world->draw();
	}

	uint8_t MCTSImplementation::current_player() const
	{
		return 0;// state.total_moves & 1 ? CIRCLE : CROSS;
	}

	int MCTSImplementation::value(uint8_t player) const
	{
		if (won(player))
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
		return res;
	}

	void MCTSImplementation::from_input_vector(const std::set<int>& input)
	{
	}

	void MCTSImplementation::play(uint16_t m)
	{
		uint8_t p = current_player();


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
		return "[TOSTRING]";
	}

	std::string MCTSImplementation::player_to_string(uint8_t player) const
	{
		//return player == CROSS ? "X" : (player == CIRCLE ? "O" : " ");
		if (player == 0)
			return "Human Player";
		else
			return "Computer Player";
	}

	std::string MCTSImplementation::move_to_string(uint16_t m) const
	{
		/*uint8_t position = ((state.moves >> (m * 3)) & 7);
		return std::to_string(position);*/
		return std::to_string(m);
	}

	unsigned int MCTSImplementation::numberOfMoves(uint8_t player) const
	{
		std::vector<unsigned int> nbMoves(players.size());
		for (int i = 0; i < players.size(); i++)
		{
			Player& p = *players.at(i);
			nbMoves[i] = 0;
			nbMoves[i] += p.getPlayableCards().size();
			nbMoves[i] += p.getHand().size();
			if (p.getMarvel()->canUpgrade(p.getResources()))
			{
				nbMoves[i] += p.getHand().size();
			}
		}

		unsigned int res = 0;
		for (unsigned int n : nbMoves)
		{
			res += n;
		}
		return res;
	}

}