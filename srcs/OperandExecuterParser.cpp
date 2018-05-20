/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandExecuterParser.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayavorsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 12:31:30 by ayavorsk          #+#    #+#             */
/*   Updated: 2018/05/18 12:31:31 by ayavorsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandExecuter.hpp"

void	OperandExecuter::OperationParser()
{
	std::string command[] = {"pop", "dump", "add",
		"sub", "mul", "div", "mod", "print", "exit"};
	for(auto const & it : lines){
		try{
			for (int i = 0; i < NBR_COMMAND;i++){
				if (it.find(command[i]) != std::string::npos)
					(this->*operations[i])();
			}
			if (it.find("push", 0) != std::string::npos)
				push(it);
			else if (it.find("assert") != std::string::npos)
				assert(it);
		}
		catch(std::exception &e){
			std::cerr << "\x1B[31m" << e.what() << "\x1B[0m"<< std::endl;
		}
		if (correct_exit_ == true)
			break ;
	}
	if (correct_exit_ == false)
		throw std::invalid_argument("Error : No Exit instruction");
}

void	OperandExecuter::pop()
{
	if (ops.empty())
		throw std::invalid_argument("Error : Pop empty stack");
	delete *ops.begin();
	ops.pop_front();
}

eOperandType		OperandExecuter::findType(std::string const & str)
{
	static std::string type_arr[] = {"int8", "int16", "int32", "float", "double"};
	for(int i = 0; i < NBR_TYPE;i++)
		if (str.find(type_arr[i], 5) != std::string::npos)
			return static_cast<eOperandType>(i);
	return Int8;
}

void	OperandExecuter::push(std::string const & str)
{
	if (str.find("push", 0, 4) != std::string::npos)
		ops.push_front(Factory.createOperand(findType(str), &str[str.find("(") + 1]));
}

void	OperandExecuter::pop_2_elements()
{
	if (ops.size() < 2)
		throw std::invalid_argument("Error : Stack size less then 2");
	delete *ops.begin();
	ops.pop_front();
	delete *ops.begin();
	ops.pop_front();
}

void	OperandExecuter::add()
{
	if (ops.size() < 2)
		throw std::invalid_argument("Error : Stack size less then 2");
	std::list<IOperand const*>::iterator it = ops.begin();
	auto const *res = (*(*++it) + *(*(--it)));
	pop_2_elements();
	ops.push_front(res);
}

void	OperandExecuter::exit()
{
	if (!ops.empty()){
		while (!ops.empty()){
			delete *ops.begin();
			ops.pop_front();
		}
	}
	correct_exit_ = true;
}

void	OperandExecuter::mod()
{
	if (ops.size() < 2)
		throw std::invalid_argument("Error : Stack size less then 2");
	std::list<IOperand const*>::iterator it = ops.begin();
	auto const *res = (*(*++it) % *(*(--it)));
	pop_2_elements();
	ops.push_front(res);
}

void	OperandExecuter::assert(std::string const & str)
{
	if (ops.empty())
		throw std::invalid_argument("Error : Empty Stack");
	if ((*ops.begin())->getType() != findType(str))
		throw std::invalid_argument("Error : Assert different type ");
	if (std::stod((*ops.begin())->toString()) != std::stod(&str[str.find("(") + 1]))
		throw std::invalid_argument("Error : Assert different value ");
}

void	OperandExecuter::sub()
{
	if (ops.size() < 2)
		throw std::invalid_argument("Error : Stack size less then 2");
	std::list<IOperand const*>::iterator it = ops.begin();
	auto const *res = (*(*++it) - *(*(--it)));
	pop_2_elements();
	ops.push_front(res);
}

void	OperandExecuter::mul()
{
	if (ops.size() < 2)
		throw std::invalid_argument("Error : Stack size less then 2");
	std::list<IOperand const*>::iterator it = ops.begin();
	auto const *res = (*(*++it) * *(*(--it)));
	pop_2_elements();
	ops.push_front(res);
}

void	OperandExecuter::div()
{
	if (ops.size() < 2)
		throw std::invalid_argument("Error : Stack size less then 2");
	std::list<IOperand const*>::iterator it = ops.begin();
	auto const *res = (*(*++it) / *(*(--it)));
	pop_2_elements();
	ops.push_front(res);
}

void	OperandExecuter::dump()
{
	if (ops.empty())
		return ;
	for(auto const & it : ops){
		if (!(*it).toString().empty())
			std::cout << (*it).toString() << std::endl;
	}
}

void	OperandExecuter::print()
{
	if (ops.empty())
		throw std::invalid_argument("Error : Print empty stack");
	if ((*ops.begin())->getType() != Int8)
		throw std::invalid_argument("Error : Print different type");
	std::cout << static_cast<char>(std::stoi((*ops.begin())->toString()));
}
