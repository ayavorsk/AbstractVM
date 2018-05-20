/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayavorsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:14:40 by ayavorsk          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:44 by ayavorsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVM.hpp"

AbstractVM::AbstractVM()
{}

template <typename T>
void				Overflow_Underflow_check(long double nbr)
{
	if (nbr > std::numeric_limits<T>::max())
		throw std::overflow_error("Error : Int overflow error ");
	if (nbr < std::numeric_limits<T>::min())
		throw std::underflow_error("Error : Int underflow error ");
}

IOperand const * AbstractVM::createInt8(std::string const & value ) const
{
	int nbr = std::stoi(value);
	Overflow_Underflow_check<int8_t>(nbr);
	return new Operand<int8_t>(nbr, Int8);
}

IOperand const * AbstractVM::createInt16(std::string const & value ) const
{
	int nbr = std::stoi(value);
	Overflow_Underflow_check<int16_t>(nbr);
	return new Operand<int16_t>(nbr, Int16);
}

IOperand const * AbstractVM::createInt32(std::string const & value ) const
{
	long nbr = std::stoi(value);
	Overflow_Underflow_check<int32_t>(nbr);
	return new Operand<int32_t>(nbr, Int32);
}

IOperand const * AbstractVM::createFloat(std::string const & value ) const
{
	float nbr = std::stof(value);
	return new Operand<float>(nbr, Float);
}

IOperand const * AbstractVM::createDouble(std::string const & value ) const
{
	double nbr = std::stod(value);
	return new Operand<double>(nbr, Double);
}

IOperand const* AbstractVM::createOperand(eOperandType type, std::string const& value) const
{
	static IOperand const * (AbstractVM::*create[5])(std::string const & value) const;
	create[Int8] = &AbstractVM::createInt8;
	create[Int16] = &AbstractVM::createInt16;
	create[Int32] = &AbstractVM::createInt32;
	create[Float] = &AbstractVM::createFloat;
	create[Double] = &AbstractVM::createDouble;
	return ((this->*create[type])(value));
}

AbstractVM::~AbstractVM(){}
