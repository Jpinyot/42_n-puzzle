/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openStack.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:50:54 by mfiguera          #+#    #+#             */
/*   Updated: 2020/09/30 21:53:51 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openStack.h"

void OpenStack::addState(State *state)
{
    State *currState = top_;
    State *prevState = NULL;

    while(currState != NULL) {
        if (state->getScore() < currState->getScore())
            break;
        prevState = currState;
        currState = currState->getNext();
    }

    state->setNext(currState);

    if (prevState == NULL)
        top_ = state;
    else
        prevState->setNext(state);
}

void OpenStack::popTop()
{
    if (top_ != NULL) {
        top_ = top_->getNext();
    }
}

void OpenStack::display()
{
    cout << "Stack:\n";
    State *curr = top_;
    while (curr)
    {
        curr->display();
        curr = curr->getNext();
    }
}

bool OpenStack::stateIsOpen(State *state)
{
    State *currState = top_;
    while (currState) {
        if (currState->getPuzzle() == state->getPuzzle()) {
            return true;
        }
        currState = currState->getNext();
    }
    return false;
}
