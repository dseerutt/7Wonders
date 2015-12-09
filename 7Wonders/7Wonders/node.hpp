#ifndef __NODE_HPP__
#define __NODE_HPP__

#include "statistics.hpp"
#include <string>
#include <iostream>
#include <limits>
#include <stdint.h>

#define NODE_WON_VALUE 1e15f
#define NODE_LOST_VALUE -1e15f

namespace mcts
{
  class node
  {    
    statistics stats;
    bool flag = false;
    uint16_t number_of_children = 0;
    node* children = nullptr;
    
  public:
    inline uint16_t get_winning_index() const;
    inline bool is_leaf() const;
    inline uint16_t get_number_of_children() const;
    inline node* get_children() const;
    inline void set_number_of_children(uint16_t n);
    inline void set_children(node* n);
    inline void set_won();
    inline void set_lost();
    inline bool is_proven() const;
    inline bool is_won() const;
    inline bool is_lost() const;
    inline const statistics& get_statistics() const;
    inline statistics& get_statistics_ref();
    inline void set_statistics(const statistics& s);
    inline bool test_and_set();
    inline void update(int value);
    inline void update_count();
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const node& n);
  };

  bool node::is_proven() const
  {
    return is_won() || is_lost();
  }

  void node::set_won()
  {
    stats.value = NODE_WON_VALUE;
  }
  
  void node::set_lost()
  {
    stats.value = NODE_LOST_VALUE;
  }
  
  bool node::is_won() const
  {
    return stats.value > 1.1;
  }
  
  bool node::is_lost() const
  {
    return stats.value < -1.1;
  }

  bool node::is_leaf() const
  {
    return get_number_of_children() == 0 || get_children() == nullptr;
  }

  uint16_t node::get_number_of_children() const
  {
    uint16_t res;
#pragma omp atomic read
    res = number_of_children;
    return res;
  }
  node* node::get_children() const
  {
    node* res;
#pragma omp atomic read
    res = children;
    return res;
  }
  void node::set_number_of_children(uint16_t n)
  {
#pragma omp atomic write
    number_of_children = n;
  }
  void node::set_children(node* n)
  {
#pragma omp atomic write
    children = n;
  }
  const statistics& node::get_statistics() const
  {
    return stats;
  }
  statistics& node::get_statistics_ref()
  {
    return stats;
  }
  void node::set_statistics(const statistics& s)
  {
    stats = s;
  }
  bool node::test_and_set()
  {
    bool res;
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma omp atomic capture
    {
      res = flag;
      flag = true;
    }
    return res;
  }

  void node::update_count()
  {
    ++stats.count;
  }
  
  void node::update(int v)
  {
    unsigned int count = stats.count;
    float value = stats.value;
    ++count;
    value += (v - value) / count;
    stats.value = value;
    stats.count = count;
  }

}

#endif
