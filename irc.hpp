/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:22:10 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/05 14:26:09 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>      // types de base (souvent inclus par d'autres)
#include <sys/socket.h>     // pour socket(), bind(), listen(), accept(), etc.
#include <netinet/in.h>     // pour struct sockaddr_in et constantes AF_INET, htons(), INADDR_ANY
#include <arpa/inet.h> 
#include <cstdlib>
#include <netdb.h>
#include <unistd.h>
#include <netdb.h>
#include <cstdio>
#include <errno.h>
#include <string.h>
#include <poll.h>
#include <vector>
#include <sstream>

class Serveur
{
	private:
	std::string _password;
	int _port;
	
	public:
	Serveur(std::string password, int port);
	~Serveur();
};
