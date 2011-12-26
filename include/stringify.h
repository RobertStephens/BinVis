#ifndef STRINGIFY_H
#define STRINGIFY_H

#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>

class BadConversion : public std::runtime_error {
public:
 BadConversion(const std::string& s)
      : std::runtime_error(s) {}
};

template<class _type>
inline std::string stringify(_type x)
{
  std::ostringstream o;
  if (!(o << std::fixed << x))
    throw BadConversion("stringify()");
  return o.str();
}

template<class _type>
inline _type convertTo(const std::string& s)
{
  std::istringstream i(s);
  _type x;
  if (!(i >> x))
    throw BadConversion("convertTo(\"" + s + "\")");
  return x;
}

#endif
