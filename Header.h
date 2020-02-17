#pragma once
#include <string>
#include <iostream>
#include <vector>

class Calculator
{
	std::vector<float>* _arguments;
	std::vector<char>* _operators;
	std::vector<float>* _queue;
	float _result;

	bool _FindOperator(std::string& buf, size_t& start);
	void _ConvertToFloat(std::string& buf, size_t start, size_t end);
	void _Calculate();

public:
	Calculator();

	void Set(std::string buf);

	std::string Get() const;

	~Calculator()
	{
		delete _arguments;
		delete _operators;
		delete _queue;
	}
};