/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:21:08 by mbarberi          #+#    #+#             */
/*   Updated: 2023/08/22 12:59:55 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>
#include <string>

Bureaucrat::Bureaucrat()
    : _name( "Default" )
    , _grade( LOWEST_GRADE ) {
}

Bureaucrat::Bureaucrat( std::string name, int grade )
    : _name( name ) {
    if ( grade < HIGHEST_GRADE )
        throw Bureaucrat::GradeTooHighException();
    else if ( grade > LOWEST_GRADE )
        throw Bureaucrat::GradeTooLowException();
    this->_grade = grade;
}

Bureaucrat::Bureaucrat( Bureaucrat const & o )
    : _name( o._name + "_copy" )
    , _grade( o._grade ) {
}

Bureaucrat::~Bureaucrat() {
}

Bureaucrat & Bureaucrat::operator=( Bureaucrat const & o ) {
    this->_grade = o._grade;
    return *this;
}

std::string const & Bureaucrat::getName() const {
    return this->_name;
}

int Bureaucrat::getGrade() const {
    return this->_grade;
}

void Bureaucrat::promote() {
    if ( this->_grade == HIGHEST_GRADE )
        throw Bureaucrat::GradeTooHighException();
    this->_grade--;
}

void Bureaucrat::demote() {
    if ( this->_grade == LOWEST_GRADE )
        throw Bureaucrat::GradeTooLowException();
    this->_grade++;
}

void Bureaucrat::signForm( Form & f ) const {
    if ( f.getSigned() ) {
        std::cout << f.getName() << " has already been signed.\n";
        return;
    }
    try {
        f.beSigned( *this );
        std::cout << this->_name << " signed " << f.getName() << ".\n";
    } catch ( Form::GradeTooLowException & e ) {
        std::cout << this->_name << " couldn't sign " << f.getName() << " because the lowest grade to sign is " << f.getSignGrade() << ".\n";
    }
}

char const * Bureaucrat::GradeTooHighException::what() const throw() {
    return ( "Cannot promote since hightest grade is 1.\n" );
}

char const * Bureaucrat::GradeTooLowException::what() const throw() {
    return ( "Cannot demote since lowest grade is 150.\n" );
}

std::ostream & operator<<( std::ostream & o, const Bureaucrat & b ) {
    o << b.getName() << ", bureaucrat grade " << b.getGrade() << ".\n";
    return o;
}
