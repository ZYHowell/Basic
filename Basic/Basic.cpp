/*
 * File: Basic.cpp
 * ---------------
 * Name: Howell
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
	EvalState state;
	Program program;
	while (true) {
		try {
			processLine(getLine(), program, state);
		}
		catch (ErrorException & ex) {
			string temp = ex.getMessage();
			if ((temp == "DIVIDE BY ZERO") || (temp == "INVALID NUMBER") ||
				(temp == "VARIABLE NOT DEFINED") || (temp == "LINE NUMBER ERROR"))
				cout << temp << endl;
			else cout << "SYNTAX ERROR" << endl;
		}
	}
	return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
	TokenScanner scanner;
	Program tempprogram;
	int ln;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp = scanner.nextToken();
	if (scanner.getTokenType(temp) == NUMBER) {
		ln = stringToInteger(temp);
		try {
			if (!scanner.hasMoreTokens()) {
				program.removeSourceLine(ln);
				return;
			}
			program.addSourceLine(ln, line);
		}
		catch (ErrorException & ex) {
			error(ex.getMessage());
		}
	}
	else {
		if (temp == "RUN")
			program.run(state);
		else if (temp == "LIST")
			program.list();
		else if (temp == "CLEAR") {
			program.clear();
			state.clear();
		}
		else if (temp == "QUIT")
			exit(0);
		else if (temp == "HELP")
			printf("Believe in yourself\n");
		else if ((temp == "LET")|| (temp == "PRINT")|| (temp == "INPUT")) {
			tempprogram.addSourceLine(0, "0 " + line);
			tempprogram.run(state);
			return;
		}
		else error("SYNTAX ERROR2");
	}
}
