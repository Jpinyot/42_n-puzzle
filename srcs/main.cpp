/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/07 11:10:35 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "state.h" */
#include "stateManhattanDistance.h"
#include "stateLinearConflict.h"
#include "shuffler.h"
#include "algorithms.h"
#include <iostream>
#include <map>

static int solve(State *firstState)
{
	if (firstState->isSolvable()) {
		if (astar(firstState)) {
			return 1;
		}
	}
	cout << "Total opened states: " << State::getStatesCreated() << ".\n";
	cout << "Not solvable puzzle.\n";
	return 1;
}

const int k_test_size = k_size * k_size;
int	main()
{
	unsigned char puzzleArr[k_test_size] = {	7,5,6,
												1,4,3,
												2,8,0};


	// unsigned char puzzleHard[k_test_size] = {
	// 	0,12,7,1,
	// 	14,10,15,5,
	// 	2,6,11,9,
	// 	3,4,8,13,
	// };

	vector<unsigned char> puzzle;
	for (int i = 0; i < k_test_size ; i++) {
		puzzle.emplace_back(puzzleArr[i]);
	}
	Shuffler *shuffler = new Shuffler(3);
	shuffler->shuffle(30);
	shuffler->display();
	cout << "aqui\n";
	puzzle = shuffler->getPuzzle();
	delete shuffler;
	cout << "la\n";
	State * state = new StateLinearConflict(puzzle, none);
	cout << "lala\n";
	solve(state);
	// shuffler.display();
	return (0);
}
