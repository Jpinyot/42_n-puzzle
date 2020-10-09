/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/09 11:57:14 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "state.h" */
#include "stateManhattanDistance.h"
#include "stateLinearConflict.h"
#include "shuffler.h"
#include "algorithms.h"
#include "inputParser.h"
#include "argparse.h"
#include <iostream>

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
int	main(int ac, char **av)
{
	string error;
	Algorithms algo;
	Heuristic h;
	const char *file;
	bool translate;
	int random;
	
	tie(error, algo, h, file, translate, random) = parse_args(ac, av);

	if (error != "") {
		cout << error;
		return 1;
	}

	vector<unsigned char> puzzle;

	if (file != NULL) {
		InputParser parser = InputParser(file);
		if (translate)
			puzzle = parser.getTranslatedPuzzle();
		else
			puzzle = parser.getPuzzle();
	} else {
		Shuffler shuffler = Shuffler(k_size);
		shuffler.shuffle(random);
		cout << "Starting with random state:\n\n";
		shuffler.display();
		cout << "Shuffled " << random << " times.\n\n";
		puzzle = shuffler.getPuzzle();
	}

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
