/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataBase.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oduwoledare <oduwoledare@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:19:53 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/10 09:29:03 by oduwoledare      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DataBase.hpp"

DataBase::DataBase(){}

DataBase::~DataBase(){}

void	DataBase::pushInBase(std::string env_name)
{
    this->_variablePath.push_back(env_name);
}

void	DataBase::eraseLastSection()
{
    // if(!this->_variablePath.empty())
        this->_variablePath.pop_back();
}

void	DataBase::printVarPath()
{
	std::vector<std::string>::iterator it;
    for(it = _variablePath.begin(); it != _variablePath.end(); it++)
        std::cout << *it << " --> ";
	std::cout << "\n";
}

std::string	DataBase::getFullPathKey()
{
	std::vector<std::string>::iterator it;
	std::string finalKey;

	for(it = _variablePath.begin(); it != _variablePath.end(); it++)
        finalKey += *it + ".";
	return finalKey;
}
