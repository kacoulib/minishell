/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 05:17:10 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/21 05:17:25 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signum)
{
	(void)signum;
	signal(signum, SIG_IGN);
}

void		signal_handler(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
