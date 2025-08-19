/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleMode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:38:15 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/19 10:39:30 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

void Server::handle_mode(std::string argument, int socketfd, User user)
{
	size_t space = argument.find(' ');
	if (space == std::string::npos || space + 1 >= argument.length())
    {
        std::string message = ":irc.example.net 461 " + user.getNickname() + " MODE :Not enough parameters\r\n";
        send(socketfd, message.c_str(), message.length(), 0);
        return;
    }
	std::string channel = argument.substr(0, space);
    if (channel.empty() || channel[0] != '#')
    {
        std::string message = ":irc.example.net 403 " + user.getNickname() + " " + argument + " :No such channel\r\n";
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
		std::string message = ":irc.example.net 472 " + user.getNickname() + " " + mode_char + " :is unknown flag\r\n";
		send(socketfd, message.c_str(), message.length(), 0);
		return ;
	}
	if (space + 4 < argument.length())
		arg = argument.substr(space + 4);
	else
		arg = "";
	int level = -1;
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
				this->changePassword(channel, arg, set_mode ,socketfd);
			else
				this->changePassword(channel, "", set_mode, socketfd);
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
			std::string message = ":irc.example.net 472 " + user.getNickname() + " " + mode_option + " :is unknown mode char\r\n";
			send(socketfd, message.c_str(), message.length(), 0);
			break;
		}	
	}
}
