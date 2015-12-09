#include "fast_log.hpp"
#include <cassert>
#include <limits>

namespace util
{
  fast_log::fast_log(int mantissa_nb_bits) 
    : mantissa_shift(MAX_MANTISSA_NB_BITS - mantissa_nb_bits)
  {
    assert(sizeof(int) == 4);
    assert(std::numeric_limits<float>::is_iec559);
    lookup_table = new float[1 << mantissa_nb_bits];
    int_float x;
    x._int = 0x3F800000;
    int incr = (1 << mantissa_shift);
    int p = (1 << mantissa_nb_bits);
    float inv_log_two = 1.0f / log(2.0f);
    for (int i = 0; i < p; ++i)
      {
	lookup_table[i] = log(x._float) * inv_log_two;
	x._int += incr;
      }
  }
  
  fast_log::~fast_log()
  {
    delete[] lookup_table;
  }
}
