#include "allocator.hpp"
#include <iostream>
#include <cstring>

namespace mcts
{
  allocator::allocator(unsigned int size)
  {
    std::cout << "allocator initialization..." << std::endl;
    node_arena = new node[size];
    std::cout << "allocator initialization done" << std::endl;
    limit = node_arena + size;
    free_pointer = node_arena;
  }
   
  allocator::~allocator()
  {
    delete[] node_arena;
  }
 
  node* allocator::allocate(unsigned int size)
  {    
    node* n;
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma omp atomic capture
    {
      n = free_pointer;
      free_pointer += size;
    }
    memset(n, 0, sizeof(node) * size);
    if (n + size >= limit) throw "allocate_children: not enough memory";
    return n;
  }

  unsigned int allocator::size() const
  {
    return limit - node_arena;
  }

  unsigned int allocator::free_space() const
  {
    return limit - free_pointer;
  }

  void allocator::clear()
  {
    free_pointer = node_arena;
  }
 
  node* allocator::allocate_unsafe(unsigned int size)
  {
    node* n = free_pointer;
    free_pointer += size;
    memset(n, 0, sizeof(node) * size);
    if (n + size > limit) throw "allocate_children: not enough memory";
    return n;
  }
  
  void allocator::copy(node* n1, node* n2, unsigned int prunning)
  {
    if (n1->get_statistics().count < prunning) return;
    n2->set_statistics(n1->get_statistics());
    unsigned int nb_children = n1->get_number_of_children();
    n2->set_number_of_children(nb_children);
    if (nb_children == 0) return;
    n2->set_children(allocate_unsafe(nb_children));
    node* children1 = n1->get_children();
    node* children2 = n2->get_children();
    for (unsigned int i = 0; i < nb_children; ++i) 
      {
	copy(children1 + i, children2 + i, prunning);
      }
  }

  node* allocator::move(node* root, unsigned int prunning)
  {
    node* r = allocate_unsafe(1);
    copy(root, r, prunning);
    free_pointer = node_arena;
    node* res = allocate_unsafe(1);
    copy(r, res);
    return res;
  }
}
