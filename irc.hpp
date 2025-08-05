/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:22:10 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/05 10:17:44 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>      // types de base (souvent inclus par d'autres)
#include <sys/socket.h>     // pour socket(), bind(), listen(), accept(), etc.
#include <netinet/in.h>     // pour struct sockaddr_in et constantes AF_INET, htons(), INADDR_ANY
#include <arpa/inet.h> 
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>

class Serveur
{
	private:
	std::string _password;
	int _port;
		
};