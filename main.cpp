/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:10:27 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/07 12:19:02 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
#include "parsing/Parsing.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Please respect this format: './ircserv <port> <password>" << std::endl;
		return -1;
	}
	Server server = Server(argv[2], atoi(argv[1]));
	server.init_server();
	return 0;
}

