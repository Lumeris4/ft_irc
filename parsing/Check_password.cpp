/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Check_password.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:11:00 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/14 10:43:34 by lelanglo         ###   ########.fr       */
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