/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataBase.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:16:08 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/10 14:51:38 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATABASE_H
# define DATABASE_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <cctype>

class DataBase{
	public: 
		DataBase();
		~DataBase();
		void		pushInBase(std::string env_name);
		void		eraseLastSection();
		void		printVarPath();
		std::string	getFullPathKey();
		std::string getKeyWithoutLastSection();
	private:
		std::vector<std::string> _variablePath;
};


#endif
