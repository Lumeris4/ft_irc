/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleWhois.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:26:42 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/13 12:31:54 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Server.hpp"

void	Server::handle_whois(std::string argument, int socketfd)
{
	std::string message;
	if (argument.empty())
		message = ":" + _servername + "requester" + _user + "user host * :" + _user + "Real Name";
	else 
		message = ":" + _servername + "requester" + _user;
	send(socketfd, message.c_str(), message.length(), 0);
}