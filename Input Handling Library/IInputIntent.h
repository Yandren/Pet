#ifndef __IInputIntent_H
#define __IInputIntent_H

class IInputIntent
{

public:
  //constructors/destructors
  IInputIntent(){}
  virtual ~IInputIntent(){}
  //methods
  virtual bool evoke() = 0;
  //members

private:
  //methods
  //members

}; //end of class IInputIntent

/*

class IState : public IInputIntent
{
public:
  IState(){}
  virtual ~IState(){}

  virtual bool evoke() = 0;
};

class IAction : public IInputIntent
{
public:
  IAction(){}
  virtual ~IAction(){}

  virtual bool evoke() = 0;
};

class IRange : public IInputIntent
{
public:
  IRange(){}
  virtual ~IRange(){}

  virtual bool evoke() = 0;
};

*/
#endif