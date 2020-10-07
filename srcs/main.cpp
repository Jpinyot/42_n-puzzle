/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/07 15:38:43 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "state.h" */
#include "stateManhattanDistance.h"
#include "stateLinearConflict.h"
#include "shuffler.h"
#include "algorithms.h"
#include "inputParser.h"
#include <iostream>
#include <map>

static int solve(State *firstState, int (*algo)(State*))
{
	if (firstState->isSolvable()) {
		if (algo(firstState)) {
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
	Algorithms algo = ida;
	Heuristic h = linconf;
	const char *file = "test/hardest3.txt";
	bool translate = false;

	// unsigned char puzzleArr[k_test_size] = {
	// 	5,10,14,7,
	// 	8, 3,6,1,
	// 	15, 0, 12,9,
	// 	2,11,4,13
	// };

	InputParser parser = InputParser(file);
	vector<unsigned char> puzzle;
	if (translate)
		puzzle = parser.getTranslatedPuzzle();
	else
		puzzle = parser.getPuzzle();
	
	State *state;
	int (*algorithm)(State*);

	switch (h) {
		case mandist:
			state = new StateManhattanDistance(puzzle, Moves::none);
			break;
		case linconf:
			state = new StateLinearConflict(puzzle, Moves::none);
			break;
	}

	switch (algo) {
		case a:
			algorithm = astar;
			break;
		case ida:
			algorithm = idastar;
			break;
	}

	solve(state, algorithm);
	return (0);
}
