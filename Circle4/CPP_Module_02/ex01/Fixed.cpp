#include <iostream>
#include "Fixed.hpp"

Fixed::Fixed	( void )
{
	std::cout << "Default constructor called" << std::endl;
	this->setRawBits(0);
}

Fixed::Fixed	( const Fixed &fixed_point_number )
{
	std::cout << "Copy constructor called" << std::endl;
	*this = fixed_point_number;
}


Fixed::Fixed	( const int int_value )
{
	std::cout << "Int constructor called" << std::endl;
	this->setRawBits(int_value * (1 << Fixed::_fractional_bit));
}

Fixed::Fixed	( const float float_value )
{
	std::cout << "Float constructor called" << std::endl;
	this->setRawBits(float_value * (1 << Fixed::_fractional_bit));
}

Fixed & Fixed::operator = ( const Fixed &fixed_point_number )
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->setRawBits(fixed_point_number.getRawBits());
	return (*this);
}

std::ostream & operator << (std::ostream & output_stream, const Fixed & fixed_point_number)
{
	float	float_value = fixed_point_number.toFloat();
	int		int_value = fixed_point_number.toInt();

	if (float_value == (float)int_value)
		output_stream << int_value;
	else
		output_stream << float_value;
	return (output_stream);
}

Fixed::~Fixed	( void )
{
	std::cout << "Destructor called" << std::endl;
}

int		Fixed::getRawBits ( void ) const
{
	// std::cout << "getRawBits member function called" << std::endl;
	return (this->_value);
}

void	Fixed::setRawBits ( int const raw )
{
	// std::cout << "setRawBits member function called" << std::endl;
	this->_value = raw;
}

float	Fixed::toFloat ( void ) const
{
	return ((float)(this->_value) / (float)(1 << Fixed::_fractional_bit));
}

int		Fixed::toInt ( void ) const
{
	return ((this->_value) >> Fixed::_fractional_bit);
}