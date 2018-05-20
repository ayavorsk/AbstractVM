/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandExecuter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayavorsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 12:30:07 by ayavorsk          #+#    #+#             */
/*   Updated: 2018/05/18 12:30:08 by ayavorsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_EXECUTER_HPP
# define OPERAND_EXECUTER_HPP
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "IOperand.hpp"
#include "Operand.hpp"
#include "AbstractVM.hpp"
#define LEN_OF_PUSH 4
#define LEN_OF_ASSERT 6
#define NBR_COMMAND 10
#define NBR_TYPE 5
class OperandExecuter
{
	public:
		OperandExecuter();
		OperandExecuter(OperandExecuter const & rhs);
		OperandExecuter const & operator=(OperandExecuter const & rhs);
		virtual ~OperandExecuter();

		void	SetInput_Stream(int argc, char *argv[]);
		void	OperationLexer();
		void 	Check_if_Good_Instruction(std::string const & line);
		bool 	Check_Push_or_Assert(std::string const & line, int pos);
		bool 	check_digit(std::string const & str);
		bool 	check_float(std::string const & str);
		bool	is_comment(std::string const & line);
		void	if_instruction_has_commnet(std::string str);

		void	OperationParser();
		void	add();
		void	sub();
		void	mul();
		void	div();
		void	dump();
		void	pop();
		void	assert(std::string const & str);
		void	push(std::string const & str);
		void	print();
		void	mod();
		void	exit();
		void	pop_2_elements();
		eOperandType findType(std::string const & str);
	private :
		void (OperandExecuter::*operations[9])();
		AbstractVM					Factory;
		std::list<std::string>		lines;
		std::list<IOperand const*>	ops;
		std::istream				*input_;
		bool						fileinput__on_;
		bool						correct_exit_;
};

#endif
