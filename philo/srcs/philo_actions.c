#include "../includes/philo.h"

void	to_fork(t_thread *thrd)
{
	int	ts;

	pthread_mutex_lock(&thrd->s->forks[thrd->philo_nr - 1]);
	if (thrd->philo_nr != thrd->s->nr_of_philo)
		pthread_mutex_lock(&thrd->s->forks[thrd->philo_nr]);
	else
		pthread_mutex_lock(&thrd->s->forks[0]);
	pthread_mutex_lock(&thrd->s->msg);
	ts = timestamp(thrd->s);
	if (!thrd->s->death)
	{
		put_msg(ts, thrd->philo_nr, " has taken a fork\n");
		put_msg(ts, thrd->philo_nr, " has taken a fork\n");
	}
	pthread_mutex_unlock(&thrd->s->msg);
}

void	to_eat(t_thread *thrd)
{
	int	ts;

	ts = timestamp(thrd->s);
	pthread_mutex_lock(&thrd->s->msg);
	if (!thrd->s->death)
		put_msg(ts, thrd->philo_nr, " is eating\n");
	pthread_mutex_unlock(&thrd->s->msg);
	thrd->last_eat = ts;
	usleep(thrd->s->time_to_eat * 1000);
	pthread_mutex_unlock(&thrd->s->forks[thrd->philo_nr - 1]);
	if (thrd->philo_nr != thrd->s->nr_of_philo)
		pthread_mutex_unlock(&thrd->s->forks[thrd->philo_nr]);
	else
		pthread_mutex_unlock(&thrd->s->forks[0]);
	thrd->times_eaten++;
}

void	to_sleep(t_thread *thrd)
{
	int	ts;

	pthread_mutex_lock(&thrd->s->msg);
	ts = timestamp(thrd->s);
	if (!thrd->s->death)
		put_msg(ts, thrd->philo_nr, " is sleeping\n");
	pthread_mutex_unlock(&thrd->s->msg);
	usleep(thrd->s->time_to_sleep * 1000);
}

void	to_think(t_thread *thrd)
{
	int	ts;

	ts = timestamp(thrd->s);
	pthread_mutex_lock(&thrd->s->msg);
	if (!thrd->s->death)
		put_msg(ts, thrd->philo_nr, " is thinking\n");
	pthread_mutex_unlock(&thrd->s->msg);
}

void	*to_die(void *thrd)
{
	int			wait;
	t_thread	*tmp;

	tmp = (t_thread *)thrd;
	while (!tmp->s->death && !tmp->max_meals)
	{
		wait = (tmp->s->time_to_die - (timestamp(tmp->s) - tmp->last_eat))
			* 1000;
		usleep(wait);
		tmp->dead_ts = timestamp(tmp->s);
		if (!tmp->max_meals && !tmp->s->death
			&& tmp->dead_ts - tmp->last_eat >= tmp->s->time_to_die)
		{
			pthread_mutex_lock(&tmp->s->msg);
			if (!tmp->s->death)
			{
				tmp->dead = 1;
				tmp->s->death = 1;
			}
			if (!tmp->max_meals && tmp->dead)
				put_msg(tmp->dead_ts, tmp->philo_nr, " is dead\n");
			pthread_mutex_unlock(&tmp->s->msg);
		}
	}
	return (NULL);
}
