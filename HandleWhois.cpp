/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleWhois.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:26:42 by bfiquet           #+#    #+#             */
/*   Updated: 2025/09/22 10:25:25 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Server.hpp"

void	Server::handle_whois(std::string argument, int socketfd, User &user)
{
	std::string message;
	if (argument.empty())
		message = ":" + _servername + "requester" + user.getUsername() + "user host * :" + user.getUsername() + "Real Name";
	else 
		message = ":" + _servername + "requester" + user.getUsername();
	send(socketfd, message.c_str(), message.length(), 0);
}