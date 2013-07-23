#ifndef __IINPUTMAPPING_H
#define __IINPUTMAPPING_H

class IInputMapping
{

public:
  //constructors/destructors
  IInputMapping(){}
  virtual ~IInputMapping(){}
  //methods
  virtual bool evoke() = 0;
  //members

private:
  //methods
  //members

}; //end of class IInputMapping


class IState : public IInputMapping
{
public:
  IState(){}
  virtual ~IState(){}

  virtual bool evoke() = 0;
};

class IAction : public IInputMapping
{
public:
  IAction(){}
  virtual ~IAction(){}

  virtual bool evoke() = 0;
};

class IRange : public IInputMapping
{
public:
  IRange(){}
  virtual ~IRange(){}

  virtual bool evoke() = 0;
};
#endif