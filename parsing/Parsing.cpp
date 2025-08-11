/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:10:28 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/11 14:15:07 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"

bool connected = false;

int Server::parsing (std::string input)
{
	std::string argument;
	std::string array[] = {"CAP", "PASS", "NICK", "USER"};
	int			size = sizeof(array) / sizeof(array[0]);
	int			last_upper;
	int			level = -1;
	
	last_upper = 0;
	if (input[input.size() - 1] == '\n' || input[input.size() - 1] == '\r')
		input.erase(input.size() - 1, 1);
	for (int i = 0; isupper(input[i]) && i < (int)input.size(); i++)
		last_upper = i + 1;
	std::string raw_cmd = input.substr(0, last_upper);
	if (last_upper < (int)input.length())
		_argument = input.substr(last_upper + 1);
	else
		_argument = "";
	for (int i = 0; i < size; i++)
	{
		if (!raw_cmd.compare(array[i]))
			level = i;
	}
	if (level > 1 && connected == false)
		std::cout << "you have to enter the password first" << std::endl;
	else
	{
		switch (level)
		{
			case 0:
				break;
			case 1:
			{
				if (connected == true)
					std::cout << "Client has already entered the password" << std::endl;
				else if (check_password(_argument) == -1)
				{
					std::cout << "client has entered wrong password" << std::endl;
					return (-1);
				}
				connected = true;
				return (0);
			}
			case 2:
			{
				std::cout << "command NICK found" << std::endl;
				return (1);
			}
			case 3:
			{
				std::cout << "command USER found" << std::endl;
				return (2);
			}
			default:
				std::cout << input << " is not a valid command" <<std::endl;
				return (0);
		}
	}
	return (0);
}
