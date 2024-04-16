# TODO

## Objectif 1

> Les processus en cours d'exécution sur l'ordinateur, ainsi que leurs PIDs

- [x] Implémenter la commande de base
- [x] Créer le parser d'arguments
    - [x] `-h` => affiche les commandes disponibles
    - [x] sans arg => affiche tous les processus
    - [x] `[process]` => affiche seulement le processus
    - [ ] `-d <pid>` => affiche le processus relié au pid
- [x] Afficher les processus en cours d'exécution

## Objectif 2

> Détails du processus, y compris par exemple son utilisation de la mémoire virtuelle ou la commande dont il émane

- [ ] Implémenter les détails

## Objectif 3

> Threads en cours d'exécution dans chaque processus, y compris leur sID de thread, leurs points d'entrée, la dernière signalée et l'état du thread

## Format d'affichage

```
Name    Pid Pri Thd Hnd Priv       CPU Time     Elapsed Time
process   0   0   0   0    0  000:00:00.000    000:00:00.000
```