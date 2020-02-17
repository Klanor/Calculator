#include "Header.h"

Calculator::Calculator()
{
	_arguments = new std::vector<float>();
	_operators = new std::vector<char>();
	_queue = new std::vector<float>(10, 0.0);
	_result = 0;
}

void Calculator::_ConvertToFloat(std::string& buf, size_t start, size_t end)
{
	int itmp;
	std::string tmp(buf.begin() + start, buf.begin() + end);

	if (tmp.empty())
		throw std::string("Empty arguments");

	if (tmp.size() == 2 && tmp[0] == '$')
	{
		_arguments->push_back(_queue->at((int)tmp[1] - '0'));
		return;
	}

	for (size_t i = 0; i < tmp.size(); ++i)
	{
		if (tmp[0] == '-'&&tmp.size()!=1)
			continue;

		itmp = (int)tmp[i];
		if (itmp < 48 || itmp > 57)
		{
			if (itmp != 46)
				throw "Uncorrect value (" + tmp + ")";
		}
	}

	_arguments->push_back(std::stof(tmp));
}

void Calculator::_Calculate()
{
	for (size_t i = 0; i < _operators->size(); ++i)
	{
		switch (_operators->at(i))
		{
		case '+':
		{
			if (i == 0) { _result = _arguments->at(0) + _arguments->at(1); }
			else
				_result += _arguments->at(i + 1);
			break;
		}
		case '-':
		{
			if (i == 0) { _result = _arguments->at(0) - _arguments->at(1); }
			else
				_result -= _arguments->at(i + 1);
			break;
		}
		case '*':
		{
			if (i == 0) { _result = _arguments->at(0) * _arguments->at(1); }
			else
				_result *= _arguments->at(i + 1);
			break;
		}
		case '/':
		{
			if (i == 0)
			{
				if (_arguments->at(1) == 0)
					throw std::string("div in 0");
				_result = _arguments->at(0) / _arguments->at(1);
			}
			else
			{
				if (_arguments->at(i + 1) == 0)
					throw std::string("div in 0");
				_result /= _arguments->at(i + 1);
				break;
			}
		}
		}
	}
}

bool Calculator::_FindOperator(std::string& buf, size_t& start)
{
	size_t op[4];

	op[0] = buf.find('-', start);
	op[1] = buf.find('+', start);
	op[2] = buf.find('*', start);
	op[3] = buf.find('/', start);

	if(buf[start]=='-')
		op[0]= buf.find('-', start+1);

	for (int i = 1; i < 4; ++i)
	{
		if (op[0] == op[i] + 1)
		{
			op[0] = buf.find('-', start + 1);
		}
	}

	for (int j = 1; j < 4; ++j)
	{
		if (op[0] > op[j])
		{
			op[0] = op[j];
		}
	}

	if (op[0] > buf.size())
	{
		return false;
	}


	start = op[0] + 1;
	_operators->push_back(buf.at(op[0]));
	return true;
}

void Calculator::Set(std::string buf)
{
	_operators->clear();
	_arguments->clear();

	size_t previus_position = 0;
	size_t position = 0;

	while (_FindOperator(buf, position))
	{
		_ConvertToFloat(buf, previus_position, position - 1);
		previus_position = position;
	}

	_ConvertToFloat(buf, position, buf.size());

	if (_operators->empty())
	{
		_result = _arguments->front();
		return;
	}

	_Calculate();

	_queue->insert(_queue->begin(), _result);
	_queue->pop_back();

	/*for (int i = 0; i < _queue->size(); ++i)
	{
		std::cout << _queue->at(i) << std::endl;
	}*/
}

std::string Calculator::Get() const
{
	std::string res("");
	size_t ss;

	if (_arguments->size() == 1)
	{
		return std::to_string(_result);
	}

	for (size_t i = 0; i < _arguments->size(); ++i)
	{
		res = res + "\n" + std::to_string(_arguments->at(i)) + "\n?";
	}
	res.pop_back();

	for (size_t i = 0; i < _operators->size(); ++i)
	{
		ss = res.find('?');
		res[ss] = _operators->at(i);
	}

	return res + "-----------\n" + std::to_string(_result) + "\n-----------";
}