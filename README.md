# 🌀 fract-ol

> Un explorateur de fractales 2D interactif et performant développé en C avec la MiniLibX (Projet de l'École 42).

## Présentation

**fract-ol** est un programme graphique conçu pour générer et explorer des ensembles fractals en temps réel. Il combine des calculs mathématiques sur les nombres complexes avec un rendu par pixels optimisé (via les images de la MiniLibX) et une navigation interactive fluide.

## Fonctionnalités

- **Fractales supportées** : 
  - Ensemble de **Mandelbrot**
  - Ensemble de **Julia** (avec constantes personnalisables)
- **Navigation et Interactions** :
  - Zoom et dézoom fluides centrés dynamiquement sur la position du curseur de la souris (via la molette).
  - Déplacement dans le plan complexe via les flèches directionnelles.
  - Modification dynamique du nombre maximal d'itérations à la volée.
  - Changement de palettes de couleurs en temps réel.
- **Rendu visuel** : Algorithme de lissage des couleurs (`smooth color`) pour un dégradé fluide sans bandes brutales.

## Compilation et Installation

### Prérequis (Linux / X11)
Assurez-vous d'avoir les bibliothèques graphiques nécessaires pour compiler la MiniLibX :
```bash
sudo apt-get install build-essential libx11-dev libxext-dev zlib1g-dev
```

### Compilation
Clonez le dépôt et utilisez le `Makefile` :

```bash
git clone git@github.com:theodelmas21-star/fract-ol.git
cd fract-ol
make
```

## Utilisation

Lancez le programme en spécifiant le nom de la fractale en argument. Pour Julia, vous pouvez optionnellement spécifier les parties réelle et imaginaire de la constante $c$.

```bash
# Pour afficher Mandelbrot
./fract-ol Mandelbrot

# Pour afficher Julia (avec les paramètres par défaut)
./fract-ol Julia

# Pour afficher Julia avec des constantes personnalisées
./fract-ol Julia -0.4 0.6
```

## Contrôles et Raccourcis

| Touche / Action | Action dans le programme |
| :--- | :--- |
| **Molette Haut / Bas** | Zoomer / Dézoomer précisément sur le curseur |
| **Flèches Directionnelles** | Se déplacer (Haut, Bas, Gauche, Droite) |
| **Touches `1`, `2`, `3`** | Changer de palette de couleurs |
| **Touches `+` / `-`** | Augmenter / Diminuer le nombre maximal d'itérations |
| **Touche `ESC`** | Quitter proprement le programme |
| **Croix de la fenêtre** | Fermer l'application |

## Aspects Techniques

- **Gestion mémoire** : Destruction propre des images, de la fenêtre, du display et libération de l'instance MiniLibX à la fermeture.
- **Plan complexe** : Recalcul dynamique des pas (`x_step`, `y_step`) et des bornes lors des zooms et des translations pour conserver un ratio d'affichage parfait.