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
#include "StanfordCPPLib/error.h"
#include "StanfordCPPLib/tokenscanner.h"
#include "StanfordCPPLib/strlib.h"

using namespace std;

Program::Program() {
	// Replace this stub with your own code
}

Program::~Program() {
  s.clear();
}

bool correctLine(string line, string order) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	if (order == "REM") return true;
	if (order == "LET") {
		Expression *tempexp = parseExp(scanner);
		return judgeExp(tempexp);
	}
	if (order == "INPUT") {
		if (!correctName(scanner.nextToken())) error("SYNTAX ERROR5");
		return !scanner.hasMoreTokens();
	}
	if (order == "PRINT") {
		Expression *tempexp = parseExp(scanner);
		return judgeExp(tempexp);
	}
	if (order == "END")
		return !scanner.hasMoreTokens();
	if (order == "GOTO") {
		order = scanner.nextToken();
		if (stringToInteger(order) < 0) error("SYNTAX ERROR6");
		return !scanner.hasMoreTokens();
	}
	if (order == "IF") {
		string leftexp;leftexp.clear();
		TokenScanner tempSc;tempSc.ignoreWhitespace();tempSc.scanNumbers();

		while (scanner.hasMoreTokens()) {
			order = scanner.nextToken();
			if ((order == "<") || (order == ">") || (order == "=")) break;
			leftexp = leftexp + ' ' + order;
		}
		if (!((order == "<") || (order == ">") || (order == "="))) error("SYNTAX ERROR7");
		tempSc.setInput(leftexp);
		Expression *tempexp = parseExp(tempSc);
		if (!judgeExp(tempexp)) error("SYNTAX ERROR8");
		delete tempexp;

		leftexp.clear();
		while (scanner.hasMoreTokens()) {
			order = scanner.nextToken();
			if ((order == "THEN")) break;
			leftexp = leftexp + ' ' + order;
		}
		if (!(order == "THEN")) error("SYNTAX ERROR9");
		tempSc.setInput(leftexp);
		tempexp = parseExp(tempSc);
		if (!judgeExp(tempexp)) error("SYNTAX ERRORA");
		delete tempexp;

		order = scanner.nextToken();
		if (scanner.getTokenType(order) != NUMBER) error("SYNTAX ERRORB");
		return (stringToInteger(order) >= 0);
	}
	error("SYNTAX ERRORX");
	return false;
}

void Program::addSourceLine(int lineNumber, string li) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(li);
	scanner.nextToken();                            //DEAL WITH LINE NUMBER
	string order = scanner.nextToken();

	string line = scanner.nextToken();
	while (scanner.hasMoreTokens())
		line = line + ' ' + scanner.nextToken();     //AFTER THIS, THE LINE IS PURE
	if (!correctLine(line, order)) error("SYNTAX ERRORC");

	if (s.count(lineNumber)) s.erase(lineNumber);
	if (order == "REM")
		s[lineNumber] = new Comment(line, li);
	else if (order == "LET")
		s[lineNumber] = new Assignment(line, li);
	else if (order == "PRINT")
		s[lineNumber] = new Print(line, li);
	else if (order == "INPUT")
		s[lineNumber] = new Input(line, li);
	else if (order == "END")
		s[lineNumber] = new Halt(line, li);
	else if (order == "GOTO")
		s[lineNumber] = new Goto(line, li);
	else if (order == "IF")
		s[lineNumber] = new Judge(line, li);
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
	if (iter == s.end()) return -1;
	iter++;
	return iter->first;
}

void Program::clear() {
  s.clear();
}

void Program::list() {
	for (auto i : s) {
		cout << i.second->origin << endl;
	}
}

void Program::run(EvalState & state) {
	int temp;
	map<int, Statement*>::iterator iter = s.begin();
	while (iter != s.end()) {
		temp = iter->second->execute(state);
		if (temp == -2) iter++;
		else if (temp == -1) break;
		else {
			iter = s.find(temp);
			if (iter == s.end()) error("LINE NUMBER ERROR");
		}
	}
}

bool correctName(string nam) {
	if (nam[0] >= '0' && nam[0] <= '9') return false;
	for (auto i : nam)
		if (!((i >= '0'&& i <= '9') || (i >= 'a' && i <= 'z') ||
			(i >= 'A' && i <= 'Z'))) return false;
	return (!((nam == "RUN") || (nam == "LIST") || (nam == "CLEAR") ||
		(nam == "QUIT") || (nam == "HELP") || (nam == "LET") || (nam == "REM") ||
		(nam == "PRINT") || (nam == "INPUT") || (nam == "END") || (nam == "IF") ||
		(nam == "THEN") || (nam == "GOTO")));
}

bool judgeExp(Expression* exp) {
	if (exp->getType() == CONSTANT) 
		return true;
	if (exp->getType() == IDENTIFIER) 
		return correctName(exp->toString());
	if (exp->getType() == COMPOUND) {
		if (!judgeExp(((CompoundExp *)exp)->getLHS())) return false;
		return judgeExp(((CompoundExp *)exp)->getRHS());
	}
}
