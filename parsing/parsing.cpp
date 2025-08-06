/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:10:28 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/06 13:11:24 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

int parsing (char *buf, std::string password)
{
	std::string input = buf;
	std::stringstream ss(input);
	std::string cmds;
	std::string line;
	std::string array[] = {"CAP", "PASS", "NICK", "KICK", "MODE", "TOPIC", "USER", "JOIN", "INVITE"};
	int last_upper;
	int level;

	while (std::getline(ss, cmds, '\n'))
	{
		last_upper = 0;
        line = cmds;
		std::cout << line << std::endl;
		line.erase(line.size() - 1, 1);
		for (int i = 0; isupper(line[i]) && i < (int)line.size(); i++)
			last_upper = i + 1;
		std::string raw_cmd = line.substr(0, last_upper);
		std::string argument = line.substr(last_upper + 1);
		for (size_t i = 0; i < array->length(); i++)
		{
			if (!raw_cmd.compare(array[i]))
				level = i;
		}
		switch (level)
		{
			case 0:
				break;
			case 1:
			{
				if (check_password(argument, password) == -1)
					return (-1);
				break;
			}
			case 2:
			{
				std::cout << "command NICK found" << std::endl;
				break;
			}
			case 3:
			{
				std::cout << "command KICK found" << std::endl;
				break;
			}
			case 4:
			{
				std::cout << "command MODE found" << std::endl;	
			break;
			}
			case 5:
			{
				std::cout <<  "command TOPIC found" << std::endl;
				break;
			}
			case 6:
			{
				std::cout << "command USER found" << std::endl;
				break;
			}
			case 7:
			{
				std::cout << "command JOIN found" << std::endl;
				break;
			}
			case 8:
			{
				std::cout << "command INVITE found" << std::endl;
				break;
			}
			default:
				std::cout << line << " is not a valid command" <<std::endl;
				break;
		}
	}	
	return (0);
}
