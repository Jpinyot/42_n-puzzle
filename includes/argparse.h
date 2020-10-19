/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:11:00 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/19 09:03:07 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <iostream>
#include <tuple>
#include <fstream>
#include "algorithms.h"
#include "state.h"

tuple<string, Algorithms, Heuristic, char*, bool, int, bool> parse_args(int ac, char **av);