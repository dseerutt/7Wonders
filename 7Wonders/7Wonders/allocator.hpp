#ifndef __ALLOCATOR_HPP__
#define __ALLOCATOR_HPP__

#include "node.hpp"

namespace mcts
{
  class allocator
  {
    node* node_arena;
    node* limit;
    node* free_pointer;

    node* allocate_unsafe(unsigned int size);
    void copy(node* n1, node* n2, unsigned int prunning = 0);

  public:
    allocator(unsigned int size = 1000000U);
    ~allocator();
    node* allocate(unsigned int size);
    void clear();
    node* move(node* root, unsigned int prunning = 0);
    unsigned int size() const;
    unsigned int free_space() const;
  };
}

#endif
