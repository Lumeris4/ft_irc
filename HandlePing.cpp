/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlePing.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:51:01 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/19 10:37:00 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

void Server::handle_ping( std::string argument, int socketfd)
{
	std::string message;
	if (argument.empty())
		message = ":" + _servername + " PONG " + _servername + "\r\n";
	else
    {
        if (argument[0] != ':')
            argument = ":" + argument;
        message = ":" + _servername + " PONG " + _servername + " " + argument + "\r\n";
    }
	send (socketfd, message.c_str(), message.length(), 0);
}