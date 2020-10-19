/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/19 09:10:52 by mfiguera         ###   ########.fr       */
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

int k_size = 0;
unsigned char k_itValue = 0;
bool k_translate = false;

static int solve(State *firstState, int (*algo)(State*, bool), bool display)
{
	if (firstState->isSolvable()) {
		if (algo(firstState, display)) {
			return 1;
		}
	}
	firstState->display();
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
	bool display;
	
	srand(time(NULL));
	int shuffleIter = rand() % 50 + 20;
	
	tie(error, algo, h, file, k_translate, k_size, display) = parse_args(ac, av);

	if (error != "") {
		cout << error;
		return 1;
	}

	vector<unsigned char> puzzle;

	if (file != NULL) {
		InputParser parser = InputParser(file);
		k_size = parser.getSize();
		k_itValue = (floor(k_size * k_size / 2) + (k_size - 1) % 2 * 1) * k_translate;
		if (k_translate)
			puzzle = parser.getTranslatedPuzzle();
		else
			puzzle = parser.getPuzzle();
	} else {
		k_itValue = (floor(k_size * k_size / 2) + (k_size - 1) % 2 * 1) * k_translate;
		Shuffler shuffler = Shuffler(k_size);
		shuffler.shuffle(shuffleIter);
		puzzle = shuffler.getPuzzle();
	}

	State *state;
	int (*algorithm)(State*, bool);

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
		case greedy:
			algorithm = greedyastar;
			break;
	}

	solve(state, algorithm, display);
	return (0);
}
