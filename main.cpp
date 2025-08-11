/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:10:27 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/11 10:10:44 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Please respect this format: './ircserv <port> <password>" << std::endl;
		return -1;
	}
	Server server = Server(argv[2], atoi(argv[1]));
	server.init_server();
	return 1;
}

//TODO refaire parsing en fonction du nombre de lignes pour le client
// retourner des codes en fonction de la commande appelee puis reparser pour detecter d'eventuelles options

//attendre que le user ait entre PASS, NICK et USER puis lui creer un socket et le bind au serveur

//mod -i -t -k -o -l