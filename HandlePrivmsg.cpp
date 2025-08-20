/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlePrivmsg.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:48:30 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/20 15:43:05 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

void Server::handle_privmsg(std::string argument, int socketfd, User user)
{
    bool is_channel = false;
    std::string content = "";
    std::string destination;

    if (argument[0] == '#')
        is_channel = true;
    size_t space_pos = argument.find(' ');
    if (space_pos != std::string::npos)
	{
		content = argument.substr(space_pos + 1);
        destination = argument.substr(0, space_pos);
	}
    else
    {
        std::string message = ":" + _servername + " 461 " + user.getNickname() + " MODE :Not enough parameters\r\n";
        send(socketfd, message.c_str(), message.length(), 0);
        return;
    }
    if (content[0] != ':')
    {
        size_t space_pos2 = content.find(' ');
        if (space_pos2 != std::string::npos)
            content = content.substr(0, space_pos2);
    }
    else 
        content = content.substr(1);
    sendMessage(destination, content, is_channel, socketfd);
}