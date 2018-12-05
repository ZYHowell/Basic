/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "parser.cpp"
#include "statement.h"
#include "../StanfordCPPLib/tokenscanner.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}
Comment::Comment(string text,string li):t(text),origin(li){}

int Comment::execute(EvalState & state){
   return;
}

Comment::~Comment(){}

Assignment::Assignment(string text,string li):t(text),origin(li){}

int Assignment::execute(EvalState & state){
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(t);
   try{
      parseExp(scanner)->eval(state);
   } catch (ErrorException & ex){
      error(ex.getMessage());
   }
   return 0;
}

Assignment::~Assignment(){}

Print::Print(string text,string li):t(text),origin(li){}

Print::execute(EvalState & state){
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(t);
   try{
      printf("%d\n",parseExp(scanner)->eval(state));
   } catch (ErrorException & ex){
      error(ex.getMessage());
   }
}
Print::~Print(){}

Input::Input(string text,string li):t(text),origin(li){}

int Input::execute(EvalState & state){
   TokenScanner scanner;
   int temp;string name;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(t);
   printf("%d\n");
   scanf("%d",&temp);
   name = scanner.nextToken();
   judgeIt(name);
   if (scanner.hasMoreTokens()) error("Uncorrect variance");
   state.setValue(t,temp);
   return 0;
}

Input::~Input(){}

Halt::Halt(string text,string li):t(text),origin(li){}

int Halt::execute(EvalState & state){
   return 1;
}

Halt::~Halt(){}