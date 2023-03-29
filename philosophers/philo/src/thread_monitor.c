/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:12:50 by mbarberi          #+#    #+#             */
/*   Updated: 2023/03/29 14:07:42 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thread_monitor_full(t_env *env)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (i < env->arg[N])
	{
		pthread_mutex_lock(&(env->common_mtx));
		if (env->full[i] == true)
			c++;
		pthread_mutex_unlock(&(env->common_mtx));
		i++;
	}
	if (c == env->arg[N])
	{
		pthread_mutex_lock(&(env->common_mtx));
		printf("All philosophers have eaten %d times.\n", env->arg[LIM]);
		env->exit = true;
		pthread_mutex_unlock(&(env->common_mtx));
		return (1);
	}
	my_usleep(1.25 * (env->arg[T2E] + env->arg[T2S]));
	return (0);
}

static int	thread_monitor_death(t_env *env)
{
	int			i;
	time_t		now;

	i = 0;
	while (i < env->arg[N])
	{
		pthread_mutex_lock(&(env->common_mtx));
		now = time_now() - env->last_meal[i];
		pthread_mutex_unlock(&(env->common_mtx));
		if (now >= env->arg[T2D])
		{
			pthread_mutex_lock(&(env->common_mtx));
			printf("%ld %d %s\n", time_now() - env->start, i + 1, MSG_DIE);
			env->exit = true;
			pthread_mutex_unlock(&(env->common_mtx));
			return (1);
		}
		i++;
	}
	return (0);
}

void	thread_monitor(t_env *env)
{
	while (1)
	{
		if (thread_monitor_full(env))
			break ;
		if (thread_monitor_death(env))
			break ;
	}
}