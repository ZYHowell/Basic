/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

  Statement() = default;
  Statement(std::string text,std::string li);

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual int execute(EvalState & state) = 0;

public:
  std::string t; 
  std::string origin;
};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */
class Comment: public Statement{
public:
  Comment(std::string text,std::string li);
  virtual int execute(EvalState & state);
  virtual ~Comment();
};
class Assignment: public Statement{
public:
  Assignment(std::string text,std::string li);
  virtual int execute(EvalState & state);
  virtual ~Assignment();
};
class Print: public Statement{
public:
  Print(std::string text,std::string li);
  virtual int execute(EvalState & state);
  virtual ~Print();
};
class Input: public Statement{
public:
  Input(std::string text,std::string li);
  virtual int execute(EvalState & state);
  virtual ~Input();
};
class Halt: public Statement{
public:
  Halt(std::string text,std::string li);
  virtual int execute(EvalState & state);
  virtual ~Halt();
};
class Goto: public Statement{
public:
  Goto(std::string text,std::string li);
  virtual int execute(EvalState & state);
  virtual ~Goto();
};
class Judge: public Statement{
private:
  Expression *lhs;
  Expression *rhs;
  string op;
  int tol;
public:
  Judge(std::string text,std::string li);
  virtual int execute(EvalState & state);
  virtual ~Judge();
};

#endif
