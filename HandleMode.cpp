/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleMode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:38:15 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/13 10:11:21 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

void Server::handle_mode(std::string argument, int socketfd)
{
	size_t pos = argument.find('#');
	if (pos == std::string::npos)
	{
		std::cout << "invalid format" << std::endl;
		return;
	}
	size_t space = argument.find(' ');
	std::string channel = argument.substr(pos + 1, space);
	if (channel.empty())
	{
		std::cout << "Invalid format (bad channel)\n";
		return;
	}
	std::string arg;
	bool		set_mode;
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
			std::cout << channel << "case 1" << arg << std::endl;
			this->changePerm(channel, set_mode, socketfd);
			break;
		}
		case 1:
		{
			std::cout << channel << "case 2" << arg << std::endl;
			this->permTopic(channel, set_mode, socketfd);
			break;
		}
		case 2:
		{
			std::cout << channel << "case 3" << arg << std::endl;
			this->changePassword(channel, arg, socketfd);
			break;
		}
		case 3:
		{
			std::cout << channel << "case 4" << arg << std::endl;
			this->givePerm(channel, arg, set_mode, socketfd);
			break;
		}
		case 4:
		{
			std::cout << channel << "case 5" << arg << std::endl;
			this->changeLimit(channel, atoi(arg.c_str()), socketfd);
			break;
		}
		default:
		{
			std::cout << channel << "is not a valid argument" << std::endl;
			break;
		}	
	}
}
