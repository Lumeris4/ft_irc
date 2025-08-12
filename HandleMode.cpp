/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleMode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:38:15 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/12 11:30:31 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

void handle_mode(std::string argument, bool is_user)
{
	if (is_user == false)
		return ;
	std::cout << argument << std::endl;
	size_t pos = argument.find('#');
	std::string channel = argument.substr(0, pos);
	std::string arg;
	bool		set_mode;
	size_t space = argument.find(' ');
	char mode_char = argument[space + 1];
	char mode_option = argument[space + 2];
	if (mode_char == '-')
		set_mode = false;
	else if (mode_char == '+')
		set_mode = true;
	else 
	{
		std::cout << "invalid format" << std::endl;
		return ;
	}
	if (space + 3 < argument.length())
		arg = argument.substr(space + 3);
	else
		arg = "";
	int level = -1;
	std::cout << mode_option << std::endl;
	std::string array[] = {"i", "t", "k", "o", "l"};
	for (int j = 0; j < 5; j++)
	{
		if (mode_option == array[j][0])
		{
			level = j;
			break;
		}
	}
	switch (level)
	{
		case 0:
		{
			std::cout << "case 1" << arg << std::endl;
			break;
		}
		case 1:
		{
			std::cout << "case 2" << arg << std::endl;
			break;
		}
		case 2:
		{
			std::cout << "case 3" << arg << std::endl;
			break;
		}
		case 3:
		{
			std::cout << "case 4" << arg << std::endl;
			break;
		}
		case 4:
		{
			std::cout << "case 5" << arg << std::endl;
			break;
		}
		default:
		{
			std::cout << "is not a valid argument" << std::endl;
			break;
		}	
	}
}
