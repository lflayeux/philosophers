#include "../inc/philo.h"

long get_time_in_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
void ft_usleep(long time_in_ms)
{
    long time_start;
    long now;

    time_start = get_time_in_ms();
    while (1)
    {
        now = get_time_in_ms();
        if (now - time_start >= time_in_ms)
            break;
        usleep(100);
    }
}

int safe_mutex_lock(pthread_mutex_t *m, t_shared *global)
{
	int stopped;

	pthread_mutex_lock(&(global->stop_mutex));
	stopped = global->stop;
	pthread_mutex_unlock(&(global->stop_mutex));
    if (stopped)
        return (1);
    if (pthread_mutex_lock(m) != 0)
        return (1);
    return (0);
}
