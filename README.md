# 42sh

42sh est un shell interactif développé en C dans le cadre du cursus informatique d'EPITECH.

## Installation

### Prérequis

* GCC
* make
* libncurses-dev

### Instructions

1. Clonez le dépôt : `git clone https://github.com/EpitechPromo2027/B-PSU-200-REN-2-1-42sh-arthur.doriel.git
2. Allez dans le répertoire du projet : `cd 42sh`
3. Compilez le programme : `make`
4. Lancez le shell : `./42sh`

## Fonctionnalités

42sh prend en charge les fonctionnalités de base d'un shell, telles que :

* L'exécution de commandes simples et de commandes avec arguments
* La redirection d'entrée/sortie
* Les pipes
* Les variables d'environnement
* L'historique des commandes
* Les commandes intégrées (cd, echo, exit)

42sh prend également en charge les fonctionnalités avancées suivantes :

* L'expansion des alias
* L'auto-complétion des commandes et des noms de fichiers
* La coloration syntaxique de la ligne de commande
* L'affichage du temps de chaque commande exécutée
* La possibilité de charger des plugins

## Utilisation

### Commandes simples

Pour exécuter une commande simple, il suffit de taper son nom suivi de ses éventuels arguments, puis de valider avec la touche Entrée :

```shell
$ ls
```

### Redirection d'entrée/sortie

Pour rediriger l'entrée ou la sortie d'une commande vers un fichier, utilisez les symboles `<` et `>` respectivement :

```shell
$ cat < fichier.txt
$ ls > fichiers.txt
```

### Pipes

Pour connecter la sortie d'une commande à l'entrée d'une autre commande, utilisez le symbole `|` :

```shell
$ ls | grep fichier
```

### Historique des commandes

42sh conserve l'historique des commandes tapées dans une session. Pour accéder à l'historique, utilisez la commande `history`. Pour exécuter une commande précédente, utilisez le symbole `!` suivi du numéro de commande :

```shell
$ history
$ !42
```

### Commandes intégrées

42sh prend en charge les commandes intégrées suivantes :

* `cd` : changer de répertoire courant
* `echo` : afficher du texte à l'écran
* `exit` : quitter le shell
* `env` : afficher la liste des variables d'environnement
* `setenv` : définir ou modifier une variable d'environnement
* `unsetenv` : supprimer une variable d'environnement
* `set` : afficher la liste des variables d'environnement et des alias
* `unset` : supprimer une variable d'environnement ou un alias
* `alias` : définir un alias pour une commande
* `unalias` : supprimer un alias existant

### Commandes `env` et `setenv`

La commande `env` affiche la liste des variables d'environnement actuelles :

```shell
$ env
```

La commande `setenv` permet de définir ou de modifier une variable d'environnement :

```shell
$ setenv VAR valeur
```

### Commande `unsetenv`

La commande `unsetenv` permet de supprimer une variable d'environnement :

```shell
$ unsetenv VAR VAR1 VAR2
```

### Commande `set`

La commande `set` affiche la liste des variable local définis :

```shell
$ set
```

La commande `set` permet aussi de définir ou de modifier une variable local :

```shell
$ set VAR=value VAR2=value2
```

### Commande `unset`

La commande `unset` permet de supprimer une variable d'environnement ou un alias :

```shell
$ unset VAR VAR2 VAR3
```

### Commande `alias`

La commande `alias` permet de définir un alias pour une commande :

```shell
$ alias ll 'ls -l'
```

### Commande `unalias`

La commande `unalias` permet de supprimer un alias existant :

```shell
$ unalias ll
```
## Sauvegarde

### Alias

Les alias sont sauvegardé dans le fichier `.alias` il est possible d'en ajouter ou d'en supprimer manuellement :
```text
ll=ls -l
```
### Variable Local
Les variables local sont sauvegardé dans le fichier `.local_var` il est possible d'en ajouter ou d'en supprimer manuellement :
```text
var=value
```

### Auto-complétion

42sh prend en charge l'auto-complétion des commandes et des noms de fichiers. Pour activer l'auto-complétion, appuyez sur la touche Tabulation.

### Coloration syntaxique

charge la coloration syntaxique de la ligne de commande pour faciliter la lecture et la compréhension des commandes tapées. Les différents éléments de la commande, tels que les noms de commande, les arguments, les options, les symboles de redirection, etc., sont colorés de manière distincte.

## Auteurs

42sh a été développé par les étudiants d'EPITECH suivants :

* Tom Lefoix `tom.lefoix@epitech.eu`
* Justine Loizel `justine.loizel@epitech.eu`
* Arthur Doriel `arthur.doriel@epitech.eu`
* Léa Allain `lea.allain@epitech.eu`
* Jule Danet `jule.danet@epitech.eu`
