/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openStack.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:45:15 by mfiguera          #+#    #+#             */
/*   Updated: 2020/09/30 12:43:12 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"

class OpenStack
{
    private:
        State   *top_;
    
    public:
        OpenStack()
        {
            top_ = NULL;
        }

        void    addState(State &state);
        State   *getTop() {return top_;}
        
        void    popTop();
};