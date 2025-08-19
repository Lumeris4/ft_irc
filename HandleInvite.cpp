/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleInvite.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:50:42 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/19 10:23:10 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

void Server::handle_invite(std::string argument, int socketfd, User user)
{
	size_t index = argument.find('#');
	if (index == std::string::npos)
	{
		std::string message = ":irc.example.net 461 " + user.getNickname() + " MODE :Not enough parameters\r\n";
        send(socketfd, message.c_str(), message.length(), 0);
        return;
	}
	size_t pos = argument.find(' ');
	std::string user1 = argument.substr(0, pos);
	if (pos == std::string::npos)
	{
        std::string message = ":irc.example.net 461 " + user.getNickname() + " MODE :Not enough parameters\r\n";
        send(socketfd, message.c_str(), message.length(), 0);
        return;
	}
	std::string channel = argument.substr(index);
	if (channel.empty())
	{
		std::string message = ":irc.example.net 403 " + user.getNickname() + " " + argument + " :No such channel\r\n";
        send(socketfd, message.c_str(), message.length(), 0);
        return;
	}
	this->invite(channel ,user1, socketfd);
}
