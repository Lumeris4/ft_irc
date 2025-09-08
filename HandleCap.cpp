/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:35:51 by bfiquet           #+#    #+#             */
/*   Updated: 2025/09/08 15:26:34 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

void Server::handle_cap(const std::string& arg, User& user, int socketfd)
{
    std::istringstream iss(arg);
    std::string subcmd;
    iss >> subcmd;

    if (subcmd == "LS")
    {
        std::string reply = "CAP * LS :\r\n";
        send(socketfd, reply.c_str(), reply.size(), 0);
    }
    else if (subcmd == "REQ")
    {
        std::string reply = "CAP * NAK :" + arg.substr(4) + "\r\n";
        send(socketfd, reply.c_str(), reply.size(), 0);
    }
    else if (subcmd == "END")
    {
        user.setCap(true);
        std::cout << "Client" << " finished CAP negotiation" << std::endl;
    }
}
