#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define ARGERR		1
# define MALERR		2
# define THRERR		3

typedef struct s_philo
{
	int				err;
	int				nr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	int				eat_limit;
	int				philo_nr;
	int				death;
	int				all_meals;
	pthread_t		*th;
	struct timeval	start;
	struct timeval	end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	msg;
}					t_philo;

typedef struct s_thread
{
	int		philo_nr;
	int		last_eat;
	int		times_eaten;
	int		max_meals;
	int		dead;
	int		dead_ts;
	t_philo	*s;
}			t_thread;

long	ft_atol(char *str);
int		ft_init(int argc, char **argv, t_philo *s);
void	*start_philo(void *s);
void	to_fork(t_thread *thrd);
void	to_eat(t_thread *thrd);
void	to_sleep(t_thread *thrd);
void	to_think(t_thread *thrd);
void	*to_die(void *thrd);
int		timestamp(t_philo *s);
void	put_msg(int i0, int i1, char *s);
int		ft_strlen(char *s);
void	init_birth(t_thread *thrd);

#endif