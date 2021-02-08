#include "philo_two.h"
#include "utils.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>

int
ph_sem_init(t_shared *sh, int number)
{
	if ((sh->forks = sem_open(PHILO_SEMF, O_CREAT, 0777, number)) == SEM_FAILED
		|| sem_unlink(PHILO_SEMF))
		return (0);
	if ((sh->speaks = sem_open(PHILO_SEMS, O_CREAT, 0777, 1)) == SEM_FAILED
	|| sem_unlink(PHILO_SEMS))
		return (0);
	return (1);
}

short
	ph_free(t_shared *sh, t_philo **pht)
{
	int i;

	i = -1;
	while (++i < *sh->max_ph)
	{
		free(pht[i]);
	}
	free(sh->max_ph);
	free(sh->time_to_die);
	free(sh->time_to_eat);
	free(sh->time_to_sleep);
	free(sh->time);
	free(sh->apetite);
	printf("FREED ALL PHILOSOPHERS");
	exit(1);
	return (1);
}

int
	ph_atoi(char *str)
{
	int n;

	n = 0;
	if (*str == 0)
		return (0);
	while (*str)
		n = n * 10 + (*str++ - 48);
	return (n);
}

void
	ft_putstr(char *str)
{
	int i;

	i = -1;
	while (str[i])
		write(1, &str[++i], 1);
}

short
	ph_isfullnum(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] > 47 && str[i] < 58))
			return (0);
	}
	return (1);
}

long
	ph_timest(short status, long ct)
{
	struct timeval	tv;
	static long		ftime;

	gettimeofday(&tv, NULL);
	if (status == 0)
	{
		ftime = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
		printf("time was set : [%ld]", ftime);
	}
	return ((status == 0) ? ftime : ct - ftime);
}

short
	ph_fills(int ac, char *av[], t_shared *sh)
{
	if (!(sh->max_ph = (int*)malloc(sizeof(int))))
		return (-1);
	if (!(sh->time_to_die = (unsigned int*)malloc(sizeof(unsigned int))))
		return (-1);
	if (!(sh->time_to_eat = (unsigned int*)malloc(sizeof(unsigned int))))
		return (-1);
	if (!(sh->time_to_sleep = (unsigned int*)malloc(sizeof(unsigned int))))
		return (-1);
	if (!(sh->time = (int*)malloc(sizeof(int))))
		return (-1);
	if (!(sh->apetite = (int*)malloc(sizeof(int))))
		return (-1);
	*sh->max_ph = ph_atoi(av[1]);
	*sh->time_to_die = ph_atoi(av[2]);
	*sh->time_to_eat = ph_atoi(av[3]);
	*sh->time_to_sleep = ph_atoi(av[4]);
	*sh->time = ph_timest(0, 0);
	sh->isdead = 0;
	if (ac == 6)
		*sh->apetite = ph_atoi(av[5]);
	else
		*sh->apetite = -1;
	return (0);
}
