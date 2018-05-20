/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayavorsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:15:15 by ayavorsk          #+#    #+#             */
/*   Updated: 2018/05/12 17:15:15 by ayavorsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"

template<class T> void Operand<T>::add_check(T a, T b) const
{
	if ((a > 0) && (b > 0)){
		if ((a + b) < b)
			throw std::underflow_error("Error : Add underflow error ");
	}
	else if ((a < 0) && (b < 0)){
		if (a < 0 && (a + b) > b)
			throw std::underflow_error("Error : Add underflow error ");
		else if ((a + b) < b)
			throw std::overflow_error("Error : Add overflow error ");
	}
}

template<class T> IOperand const * Operand<T>::operator+( IOperand const & rhs ) const
{
	if(getPrecision() < rhs.getPrecision())
		return (rhs + *this);
	add_check(value_ , static_cast<T>(std::stod(rhs.toString())));
	return new Operand<T>(value_ + (static_cast<T>(std::stod(rhs.toString()))),  getType());
}

template<class T> IOperand const * Operand<T>::operator-( IOperand const & rhs ) const
{
	auto const & res = AbstractVM().createOperand((getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType(),
		std::to_string(value_ - (std::stod(rhs.toString()))));
	return res;
}

template<class T> void mul_check(T a, T b)
{
	if (abs(a) > std::numeric_limits<T>::max()/abs(b)){
		if ((a < 0) && (b < 0))
			throw std::overflow_error("Error : Mul overflow error ");
		else if ((a > 0) && (b > 0))
			throw std::overflow_error("Error : Mul overflow error ");
		else
			throw std::underflow_error("Error : Mul underflow error ");
	}
}

template<class T> IOperand const * Operand<T>::operator*( IOperand const & rhs ) const
{
	if(getPrecision() < rhs.getPrecision())
		return (rhs * *this);
	add_check(value_ , static_cast<T>(std::stod(rhs.toString())));
	auto const & res = AbstractVM().createOperand(getType(), std::to_string(value_ * (static_cast<T>(std::stod(rhs.toString())))));
	return res;
}

template<class T> IOperand const * Operand<T>::operator/( IOperand const & rhs ) const
{
	if ((std::stod(rhs.toString())) == 0)
		throw std::invalid_argument("Error : div by 0");
	auto const & res = AbstractVM().createOperand((getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType(),
		std::to_string(value_ / (static_cast<T>(std::stod(rhs.toString())))));
	return res;
}

template<class T> IOperand const * Operand<T>::operator%( IOperand const & rhs ) const
{
	if ((std::stod(rhs.toString())) == 0)
		throw std::invalid_argument("Error : mod by 0");
	if (rhs.getType() > 2 || getType() > 2)
		throw std::invalid_argument("Error : mod wrong type");
	auto const & res = AbstractVM().createOperand((getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType(),
		std::to_string(static_cast<long>(value_) % (static_cast<long>(std::stod(rhs.toString())))));
	return res;
}

template<class T> std::string const & Operand<T>::toString(void) const
{
	return stringvalue_;
}

template<class T> Operand<T>::Operand(T value, eOperandType type) : value_(value), type_(type)
{
	if (type_ > 2)
	{
		std::ostringstream strs;
		strs << value_;
		stringvalue_ = strs.str();
	}
	else
		stringvalue_ = std::to_string(value_);
}

template<class T> Operand<T>::Operand()
{
}

template<class T> Operand<T>::Operand(Operand<T> const & copy)
{
	value_ = copy.value_; 
	stringvalue_ = copy.stringvalue_;
	type_ = copy.type_;
}

template<class T> IOperand const & Operand<T>::operator=(Operand const & copy)
{
	value_ = copy.value_; 
	stringvalue_ = copy.stringvalue_;
	type_ = copy.type_;
	return (*this);
}

template<class T> Operand<T>::~Operand(){
}

template<class T> int Operand<T>::getPrecision( void ) const
{
	return type_;
}

template<class T> eOperandType Operand<T>::getType( void ) const
{
	return type_;
}


//Template HARD Define
template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
