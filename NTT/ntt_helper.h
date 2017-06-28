
using ull = unsigned int;


template <int exp>
struct PowULL{
  static constexpr ull pow(const ull base)
  {
    return 0;
  }
};

template <>
struct PowULL<1>{
  static constexpr ull pow(const ull base){return base;}
};