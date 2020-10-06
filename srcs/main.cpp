/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/06 10:54:48 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "state.h" */
#include "stateManhattanDistance.h"
#include "closedStack.h"
#include "openStack.h"
#include <iostream>

const int k_test_size = 9;

#include <QApplication>
#include <QPushButton>
#include <unistd.h>

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "ui/mainWindow.h"

int main(int argc, char** argv)
{
	QApplication* app = new QApplication(argc, argv);
	
	MainWindow mw;
			cout << "##/n";
	mw.oli();
	mw.show();
	/* QPushButton btn("DEU"); */
	/* btn.show(); */
	/* deu(argc, argv); */
	/* oli(argc, argv); */
	app->exec();
	return 0;
}
