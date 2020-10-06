/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:50:54 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/06 11:48:46 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void OpenStack::addState(State *state)
{
    State *currState = top_;
    State *prevState = NULL;

    while (currState != NULL) {
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

void UnsortedStack::addState(State* state)
{
    state->setNext(top_);
    top_ = state;
}

void Stack::popTop()
{
    if (top_ != NULL) {
        top_ = top_->getNext();
    }
}

void Stack::display() const
{
    cout << "Stack:\n";
    State *curr = top_;
    while (curr)
    {
        curr->display();
        curr = curr->getNext();
    }
}

const bool Stack::stateIsOpen(State *state) const
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
