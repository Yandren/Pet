#ifndef __IINPUTMAPPING_H
#define __IINPUTMAPPING_H

#include "SInput_t.h"

class IInputMapping
{

public:
  //constructors/destructors
  IInputMapping(){}
  ~IInputMapping(){}
  //methods
 
  //members

private:
  //methods
  //members

}; //end of class IInputMapping


class IState : public IInputMapping
{
  IState(){}
  virtual ~IState(){}
};

class IAction : public IInputMapping
{
  IAction(){}
  virtual ~IAction(){}
};

class IRange : public IInputMapping
{
  IRange(){}
  virtual ~IRange(){}
};
#endif