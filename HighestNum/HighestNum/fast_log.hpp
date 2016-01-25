#ifndef __FAST_LOG_HPP__
#define __FAST_LOG_HPP__

namespace util
{
  class fast_log
  {
  public:
    fast_log(int mantissa_nb_bits = 11);
    ~fast_log();
    inline float log(float v) const;
  private:
    union int_float
    {
      int _int;
      float _float;
    };
    float* lookup_table;    
    const int mantissa_shift;
    const int MAX_MANTISSA_NB_BITS = 23;
  };

  float fast_log::log(float val) const
  {
    int_float x;
    x._float = val;
    int exponent = ((x._int >> MAX_MANTISSA_NB_BITS) & 255) - 127;
    x._int &= 0x7FFFFF;
    x._int >>= mantissa_shift;
    return (lookup_table[x._int] + float(exponent)) * 0.69314718f;
  }
}

#endif
