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
#include "program.h"
#include "statement.h"
#include "parser.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

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
   scanner.setInput(l);
   string temp = scanner.nextToken();
   if (temp == "REM") return true;
   if (temp == "LET"){
      parseExp(scanner);
      return true;
   }
   if ((temp == "INPUT")||(temp == "PRINT")||){
      temp = scanner.nextToken();
      if (temp[0]>='0' && (temp[0]<='9')) return false;
      for (auto i : temp)
         if ( !( (i >= '0'&& i <= '9') || (i >= 'a' && i<= 'z') || 
         (i >= 'A' && i <= 'Z') || (i != '_')) ) return false;
      return !scanner.hasMoreTokens();
   }
   if (temp == "END")
      return !scanner.hasMoreTokens();
}

void Program::addSourceLine(int lineNumber, string line, string li){
   if (!correctLine(line)) error("SYNTAX ERROR");
   if (map.count(lineNumber)) map.erase(lineNumber); 
   if (order == "REM")
         map[lineNumber] = new Comment(line,li);
   else if (order == "LET")
         map[lineNumber] = new Assignment(line,li);
   else if (order == "PRINT")
         map[lineNumber] = new Print(line,li);
   else if (order == "INPUT")
         map[lineNumber] = new Input(line,li);
   else if (order == "END")
         map[lineNumber] = new Halt(line,li);
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
   map<int, Statement*>::iterator iter = s.begin();
   return iter->first;
   return 0;
}

int Program::getNextLineNumber(int lineNumber) {
   map<int, Statement*>::iterator iter = s.find(lineNumber);
   if (iter == s.end()) return 0;
   iter++;
   return iter->first;
   return 0;
}

void Program::clear() {
   for (auto i : s){
      s.erase(i.first);
   }
}

void Program::list(){
   for (auto i : s){
      printf("%d %s\n",i.first,i.second->origin);
   }
}

void Program::run(EvalState & state){
   int temp;
   map<int, Statement*>::iterator iter = s.begin();
   while (iter != s.end()){
   temp = i.second->execute();
   if (temp == 0) iter++;
   else if (temp == 1) break;
   else iter = 
   }
   }
}