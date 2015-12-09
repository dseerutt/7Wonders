#ifndef __OMP_UTIL_HPP__
#define __OMP_UTIL_HPP__

#include <omp.h>

namespace util
{
  struct omp_util
  {
    static int get_num_threads();
    static int get_thread_num();
  };
}

#endif
