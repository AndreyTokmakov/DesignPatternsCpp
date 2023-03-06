//============================================================================
// Name        : Interpreter.cpp
// Created on  : October 23, 2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Interpreter pattern test
//============================================================================

#include "Interpreter.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <initializer_list>  // std::initializer_list


// IExpression interface used to check the interpreter. 
class IExpression {
public:
	[[nodiscard]]
    virtual bool interpret(const std::string& condition) const noexcept = 0;
};

// Expression class implementing the above interface. 
// This interpreter just check if the data is same as the interpreter data. 
class Expression : public IExpression {
private:
	std::string str;

public:
	explicit Expression(std::string data): str(std::move(data)){
	}

	[[nodiscard]]
    bool interpret(const std::string& condition) const noexcept override {
		return std::string::npos != condition.find(this->str);
	}
};

// ComplexExpression class implementing the above interface. 
// This interpreter just check if the data is same as the interpreter data. 
class ComplexExpression : public IExpression {
protected:
	std::vector<std::shared_ptr<IExpression>> exprList;

public:
	ComplexExpression(const std::initializer_list<std::shared_ptr<IExpression>>& il) {
		exprList.assign(il);
	}

	void addExpression(const std::shared_ptr<IExpression>& expr) {
		exprList.push_back(expr);
	}

	[[nodiscard]]
    bool interpret(const std::string& condition) const noexcept override = 0;
};

// OrExpression class implementing the above interface. This interpreter just
// returns the or condition of the data is same as the interpreter data. 
class OrExpression: public ComplexExpression {
public:
	OrExpression(const std::initializer_list<std::shared_ptr<IExpression>>& il): 
		ComplexExpression(il){
	}

	[[nodiscard]]
    bool interpret(const std::string& condition) const noexcept override {
		return std::any_of(exprList.begin(), exprList.end(), [&condition](const auto& expr) {
			return expr->interpret(condition);
		});
	}
};

// OrExpression class implementing the above interface. This interpreter just
// returns the or condition of the data is same as the interpreter data. 
class AndExpression : public ComplexExpression {
public:
	AndExpression(const std::initializer_list<std::shared_ptr<IExpression>>& il) :
		ComplexExpression(il) {
	}

	[[nodiscard]]
    bool interpret(const std::string& condition) const noexcept override {
		return std::all_of(exprList.begin(), exprList.end(), [&condition](const auto& expr) {
			return expr->interpret(condition);
		});
	}
};

namespace Interpreter
{
	void Test() {
		auto expr1 = std::make_shared<Expression>("AAA");
		auto expr2 = std::make_shared<Expression>("BBB");

		OrExpression orExpr({ expr1 , expr2 });
		AndExpression andExpr({ expr1 , expr2 });

		std::cout << std::boolalpha << orExpr.interpret("AAABBCCDD") << std::endl;  // true
		std::cout << std::boolalpha << andExpr.interpret("AAABBCCDD") << std::endl; // false
	}
};

