#include <stdio.h>

#include "utils.h"
#include "actions.h"
#include "philo_three.h"

short
	ph_speak(long ts, int nb, char *message, t_shared *sh)
{
	sem_wait(sh->speaks);
	printf("[%ld]%d %s\n", ts, nb, message);
	sem_post(sh->speaks);
	return (1);
}
