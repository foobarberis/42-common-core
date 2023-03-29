/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:14:03 by mbarberi          #+#    #+#             */
/*   Updated: 2023/03/29 14:08:51 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thread_eat(t_thread *t, int fork1, int fork2)
{
	pthread_mutex_lock(&(t->env->mtx[fork1]));
	print_action(t, MSG_FORK);
	pthread_mutex_lock(&(t->env->mtx[fork2]));
	print_action(t, MSG_FORK);
	print_action(t, MSG_EAT);
	my_usleep(t->env->arg[T2E]);
	pthread_mutex_lock(&(t->env->common_mtx));
	t->env->last_meal[t->id] = time_now();
	pthread_mutex_unlock(&(t->env->common_mtx));
	pthread_mutex_unlock(&(t->env->mtx[fork1]));
	pthread_mutex_unlock(&(t->env->mtx[fork2]));
	t->nmeal++;
	if (t->nmeal == t->env->arg[LIM] && t->env->full[t->id] == false)
	{
		pthread_mutex_lock(&(t->env->common_mtx));
		t->env->full[t->id] = true;
		pthread_mutex_unlock(&(t->env->common_mtx));
	}
}

static void	thread_wait(t_thread *t)
{
	print_action(t, MSG_SLEEP);
	my_usleep(t->env->arg[T2S]);
	print_action(t, MSG_THINK);
}

static void	thread_routine(t_thread *t)
{
	while (!t->env->exit)
	{
		if (t->id % 2 == 1)
			thread_eat(t, t->id, (t->id + 1) % t->env->arg[N]);
		else
			thread_eat(t, (t->id + 1) % t->env->arg[N], t->id);
		thread_wait(t);
	}
	pthread_mutex_unlock(&(t->env->mtx[t->id]));
	pthread_mutex_unlock(&(t->env->mtx[(t->id + 1) % t->env->arg[N]]));
}

void	*thread_init(void *arg)
{
	t_thread		t;
	static uint8_t	id = 0;

	t.env = (t_env *)arg;
	t.nmeal = 0;
	pthread_mutex_lock(&(t.env->common_mtx));
	t.id = id++;
	pthread_mutex_unlock(&(t.env->common_mtx));
	t.env->full[t.id] = false;
	t.env->last_meal[t.id] = t.env->start;
	while (t.env->exit)
		;
	print_action(&t, MSG_THINK);
	thread_routine(&t);
	return (NULL);
}