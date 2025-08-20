/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleUser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:51:14 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/20 15:44:08 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

int Server::setUser(std::string name, int socket, User &user)
{
	std::istringstream iss(name);
	std::vector<std::string> parts;
	std::string part;
	while (iss >> part)
		parts.push_back(part);
	if (parts.size() < 4)
	{
		std::string message = ":" + _servername + " 461 * USER :Not enough parameters\r\n";
		send(socket, message.c_str(), message.length(), 0);
		return -1;
	}
	std::string username = parts[0];
	std::string nickname = user.getNickname().empty() ? username + "_" : user.getNickname();
	std::string hostname = parts[1];
	if (!user.getUsername().empty())
	{
		std::string message = ":" + _servername + " 462 " + nickname + " :You may not reregister\r\n";
		send(socket, message.c_str(), message.length(), 0);
		return -1;
	}
	user.setUsername(username);
	std::string message = ":" + _servername + " 001 " + nickname + " :Welcome to the Internet Relay Network " + nickname + "!" + user.getUsername() + "@" + hostname + "\r\n";
	send(socket, message.c_str(), message.length(), 0);
	return (0);
}