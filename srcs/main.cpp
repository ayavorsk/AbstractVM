/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayavorsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 16:56:56 by ayavorsk          #+#    #+#             */
/*   Updated: 2018/05/12 16:56:58 by ayavorsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandExecuter.hpp"
#include "IOperand.hpp"
#include "Operand.hpp" 

int	 main(int argc, char *argv[])
{
	OperandExecuter vm;

	try{
		vm.SetInput_Stream(argc, argv);
		vm.OperationLexer();
		vm.OperationParser();
	}
	catch (std::exception &e){
		std::cerr << "\x1B[31m" << e.what() << "\x1B[0m"<< std::endl;
	}
	return (0);
}
