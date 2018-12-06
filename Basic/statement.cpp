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
   return -2;
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
   return -2;
}

Assignment::~Assignment(){}

Print::Print(string text,string li):t(text),origin(li){}

int Print::execute(EvalState & state){
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(t);
   try{
      printf("%d\n",parseExp(scanner)->eval(state));
   } catch (ErrorException & ex){
      error(ex.getMessage());
   }
   return -2;
}
Print::~Print(){}

Input::Input(string text,string li):t(text),origin(li){}

int Input::execute(EvalState & state){
   TokenScanner scanner;
   int temp;
   printf(" ? ");
   string tt;bool redo = true;
   while (redo)
      try{
         scanf("%s",tt);
         temp = stringToInteger(tt);
         redo = false;
      } catch(ErrorException & ex){
         printf("INVALID NUMBER\n");
         redo = true;
      }
   state.setValue(t,temp);
   return -2;
}

Input::~Input(){}

Halt::Halt(string text,string li):t(text),origin(li){}

int Halt::execute(EvalState & state){
   return -1;
}

Halt::~Halt(){}

Goto::Goto(string text,string li):t(text),origin(li){}

int Goto::execute(EvalState & state){
   return stringToInteger(t);
}

Goto::~Goto(){}

Judge::Judge(string text,string li):t(text),origin(li){
   TokenScanner scanner;scanner.scanNumbers();scanner.ignoreWhitespace();scanner.setInput(text);
   string leftexp;leftexp.clear();
   TokenScanner tempSc;tempSc.ignoreWhitespace();tempSc.scanNumbers();

   while (scanner.hasMoreTokens()){
      temp = scanner.nextToken();
      if ((temp == "<")||(temp == ">")||(temp == "=")) break;
      leftexp = leftexp + ' ' + temp;
   }
   tempSc.setInput(leftexp);
   lhs = parseExp(tempSc);

   op = temp;
      
   lefttemp = scanner.nextToken();
   while (scanner.hasMoreTokens()){
      temp = scanner.nextToken();
      if ((temp == "THEN")) break;
      leftexp = leftexp + ' ' + temp;
   }
   tempSc.setInput(leftexp);
   rhs = parseExp(tempSc);

   temp = scanner.nextToken();
   tol = stringToInteger(temp);
}

int Judge::execute(EvalState & state){
   if (op == "=" && (lhs->eval(state) == rhs->eval(state))) return tol;
   if (op == ">" && (lhs->eval(state) >  rhs->eval(state))) return tol;
   if (op == "<" && (lhs->eval(state) <  rhs->eval(state))) return tol;
   return -2;
}

Judge::~Judge(){
   delete lhs;
   delete rhs;
}