/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleTopic.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:21:36 by bfiquet           #+#    #+#             */
/*   Updated: 2025/09/22 10:25:21 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"


void Server::handle_topic(std::string argument, int socketfd, User &user)
{
	size_t index = argument.find('#');
	if (index == std::string::npos)
	{
		std::string message = ":" + _servername + " 403 " + user.getNickname() + " " + argument + " :No such channel\r\n";
        send(socketfd, message.c_str(), message.length(), 0);
        return;
	}
	size_t pos = argument.find(' ');
	std::string channel = argument.substr(0, pos);
	if (channel.empty())
	{
		std::string message = ":" + _servername + " 461 " + user.getNickname() + " TOPIC :Not enough parameters\r\n";
        send(socketfd, message.c_str(), message.length(), 0);
        return;
	}
	if (pos == std::string::npos)
	{
		this->changeTopic(channel, "", socketfd);
		return;
	}
	std::string newTopic = argument.substr(pos + 1);
	if (newTopic[0] != ':')
    {
        size_t space_pos2 = newTopic.find(' ');
        if (space_pos2 != std::string::npos)
            newTopic = newTopic.substr(0, space_pos2);
    }
    else 
		newTopic = newTopic.substr(1);
	this->changeTopic(channel, newTopic, socketfd);
}
