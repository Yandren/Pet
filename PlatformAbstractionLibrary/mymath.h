#ifndef MYMATH_H
#define MYMATH_H


template <class T> const T& min( const T& a, const T& b ) {
  return (a<b)?a:b;     
}

#endif