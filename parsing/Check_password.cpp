/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Check_password.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:11:00 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/07 10:45:38 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.hpp"

int Parsing::check_password(std::string password)
{
	if (password.compare(_serverPassword) != 0)
		return (-1);
	setConnected(true);
	std::cout << "Client has entered password. Accessing server" << std::endl;
	return (0);
}