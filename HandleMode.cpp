/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleMode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:38:15 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/18 15:52:28 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

void Server::handle_mode(std::string argument, int socketfd, User user)
{
	size_t pos = argument.find('#');
	size_t space = argument.find(' ');
	std::string channel = argument.substr(pos, space);
	if (pos == std::string::npos)
	{
		std::string message = ":irc.example.net 403 " + user.getNickname() + channel + " :No such channel";
		send(socketfd, message.c_str(), message.length(), 0);
		return;
	}
	// size_t space = argument.find(' ');
	// std::string channel = argument.substr(pos, space);
	if (channel.empty())
	{
		std::string message = ":irc.example.net 461 " +  user.getNickname() + argument + " :Not enough parameters";
		send(socketfd, message.c_str(), message.length(), 0);
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
	if (space + 4 < argument.length())
		arg = argument.substr(space + 4);
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
			this->changePerm(channel, set_mode, socketfd);
			break;
		}
		case 1:
		{
			this->permTopic(channel, set_mode, socketfd);
			break;
		}
		case 2:
		{
			if (set_mode == true)
				this->changePassword(channel, arg, socketfd);
			else
				this->changePassword(channel, "", socketfd);
			break;
		}
		case 3:
		{
			this->givePerm(channel, arg, set_mode, socketfd);
			break;
		}
		case 4:
		{
			this->changeLimit(channel, arg , set_mode ,socketfd);
			break;
		}
		default:
		{
			std::string message = "Invalid arguments\n";
			send(socketfd, message.c_str(), message.length(), 0);
			break;
		}	
	}
}
