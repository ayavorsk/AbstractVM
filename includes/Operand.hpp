/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayavorsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:15:09 by ayavorsk          #+#    #+#             */
/*   Updated: 2018/05/12 17:15:10 by ayavorsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include "AbstractVM.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

template <class T>
class Operand : public IOperand
{
	public:
		Operand(T value, eOperandType type);
		Operand(Operand const & copy);
		Operand();
		IOperand const & operator=(Operand const & copy);
		virtual ~Operand();
		int getPrecision( void ) const;
		eOperandType getType( void ) const;
		IOperand const * operator+( IOperand const & rhs ) const;
		IOperand const * operator-( IOperand const & rhs ) const;
		IOperand const * operator*( IOperand const & rhs ) const;
		IOperand const * operator/( IOperand const & rhs ) const;
		IOperand const * operator%( IOperand const & rhs ) const;
		std::string const & toString( void ) const;
		void add_check(T a, T b) const;
	private :
		T 			value_;
		std::string stringvalue_;
		eOperandType type_;
};

#endif