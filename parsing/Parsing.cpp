/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:10:28 by bfiquet           #+#    #+#             */
/*   Updated: 2025/09/09 15:36:20 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"

int Server::parsing(std::string input, User &user)
{
	std::string argument;
	std::string array[] = {"CAP", "PASS", "NICK", "USER", "MODE", "TOPIC", "INVITE", "KICK", "JOIN", "PRIVMSG", "PING", "WHOIS", "QUIT"};
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
	if (level > 1 && !user.getConnected())
	{
		level = 0;
		std::string message = "You have to enter the password first\n";
		send(user.getSocket(), message.c_str(), message.length(), 0);
	}
	else
	{
		switch (level)
		{
			case 0:
				break;
			case 1:
			{
				if (user.getConnected())
				{
					std::string message = "Client has already entered the password\n";
					send(user.getSocket(), message.c_str(), message.length(), 0);
				}
				else if (check_password(_argument) == -1)
				{
					std::string message = "Client has entered wrong password\n";
					send(user.getSocket(), message.c_str(), message.length(), 0);
					return (-1);
				}
				user.setConnected(true);
				return (0);
			}
			case 2:
				return (1);
			case 3:
				return (2);
			case 4:
				return (3);
			case 5:
				return (4);
			case 6:
				return (5);
			case 7: 
				return (6);
			case 8:
				return (7);
			case 9:
				return (8);
			case 10:
				return (9);
			case 11:
				return (10);
			case 12:
				return(11);
			default:
			{
				if (input.empty())
					return (-1);
				std::string message = input + " is not a valid command\n";
				send(user.getSocket(), message.c_str(), message.length(), 0);
				return (-1);
			}
		}
	}
	return 0;
}
