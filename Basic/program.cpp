/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "exp.h"
#include "parser.h"
#include "statement.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/strlib.h"

using namespace std;

Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {
   for (auto i : s){
      delete i.second;
   }
}

bool correctLine(string line){
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   string temp = scanner.nextToken();
   if (temp == "REM") return true;
   if (temp == "LET"){
      CompoundExp *tempexp = parseExp(scanner);
      judgeExp(temp)
      return true;
   }
   if ((temp == "INPUT")||(temp == "PRINT")||){
      
   }
   if (temp == "END")
      return !scanner.hasMoreTokens();
   if (temp == "GOTO"){
      temp = scanner.nextToken();
      if (stringToInteger(temp) <= 0) error("SYNTAX ERROR");
      return scanner.hasMoreTokens();
   }
   if (temp == "IF"){

   }
}

void Program::addSourceLine(int lineNumber, string line, string li){
   if (!correctLine(line)) error("SYNTAX ERROR");
   if (s.count(lineNumber)) s.erase(lineNumber); 
   if (order == "REM")
      s[lineNumber] = new Comment(line,li);
   else if (order == "LET")
      s[lineNumber] = new Assignment(line,li);
   else if (order == "PRINT")
      s[lineNumber] = new Print(line,li);
   else if (order == "INPUT")
      s[lineNumber] = new Input(line,li);
   else if (order == "END")
      s[lineNumber] = new Halt(line,li);
   else if (order == "GOTO")
      s[lineNumber] = new Goto(line,li);
   else if (order == "IF")
      s[lineNumber] = new Judge(line,li);
   }
}

void Program::removeSourceLine(int lineNumber) {
   s.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
   if (s.count(lineNumber)) return s[lineNumber]->t;
   return "";
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
   return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
   return s.begin()->first;
}

int Program::getNextLineNumber(int lineNumber) {
   map<int, Statement*>::iterator iter = s.find(lineNumber);
   if (iter == s.end()) return 0;
   iter++;
   return iter->first;
}

void Program::clear() {
   for (auto i : s){
      s.erase(i.first);
   }
}

void Program::list(){
   for (auto i : s){
      printf("%s\n",i.second->origin);
   }
}

void Program::run(EvalState & state){
   int temp;
   map<int, Statement*>::iterator iter = s.begin();
   while (iter != s.end()){
      temp = i.second->execute();
      if (temp == 0) iter++;
      else if (temp == -1) break;
      else iter = s.find(temp);
   }
}

bool correctName(string nam){
   if (nam[i] >= '0' && nam[i] <= '9') return false;
   for (auto i : nam)
   if ( !( (i >= '0'&& i <= '9') || (i >= 'a' && i<= 'z') || 
         (i >= 'A' && i <= 'Z') ) ) return false;
   return ((nam == "RUN") || (nam == "LIST") || (nam == "CLEAR") ||
   (nam == "QUIT") || (nam == "HELP") || (nam == "LET") || (nam == "REM") || 
   (nam == "PRINT") || (nam == "INPUT") || (nam == "END") || (nam == "IF") ||
   (nam == "THEN") || (nam == "GOTO"));
}