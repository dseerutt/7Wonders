#ifndef __MCTS_HPP__
#define __MCTS_HPP__

#include <random>
#include <chrono>
#include <vector>
#include "game.hpp"
#include "node.hpp"

namespace mcts
{
  template <typename Game>
  class mcts
  {
  protected:
    Game& game;
    std::chrono::milliseconds milliseconds;
    std::vector<std::mt19937> generators;
    node* root;
    
  public:
    mcts(Game& game, uint32_t milliseconds) : game(game), milliseconds(milliseconds) {}

    virtual void reset() = 0;
    virtual uint16_t select_move() = 0;
    virtual void last_moves(uint16_t m1, uint16_t m2) {}
    virtual void last_moves(const std::vector<uint16_t>& moves) {}
  };
}

#endif
