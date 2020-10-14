/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/14 11:26:43 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "state.h" */
#include "stateManhattanDistance.h"
#include "stateLinearConflict.h"
#include "stateUniformCost.h"
#include "shuffler.h"
#include "algorithms.h"
#include "inputParser.h"
#include "argparse.h"
#include <iostream>
#include <time.h>

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

int	main(int ac, char **av)
{
	string error;
	Algorithms algo;
	Heuristic h;
	const char *file;
	bool translate;
	int size;
	
	srand(time(NULL));
	int shuffleIter = rand() % 50 + 20;
	
	tie(error, algo, h, file, translate, size) = parse_args(ac, av);

	if (error != "") {
		cout << error;
		return 1;
	}

	vector<unsigned char> puzzle;

	if (file != NULL) {
		InputParser parser = InputParser(file);
		size = parser.getSize();
		if (translate)
			puzzle = parser.getTranslatedPuzzle();
		else
			puzzle = parser.getPuzzle();
	} else {
		Shuffler shuffler = Shuffler(size);
		shuffler.shuffle(shuffleIter);
		cout << "Starting with random state:\n\n";
		shuffler.display();
		cout << "Shuffled " << shuffleIter << " times.\n\n";
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
		case unicost:
			state = new StateUniformCost(puzzle, Moves::none);
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
