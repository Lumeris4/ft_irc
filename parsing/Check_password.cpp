/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Check_password.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:11:00 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/11 09:51:04 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"

int Server::check_password(std::string password)
{
	if (password.compare(_password) != 0)
		return (-1);
	std::cout << "Client has entered password. Accessing server" << std::endl;
	return (0);
}