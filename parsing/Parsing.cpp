/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:10:28 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/07 13:32:28 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"

bool connected = false;

int Server::parsing (char *buf, std::string password)
{
	std::string input = buf;
	std::stringstream ss(input);
	std::string cmds;
	std::string line;
	std::string argument;
	std::string array[] = {"CAP", "PASS", "NICK", "KICK", "MODE", "TOPIC", "USER", "JOIN", "INVITE"};
	int			size = sizeof(array) / sizeof(array[0]);
	int			last_upper;
	int			level = -1;

	while (std::getline(ss, cmds, '\n'))
	{
		last_upper = 0;
        line = cmds;
		if (line[line.size() - 1] == '\n' || line[line.size() - 1] == '\r')
			line.erase(line.size() - 1, 1);
		for (int i = 0; isupper(line[i]) && i < (int)line.size(); i++)
			last_upper = i + 1;
		std::string raw_cmd = line.substr(0, last_upper);
		if (last_upper < (int)line.length())
			argument = line.substr(last_upper + 1);
		else
			argument = "";
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
					else if (check_password(argument, password) == -1)
						return (-1);
					connected = true;
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
		level = 0;
	}
	return (0);
}
