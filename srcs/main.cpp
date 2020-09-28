/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/09/28 17:41:13 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "state.h" */
#include "stateManhattanDistance.h"
#include <iostream>

int	main()
{
	vector<char> puzzle;
	puzzle.push_back(0);
	puzzle.push_back(1);
	puzzle.push_back(2);
	puzzle.push_back(3);
	puzzle.push_back(4);
	puzzle.push_back(5);
	puzzle.push_back(6);
	puzzle.push_back(7);
	puzzle.push_back(8);
	StateManhattanDistance state(puzzle);
	cout << state.getScore();
	return (0);
}
