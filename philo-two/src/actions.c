#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#include "utils.h"
#include "actions.h"
#include "philo_two.h"

short
	ph_speak(long ts, int nb, char *message, t_shared *sh)
{
	sem_wait(sh->speaks);
	printf("[%ld]%d %s\n", ts, nb, message);
	sem_post(sh->speaks);
	return (1);
}

short
	ph_eat(t_philo *ph)
{
	struct timeval ctv;

	gettimeofday(&ctv, NULL);
	if ((ph_timest(1, (ctv.tv_sec * 1000) +
		(ctv.tv_usec / 1000)) -
		ph->lastate) > *ph->shared->time_to_die)
	{
		ph->isdead = 1;
		return (1);
	}
	sem_wait(ph->shared->forks);
	sem_wait(ph->shared->forks);
	gettimeofday(&ctv, NULL);
	ph_speak(ph_timest(1, (ctv.tv_sec * 1000) +
		(ctv.tv_usec / 1000)), ph->num, PHILO_EAT, ph->shared);
	usleep(*ph->shared->time_to_eat * 1000);
	ph->lastate = ph_timest(1, (ctv.tv_sec * 1000) +
		(ctv.tv_usec / 1000));
	sem_post(ph->shared->forks);
	sem_post(ph->shared->forks);
	return (0);
}

short
	ph_sleep(t_philo *ph)
{
	struct timeval ctv;

	gettimeofday(&ctv, NULL);
	ph_speak(ph_timest(1, (ctv.tv_sec * 1000) +
		(ctv.tv_usec / 1000)), ph->num, PHILO_SLEEP, ph->shared);
	usleep(*ph->shared->time_to_sleep * 1000);
	return (0);
}

short
	ph_think(t_philo *ph)
{
	struct timeval ctv;

	gettimeofday(&ctv, NULL);
	ph_speak(ph_timest(1, (ctv.tv_sec * 1000) +
		(ctv.tv_usec / 1000)), ph->num, PHILO_THINK, ph->shared);
	return (0);
}
