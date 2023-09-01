# Get Next Line - 42 School Project

## 📋 Résumé

Ce projet a pour objectif de développer une fonction en C, `get_next_line`, qui retourne une ligne lue depuis un descripteur de fichier. Cette fonction est particulièrement utile pour lire des fichiers texte ligne par ligne. Le projet inclut également des fonctions bonus pour gérer plusieurs descripteurs de fichier simultanément.

## 💻 Technologies Utilisées

- Langage de programmation : C
- Utilisation de fonctions systèmes comme `read`, `malloc`, et `free`.

## 📦 Installation

```bash
git clone https://github.com/Jeanmichel7/get_next_line.git
cd get_next_line
make[ bonus]
```

## 🛠️ Utilisation

Pour utiliser la fonction `get_next_line`, compilez votre fichier source avec le fichier `get_next_line.c` :

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 your_file.c get_next_line.c get_next_line_utils.c
./a.out
```

Vous pouvez changer la valeur de `BUFFER_SIZE` pour tester avec une taille de buffer différente.

## 🧪 Test

```bash
./tester[_bonus]
```

## 📜 Règles du Projet

- Le code doit être écrit en respectant la Norme de 42.
- Le Makefile doit avoir les règles standard (`all`, `clean`, `fclean`, `re`).
- Les variables globales sont interdites.
- Les fonctions ne doivent pas s’arrêter de manière inattendue.
- Toute mémoire allouée sur la heap doit être libérée.
- La fonction `lseek()` et la libft ne sont pas autorisées.
