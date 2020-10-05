/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/05 12:45:12 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "state.h" */
#include "stateManhattanDistance.h"
#include "closedStack.h"
#include "openStack.h"
#include <iostream>

static int solve(StateManhattanDistance *firstState)
{
	OpenStack openStack = OpenStack();
	openStack.addState(firstState);

	ClosedStack closedStack = ClosedStack();
	
	while (openStack.getTop() != NULL) {
		openStack.display();
		State *state = openStack.getTop();
		if (state->getHeuristicScore() == 0) {
			/* state->display(); */
			return 0;
		}
		else {
			openStack.popTop();
			closedStack.addState(state);
			if (state->canMoveTo(N)) {
				StateManhattanDistance *newState = new StateManhattanDistance(state, N);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
				/* newState.display(); */
			}

			if (state->canMoveTo(E)) {
				/* cout <<"E\n"; */
				StateManhattanDistance *newState = new StateManhattanDistance(state, E);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
				/* newState.display(); */
			}

			if (state->canMoveTo(S)) {
				/* cout <<"S\n"; */
				StateManhattanDistance *newState = new StateManhattanDistance(state, S);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
				/* newState.display(); */
			}

			if (state->canMoveTo(W)) {
				/* cout <<"W\n"; */
				StateManhattanDistance *newState = new StateManhattanDistance(state, W);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
				/* newState.display(); */
			}
		}
	}

	return 1;
}

const int k_test_size = 9;

#include <QApplication>
#include <QPushButton>
#include "ui/puzzleWidget.h"

/* int main(int argc, char** argv) */
/* { */
/* 	QApplication app (argc, argv); */


/* 	PuzzleWidget	puzzle(3); */
/* 	PuzzleWidget.show(); */
/* 	/1* puzzle.show(); *1/ */

/* 	QPushButton button("OLI"); */
/* 	button.show(); */
/* 	return app.exec(); */
/* } */


#include <QtCore>
#include <QtWidgets>
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

//![1]
    QGraphicsRectWidget *button1 = new QGraphicsRectWidget;
    QGraphicsRectWidget *button2 = new QGraphicsRectWidget;
    QGraphicsRectWidget *button3 = new QGraphicsRectWidget;
    QGraphicsRectWidget *button4 = new QGraphicsRectWidget;
    button2->setZValue(1);
    button3->setZValue(2);
    button4->setZValue(3);
    QGraphicsScene scene(0, 0, 300, 300);
    scene.setBackgroundBrush(Qt::black);
    scene.addItem(button1);
    scene.addItem(button2);
    scene.addItem(button3);
    scene.addItem(button4);
//![1]
    GraphicsView window(&scene);
    window.setFrameStyle(0);
    window.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    window.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    window.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//![2]
    QStateMachine machine;

    QState *group = new QState();
    group->setObjectName("group");
    QTimer timer;
    timer.setInterval(1250);
    timer.setSingleShot(true);
    /* QObject::connect(group, &QState::entered, &timer, QOverload<>::of(&QTimer::start)); */
//![2]

//![3]
    QState *state1;
    QState *state2;
    QState *state3;
    QState *state4;
    QState *state5;
    QState *state6;
    QState *state7;

    state1 = createGeometryState(button1, QRect(100, 0, 50, 50),
                                 button2, QRect(150, 0, 50, 50),
                                 button3, QRect(200, 0, 50, 50),
                                 button4, QRect(250, 0, 50, 50),
                                 group);
//![3]
    state2 = createGeometryState(button1, QRect(250, 100, 50, 50),
                                 button2, QRect(250, 150, 50, 50),
                                 button3, QRect(250, 200, 50, 50),
                                 button4, QRect(250, 250, 50, 50),
                                 group);
    state3 = createGeometryState(button1, QRect(150, 250, 50, 50),
                                 button2, QRect(100, 250, 50, 50),
                                 button3, QRect(50, 250, 50, 50),
                                 button4, QRect(0, 250, 50, 50),
                                 group);
    state4 = createGeometryState(button1, QRect(0, 150, 50, 50),
                                 button2, QRect(0, 100, 50, 50),
                                 button3, QRect(0, 50, 50, 50),
                                 button4, QRect(0, 0, 50, 50),
                                 group);
    state5 = createGeometryState(button1, QRect(100, 100, 50, 50),
                                 button2, QRect(150, 100, 50, 50),
                                 button3, QRect(100, 150, 50, 50),
                                 button4, QRect(150, 150, 50, 50),
                                 group);
    state6 = createGeometryState(button1, QRect(50, 50, 50, 50),
                                 button2, QRect(200, 50, 50, 50),
                                 button3, QRect(50, 200, 50, 50),
                                 button4, QRect(200, 200, 50, 50),
                                 group);
//![4]
    state7 = createGeometryState(button1, QRect(0, 0, 50, 50),
                                 button2, QRect(250, 0, 50, 50),
                                 button3, QRect(0, 250, 50, 50),
                                 button4, QRect(250, 250, 50, 50),
                                 group);
    group->setInitialState(state1);
//![4]

//![5]
	/* animate each button */
QParallelAnimationGroup animationGroup;
QSequentialAnimationGroup *subGroup;

QPropertyAnimation *anim = new QPropertyAnimation(button4, "geometry");
anim->setDuration(1000);
anim->setEasingCurve(QEasingCurve::OutElastic);
animationGroup.addAnimation(anim);
//![5]

//![6]
subGroup = new QSequentialAnimationGroup(&animationGroup);
subGroup->addPause(100);
anim = new QPropertyAnimation(button3, "geometry");
anim->setDuration(1000);
anim->setEasingCurve(QEasingCurve::OutElastic);
subGroup->addAnimation(anim);
//![6]

subGroup = new QSequentialAnimationGroup(&animationGroup);
subGroup->addPause(150);
anim = new QPropertyAnimation(button2, "geometry");
anim->setDuration(1000);
anim->setEasingCurve(QEasingCurve::OutElastic);
subGroup->addAnimation(anim);

subGroup = new QSequentialAnimationGroup(&animationGroup);
subGroup->addPause(200);
anim = new QPropertyAnimation(button1, "geometry");
anim->setDuration(1000);
anim->setEasingCurve(QEasingCurve::OutElastic);
subGroup->addAnimation(anim);

//![7]
    /* StateSwitcher *stateSwitcher = new StateSwitcher(&machine); */
    /* stateSwitcher->setObjectName("stateSwitcher"); */
    /* group->addTransition(&timer, &QTimer::timeout, stateSwitcher); */
    /* stateSwitcher->addState(state1, &animationGroup); */
    /* stateSwitcher->addState(state2, &animationGroup); */
/* //![7] */
    /* stateSwitcher->addState(state3, &animationGroup); */
    /* stateSwitcher->addState(state4, &animationGroup); */
    /* stateSwitcher->addState(state5, &animationGroup); */
    /* stateSwitcher->addState(state6, &animationGroup); */
/* //![8] */
    /* stateSwitcher->addState(state7, &animationGroup); */
//![8]

//![9]
    machine.addState(group);
    machine.setInitialState(group);
    machine.start();
//![9]

    window.resize(300, 300);
    window.show();

    return app.exec();
}
/* #include "main.moc" */
