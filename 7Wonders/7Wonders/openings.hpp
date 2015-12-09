#ifndef __OPENINGS_HPP__
#define __OPENINGS_HPP__

#include "allocator.hpp"
#include <vector>
#include "display_node.hpp"

namespace mcts
{
  class openings
  {
    allocator alloc_;
    node* root_;
    const unsigned int nb_visits_before_expansion_;

    void copy(node* src, node* dst, allocator& alloc) const;
    template <typename Game>
    void expand(Game& game, node* n, uint16_t move, int value);
  public:
    template <typename Game>
    openings(const Game& game, unsigned int nb_visits_before_expansion = 2);
    void copy_to(node* root, allocator& alloc) const;
    template <typename Game>
    void update(Game& game, const std::vector<uint16_t>& moves, int value);
    friend std::ostream& operator<<(std::ostream& os, const openings& op);
  };

  template <typename Game>
  openings::openings(const Game& game, unsigned int nb_visits_before_expansion) : nb_visits_before_expansion_(nb_visits_before_expansion)
  {
    root_ = alloc_.allocate(1);
    unsigned int nb_children = game.number_of_moves();
    node* children = alloc_.allocate(nb_children);
    for (unsigned int i = 0; i < nb_children; ++i)
      {
        node* child = children + i;
        child->get_statistics_ref().count = 1;
        child->get_statistics_ref().value = 0;
      }
  }

  template <typename Game>
  void openings::expand(Game& game, node* n, uint16_t move, int value)
  {
    unsigned int count = n->get_statistics().count;
    if (count >= nb_visits_before_expansion_)
      {
        unsigned int nb_children = game.number_of_moves();
        node* children = alloc_.allocate(nb_children);
        for (unsigned int i = 0; i < nb_children; ++i)
	  {
            node* child = children + i;
            child->get_statistics_ref().count = 1;
            child->get_statistics_ref().value = 0;
	  }
        n->set_children(children);
        n->set_number_of_children(nb_children);
        children[move].update(value);
      }
  }

  template <typename Game>
  void openings::update(Game& game, const std::vector<uint16_t>& moves, int value)
  {
    node* pred = nullptr;
    node* current = root_;
    int k = 0;
    while (true)
      {
        current->update(value);
        value = -value;
        if (current->is_leaf()) break;
        uint16_t m = moves[k++];
        game.play(m);
        pred = current;
        current = current->get_children() + m;
        if (current->is_proven())
	  {
            if (current->is_lost()) pred->set_won();
            else
	      {
                const uint16_t nb_children = pred->get_number_of_children();
                node* const children = pred->get_children();
                bool all_won = true;
                for (uint16_t i = 0; i < nb_children; ++i)
		  {
                    node* child = children + i;
                    if (!child->is_won())
		      {
                        all_won = false;
                        break;
		      }
		  }
                if (all_won) pred->set_lost();
	      }
            return;
	  }
      }
    if (!game.end_of_game())
      {
        expand(game, current, moves[k], value);
      }
    else
      {
        if (value == 1) current->set_won();
        else if (value == -1)
	  {
            current->set_lost();
            if (pred != nullptr) pred->set_won();
	  }
      }
  }
}

#endif
