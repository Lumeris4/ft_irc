/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleKick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:44:06 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/13 13:00:23 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

void Server::handle_kick(std::string argument, int socket)
{
	std::string reason;
	size_t first_space = argument.find(' ');
	if (first_space == std::string::npos)
	{
		std::cout << "Invalid format (missing space)\n";
		return;
	}
	size_t index = argument.find('#');
	if (index == std::string::npos)
	{
		std::cout << "Invalid channel format" << std::endl;
		return;
	}
	std::string channel = argument.substr(index, first_space);
	if (channel.empty())
	{
		std::cout << "Invalid format (bad channel)\n";
		return;
	}
	std::string rest = argument.substr(first_space + 1);
	size_t second_space = rest.find(' ');
	if (second_space == std::string::npos)
		reason = "";
	else
		reason = rest.substr(second_space + 1);
	std::string user = rest.substr(0, second_space);
	if (!reason.empty() && reason[0] == ':')
		reason = reason.substr(1);
	std::cout << "User " << user << " got kicked from " << channel << " because: " << reason << std::endl;
	kick(channel, user, reason, socket);
}

