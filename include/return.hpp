#ifndef LOXPP_RETURN_HPP
#define LOXPP_RETURN_HPP

#include <stdexcept>

class Return : public std::runtime_error
{
  public:
    Return() : runtime_error("Return sentinel") {}
};

#endif //LOXPP_RETURN_HPP
