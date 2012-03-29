#ifndef MATH_H
#define MATH_H

template <class T> const T& min( const T& a, const T& b ) {
  return (a<b)?a:b;     
}

#endif