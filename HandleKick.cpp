/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleKick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:44:06 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/20 13:19:00 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

void Server::handle_kick(std::string argument, int socket, User user)
{
	std::string reason;
	size_t first_space = argument.find(' ');
	if (first_space == std::string::npos)
	{
		std::string message = ":" + _servername + " 461 " + user.getNickname() + " MODE :Not enough parameters\r\n";
        send(socket, message.c_str(), message.length(), 0);
        return;
	}
	size_t index = argument.find('#');
	if (index == std::string::npos)
	{
		std::string message = ":" + _servername + " 403 " + user.getNickname() + " " + argument + " :No such channel\r\n";
        send(socket, message.c_str(), message.length(), 0);
        return;
	}
	std::string channel = argument.substr(index, first_space);
	if (channel.empty())
	{
		std::string message = ":" + _servername + " 403 " + user.getNickname() + " " + argument + " :No such channel\r\n";
        send(socket, message.c_str(), message.length(), 0);
        return;
	}
	std::string rest = argument.substr(first_space + 1);
	size_t second_space = rest.find(' ');
	if (second_space == std::string::npos)
		reason = "";
	else
		reason = rest.substr(second_space + 1);
	std::string user1 = rest.substr(0, second_space);
	if (!reason.empty() && reason[0] == ':')
		reason = reason.substr(1);
	kick(channel, user1, reason, socket);
}

