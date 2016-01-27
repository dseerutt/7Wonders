#pragma once
#include "game.hpp"
#include <random>
#include <array>
#include <iostream>
#include <memory>
#include <stdint.h>

#include "World.h"
#include "CardSet.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "DefaultMarvel.h"

namespace game
{
	struct GameState
	{
		uint8_t current_player = 0;
		World* world;

		std::vector<HumanPlayer> hp;
		std::vector<ComputerPlayer> cp;

		std::vector<DefaultMarvel> marvels;
	};

	class MCTSImplementation : public game<GameState>
	{
	public:
		MCTSImplementation();
		MCTSImplementation(World* w);
		~MCTSImplementation();
		MCTSImplementation(const MCTSImplementation& c4) = default;
		MCTSImplementation& operator=(const MCTSImplementation& c4) = default;
		bool end_of_game() const;
		int value(std::uint8_t player) const;
		bool won(std::uint8_t player) const;
		bool lost(std::uint8_t player) const;
		bool draw(std::uint8_t player) const;
		uint8_t current_player() const;
		std::uint16_t number_of_moves() const;
		void play(std::uint16_t m);
		void undo(std::uint16_t m) {}
		std::string player_to_string(std::uint8_t player) const;
		std::string move_to_string(std::uint16_t m) const;
		std::string to_string() const;
		//    void playout(std::mt19937& engine, int max_depth = -1);
		std::set<int> to_input_vector() const;
		void from_input_vector(const std::set<int>& input);
		GameState get_state();
		void set_state(const GameState& state);
		std::shared_ptr<game<GameState>> do_copy() const;
		std::uint64_t hash(std::uint16_t m) const;
		std::uint64_t hash() const;

		std::string to_string_before() const;
		std::string to_string_after() const;
		void displayResults() const;
		void display() const;

	private:
		unsigned int numberOfMoves(unsigned int player) const;
		void playerMove(int i, uint16_t m);
		void player2Move(uint16_t m);

		GameState state;

		static std::vector<std::vector<uint64_t>> cross_hash_values;
		static std::vector<std::vector<uint64_t>> circle_hash_values;
	};
	std::ostream& operator<<(std::ostream& os, const MCTSImplementation& c4);

}
