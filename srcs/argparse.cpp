/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:02:53 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/09 11:55:51 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argparse.h"

// using namespace std;

const int TYPE_HELP = 00;
const int TYPE_MAP = 01;
const int TYPE_ALGO = 010;
const int TYPE_HEURISTIC = 0100;
const int TYPE_SHUFFLE = 01000;
const int TYPE_TRANSLATE = 010000;


map<string, Algorithms> algorithms {
	{"--idastar", ida},
	{"-ida", ida},
	{"--astar", a},
	{"-a", a}
};

map<string, Heuristic> heuristics {
	{"--mandist", mandist},
	{"--linconf", linconf}
};

map<string, int> skips {
	{"--help", TYPE_HELP},
	{"-h", TYPE_HELP},
	{"--idastar", TYPE_ALGO},
	{"-ida", TYPE_ALGO},
	{"--astar", TYPE_ALGO},
	{"-a", TYPE_ALGO},
	{"--shuffle", TYPE_SHUFFLE},
	{"--notranslate", TYPE_TRANSLATE},
	{"--mandist", TYPE_HEURISTIC},
	{"--linconf", TYPE_HEURISTIC}
};

tuple<string, Algorithms, Heuristic, char*, bool, int>    parse_args(int ac, char **av) {
	int argsSet = 00;

	string error = "";
	Algorithms algo = ida;
	Heuristic h = linconf;
	char *file = NULL;
	bool translate = true;
	int random = 50;

	for (int i = 1; i < ac; i++) {
		auto arg = skips.find(string(av[i]));
		if (arg != skips.end()) {
			if ((argsSet & arg->second) == arg->second) {
				error =  "ERROR - Argument \"" + arg->first + "\" already has been represented.\n"; // or return error
				if (arg->second == TYPE_HELP) {
					error = "help\n";
				}
				break;
			}
			argsSet |= arg->second;
			switch (arg->second)
			{
				case TYPE_ALGO:
					algo = algorithms.find(arg->first)->second;
					break;

				case TYPE_HEURISTIC:
					h = heuristics.find(arg->first)->second;
					break;

				case TYPE_SHUFFLE:
					break; //TODO deal with this

				case TYPE_TRANSLATE:
					translate = false;
					break;

				default:
					break;
			}
		} else {
			ifstream f(av[i]);
			if (f.good()) {
				if ((argsSet & TYPE_MAP) == TYPE_MAP) {
					error = "ERROR - Argument path already has been represented.\n"; // or return error
					break;
				}
				argsSet |= TYPE_MAP;
				file = av[i];
			} else {
				error = "ERROR - Extraneous member \"" + string(av[i]) + "\" in input.\n";
			}
		}
	}
	return make_tuple(error, algo, h, file, translate, random);
}