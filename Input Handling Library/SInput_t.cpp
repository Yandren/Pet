#include "SInput_t.h"

//Why include std in the header? Might as well just separate
SInput_t::SInput_t(const char * c)
{
  identifier.assign(c);
}

SInput_t::SInput_t(std::string s)
{
  identifier.assign(s);
}

int
SInput_t::getValue()
{
  return (int)identifier.c_str();
}

const char *
SInput_t::getIdentifier()
{
 return identifier.c_str();
}