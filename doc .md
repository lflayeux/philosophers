# PHILOSOPHERS
---


##	1. DESCRIPTION

<br>

#####	Write a program that take on arguments :
>	- number_of_philosopher (min 1)
>	- time_to_die (min 0)
>	- time_to_eat (min 0)
>	- time_to_sleep (min 0)
>	- number_of_times_each_philosopher_must_eat

<br>

#####	With logs :
>	- timestamp_in_ms X has taken a fork
>	- timestamp_in_ms X is eating
>	- timestamp_in_ms X is sleeping
>	- timestamp_in_ms X is thinking
>	- timestamp_in_ms X died

<br>

#####	Functons to use :
>	memset, printf, malloc, free, write,
>	usleep, gettimeofday, pthread_create,
>	pthread_detach, pthread_join, pthread_mutex_init,
>	pthread_mutex_destroy, pthread_mutex_lock,
>	pthread_mutex_unlock

<br>

---

## 2. TODO

> - [] Shared struct
> - [] Observer thread
> - [] s'occuper des mutex pr les forks
> - [] restructer les inits