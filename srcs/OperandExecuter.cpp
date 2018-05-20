/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandExecuter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayavorsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:03:46 by ayavorsk          #+#    #+#             */
/*   Updated: 2018/05/18 13:03:49 by ayavorsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandExecuter.hpp"

OperandExecuter::OperandExecuter()
{
	operations[0] = &OperandExecuter::pop;
	operations[1] = &OperandExecuter::dump;
	operations[2] = &OperandExecuter::add;
	operations[3] = &OperandExecuter::sub;
	operations[4] = &OperandExecuter::mul;
	operations[5] = &OperandExecuter::div;
	operations[6] = &OperandExecuter::mod;
	operations[7] = &OperandExecuter::print;
	operations[8] = &OperandExecuter::exit;
	fileinput__on_ = false;
	correct_exit_ = false;
}

OperandExecuter::~OperandExecuter()
{
	if (fileinput__on_)
		delete input_;
}

OperandExecuter::OperandExecuter(OperandExecuter const & rhs)
{
	operations[0] = &OperandExecuter::pop;
	operations[1] = &OperandExecuter::dump;
	operations[2] = &OperandExecuter::add;
	operations[3] = &OperandExecuter::sub;
	operations[4] = &OperandExecuter::mul;
	operations[5] = &OperandExecuter::div;
	operations[6] = &OperandExecuter::mod;
	operations[7] = &OperandExecuter::print;
	operations[8] = &OperandExecuter::exit;
	fileinput__on_ = false;
	correct_exit_ = false;
	lines = rhs.lines;
	ops = rhs.ops;
	input_ = rhs.input_;
}

OperandExecuter const & OperandExecuter::operator=(OperandExecuter const & rhs)
{
	operations[0] = &OperandExecuter::pop;
	operations[1] = &OperandExecuter::dump;
	operations[2] = &OperandExecuter::add;
	operations[3] = &OperandExecuter::sub;
	operations[4] = &OperandExecuter::mul;
	operations[5] = &OperandExecuter::div;
	operations[6] = &OperandExecuter::mod;
	operations[7] = &OperandExecuter::print;
	operations[8] = &OperandExecuter::exit;
	fileinput__on_ = false;
	correct_exit_ = false;
	lines = rhs.lines;
	ops = rhs.ops;
	input_ = rhs.input_;
	return (*this);
}

void	OperandExecuter::SetInput_Stream(int argc, char *argv[])
{	
	if (argc > 2)
		throw std::invalid_argument("Error : More then 2 argument ");
	if (argc == 2)
	{
		fileinput__on_ = true;
		input_ = static_cast<std::istream*>(new std::ifstream(argv[1]));
	}
	else
	{
		fileinput__on_ = false;
		input_ = &std::cin;
	}
}
