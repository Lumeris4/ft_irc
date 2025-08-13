/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleTopic.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:21:36 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/13 10:10:37 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"


void Server::handle_topic(std::string argument, int socketfd)
{
	size_t index = argument.find('#');
	if (index == std::string::npos)
	{
		std::cout << "Invalid format" << std::endl;
		return;
	}
	size_t pos = argument.find(' ');
	std::string channel = argument.substr(1, pos);
	if (channel.empty())
	{
		std::cout << "Invalid format (bad channel)\n";
		return;
	}
	if (pos == std::string::npos)
	{
		std::cout << "Ceci est le topic du channel" << std::endl;
		return;
	}
	std::string newTopic = argument.substr(pos + 1);
	//setTopic(newTopic);
	std::cout << "new topic : " << newTopic << std::endl;
}
