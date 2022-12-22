/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:32:43 by sangkkim          #+#    #+#             */
/*   Updated: 2022/12/22 16:09:17 by sangkkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include "fork.h"
#include "philo.h"
#include "simulation.h"
#include "error_code.h"

void	*philo_main(void *arg);
int		monitor_main(t_simulation *sim);

int		get_condition(t_condition *condition, int argc, char *argv[]);
int		init_simulation(t_simulation *sim);
int		run_simulation(t_simulation *sim);
int		terminate_simulation(t_simulation *sim);

#include <stdio.h>
int	main(int argc, char *argv[])
{
	int				err;
	t_simulation	sim;

	memset(&sim, 0, sizeof(t_simulation));
	err = get_condition(&(sim.condition), argc, argv);
	if (err == 0)
		init_simulation(&sim);
	if (err == 0)
		err = run_simulation(&sim);
	if (err == 0)
		err = monitor_main(&sim);
	if (err == 0)
		err = terminate_simulation(&sim);
	if (err != 0)
		perror("ERROR");
	return (err);
}

int	run_simulation(t_simulation *sim)
{
	long long	i;
	int			err;

	gettimeofday(&(sim->start_time), NULL);
	sim->status = sim_running;
	sim->start_time.tv_usec += 100000;
	if (sim->start_time.tv_usec >= 1000000)
	{
		sim->start_time.tv_sec += 1;
		sim->start_time.tv_usec -= 1000000;
	}
	i = 0;
	err = 0;
	while (err == 0 && i < sim->condition.philo_num)
	{
		sim->philos[i].last_eat_time = sim->start_time;
		err = pthread_create(&(sim->threads[i]), NULL, \
			philo_main, &(sim->philos[i]));
		i++;
	}
	return (err);
}

int	terminate_simulation(t_simulation *sim)
{
	long long	i;
	int			err;

	i = 0;
	err = 0;
	while (err == 0 && i < sim->condition.philo_num)
		err = pthread_detach(sim->threads[i++]);
	i = 0;
	while (err == 0 && i < 2 + (2 * sim->condition.philo_num))
		err = pthread_mutex_destroy(&(sim->mutexes[i++]));
	if (err == 0)
	{
		free(sim->threads);
		free(sim->mutexes);
		free(sim->forks);
		free(sim->philos);
	}
	return (err);
}
