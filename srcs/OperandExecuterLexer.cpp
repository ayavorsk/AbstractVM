/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandExecuterLexer.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayavorsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 12:30:21 by ayavorsk          #+#    #+#             */
/*   Updated: 2018/05/18 12:30:23 by ayavorsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandExecuter.hpp"

void			 OperandExecuter::OperationLexer()
{
	for (std::string str; std::getline(*(input_), str);){
		if (str == ";;" && !fileinput__on_)
       		break ;
       	try{
       		if (!is_comment(str)){
       			Check_if_Good_Instruction(str);
       			lines.push_back(str);
       		}
       	}
       	catch(std::exception & e){
       		std::cerr << "\x1B[31m" << e.what() << "\x1B[0m" << std::endl;
       	}
    }
}

void	OperandExecuter::Check_if_Good_Instruction(std::string const & line)
{
	static const std::string inst[10] = {"add", "div", "sub", "mul", "mod", "print", "exit",
	"dump", "pop", ";;"};
	for (auto i = 0; i < 10;i++){
		if (line.compare(0, inst[i].size(), inst[i]) == 0){
			if_instruction_has_commnet(&line[inst[i].size()]);
			return ;
		}
	}
	if (line.compare(0, LEN_OF_PUSH, "push") == 0)
		Check_Push_or_Assert(line, LEN_OF_PUSH + 1);
	else if (line.compare(0, LEN_OF_ASSERT, "assert") == 0)
		Check_Push_or_Assert(line, LEN_OF_ASSERT + 1);
	else
		throw std::invalid_argument("Error : Wrong instruction ");
}

bool 	OperandExecuter::Check_Push_or_Assert(std::string const & str, int pos)  // compare
{
	if (   str.compare(pos, 5,"int8(") == 0
		|| str.compare(pos, 6,"int16(") == 0
		|| str.compare(pos, 6,"int32(") == 0){
		check_digit(&str[str.find("(") + 1]);
	}
	else if (str.compare(pos, 6, "float(") == 0 || str.compare(pos, 7, "double(") == 0)
		check_float(&str[str.find("(") + 1]);
	else
		throw std::invalid_argument("Error : Bad argument ");
	return (true);
}

bool	OperandExecuter::is_comment(std::string const & line)
{
	if (!line.empty()){
		if (line[0] == ';')
			return (true);
	}
	return (false);
}

bool 	OperandExecuter::check_float(std::string const & str)
{
	std::string::const_iterator it = str.begin();
	if ((*it) == '-')
		it++;
	int dots = 0;
	while (*it != ')'){
		if ((std::isdigit((*it)) || (*it) == '.') && dots < 2){
			if ((*it) == '.')
				dots++;
			it++;
		}
		else
			throw std::invalid_argument("Error : Bad argument ");
	}
	if_instruction_has_commnet(&(str[str.find(")") + 1]));
	return (true);
}

bool 	OperandExecuter::check_digit(std::string const & str)
{
	std::string::const_iterator it = str.begin();
	if ((*it) == '-')
		it++;
	while (*it != ')'){
		if (std::isdigit((*it)))
			it++;
		else
			throw std::invalid_argument("Error : Bad argument ");
	}
	if_instruction_has_commnet(&(str[str.find(")") + 1]));
	return (true);
}

void	OperandExecuter::if_instruction_has_commnet(std::string str)
{
	for (size_t i = 0; i < str.size(); i++){
		if (str[i] == ';')
			return ;
		else if (str[i] != ' ')
			throw std::invalid_argument("Error : Wrong instruction comment");
	}
}
