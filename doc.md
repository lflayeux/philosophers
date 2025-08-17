# PHILOSOPHERS

---

## 1. DESCRIPTION

Ce projet consiste à implémenter le problème des philosophes, un classique de la programmation concurrente.  
Le but est de simuler des philosophes qui mangent, dorment et pensent autour d'une table, en partageant des fourchettes (ressources critiques) sans provoquer de deadlock ni de starvation.

### Arguments du programme

- **number_of_philosopher** : Nombre de philosophes (minimum 1)
- **time_to_die** : Temps (ms) avant qu’un philosophe meure s’il ne mange pas
- **time_to_eat** : Temps (ms) pour manger
- **time_to_sleep** : Temps (ms) pour dormir
- **number_of_times_each_philosopher_must_eat** *(optionnel)* : Nombre de repas à atteindre pour terminer la simulation

### Logs attendus

- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

### Fonctions autorisées

- memset, printf, malloc, free, write
- usleep, gettimeofday
- pthread_create, pthread_detach, pthread_join
- pthread_mutex_init, pthread_mutex_destroy
- safe_mutex_lock, pthread_mutex_unlock

---

## 2. STRUCTURE DU PROJET

- **src/** : Fichiers sources
  - `main.c` : Point d’entrée, gestion des threads et de la boucle principale
  - `init.c` : Initialisation des structures et des mutex
  - `parsing.c` : Vérification et parsing des arguments
  - `philosopher.c` : Routine des philosophes (manger, dormir, penser)
  - `utils.c` : Fonctions utilitaires (temps, usleep, etc.)
- **inc/** : Fichiers d’en-tête
  - `philo.h` : Déclarations des structures et prototypes

---

## 3. TODO

- [x] Définir la structure partagée (`t_shared`)
- [x] Créer et initialiser les mutex pour les fourchettes
- [x] Créer la routine des philosophes
- [x] Créer le thread observateur (monitoring)
- [x] Gérer la synchronisation des accès (mutex)
- [x] Gérer les logs et l’affichage thread-safe
- [x] Gérer la fin de simulation (mort ou tous les repas atteints)
- [ ] Gérer la destruction propre des mutex et la libération mémoire
- [ ] Tester les cas limites (1 philosophe, temps à 0, etc.)
- [ ] Nettoyer et commenter le code
- [ ] Rédiger un README complet

---

## 4. NOTES

- Attention aux conditions de concurrence et à la gestion des ressources.
- Bien vérifier la validité des arguments en entrée.
- Penser à la gestion des erreurs et à la robustesse du programme.

---