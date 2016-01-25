#ifndef __STATISTICS_HPP__
#define __STATISTICS_HPP__

#include <string>

namespace mcts
{
  struct statistics
  {
    unsigned int count = 0;
    float value = 0;
    std::string to_string() const;
  };
}

#endif
