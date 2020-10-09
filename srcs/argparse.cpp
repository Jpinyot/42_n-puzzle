/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:02:53 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/09 16:41:18 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argparse.h"

// using namespace std;

const int TYPE_HELP = 00;
const int TYPE_MAP = 01;
const int TYPE_ALGO = 010;
const int TYPE_HEURISTIC = 0100;
const int TYPE_SIZE = 01000;
const int TYPE_TRANSLATE = 010000;


string help =
"\
n-puzzle [PUZZLE] [args]\n\
\n\
Args:\n\
	PUZZLE		path to map file. If not provided map is randomly generated\n\
	-s, --size S	size of the generated map -- Default=3\n\
	-h, --help	display help and exit\n\
	-a, --astar	solve using A* algorithm\n\
	-ida, --idastar	solve using IDA* algorithm -- Default\n\
	--notranslate	map is not curled\n\
	--mandist	solve using Manhattan Distance heuristic\n\
	--linconf	solve using Linear Conflict heuristic -- Default\n\
";

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
	{"--size", TYPE_SIZE},
	{"-s", TYPE_SIZE},
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
	int size = 3;

	for (int i = 1; i < ac && error == ""; i++) {
		auto arg = skips.find(string(av[i]));
		if (arg != skips.end()) {
			if ((argsSet & arg->second) == arg->second) {
				error =  "ERROR - Argument \"" + arg->first + "\" already has been represented.\n";
				if (arg->second == TYPE_HELP) {
					error = help;
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

				case TYPE_SIZE:
					i++;
					if (i < ac) {
						string n = string(av[i]);
						string::const_iterator it = n.begin();
						while (it != n.end() && isdigit(*it))
							it++;
						if (it == n.end()) {
							size = stoi(n);
							if (size >= 3) {
								continue;
							}
						}
					}
					error = "ERROR - Argument \"" + arg->first + "\" requires number greater than 3 after.\n";
					break;

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
					error = "ERROR - Argument path already has been represented.\n";
					break;
				}
				argsSet |= TYPE_MAP;
				file = av[i];
			} else {
				error = "ERROR - Extraneous member \"" + string(av[i]) + "\" in input.\n";
			}
		}
	}
	return make_tuple(error, algo, h, file, translate, size);
}