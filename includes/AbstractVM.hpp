/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayavorsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:14:36 by ayavorsk          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:37 by ayavorsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM
#define ABSTRACT_VM

#include "IOperand.hpp"
#include "Operand.hpp"
#include <string>

class AbstractVM
{
	public:
		AbstractVM();
		virtual ~AbstractVM();
		IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	private :
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;
};
#endif