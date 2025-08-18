#include "../inc/philo.h"

long current_time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
void ft_usleep(long time_in_ms)
{
    long start_time;
    long now;

    start_time = current_time_ms();
    while (1)
    {
        now = current_time_ms();
        if (now - start_time >= time_in_ms)
            break;
        usleep(100);
    }
}

int safe_mutex_lock(pthread_mutex_t *m, t_table *global)
{
	int simulation_stopped;

	pthread_mutex_lock(&(global->stop_mutex));
	simulation_stopped = global->simulation_stop;
	pthread_mutex_unlock(&(global->stop_mutex));
    if (simulation_stopped)
        return (1);
    if (pthread_mutex_lock(m) != 0)
        return (1);
    return (0);
}
