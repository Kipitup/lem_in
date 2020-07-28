# Lem_in
*Ce projet permet d'appréhender les algorithmes de parcours de graphe et de gestion de flots.*

Le but du projet est de trouver l'ensemble de chemins le plus rapide pour déplacer n fourmis de la salle definie par '##start'
à la salle définie par '##end'. Une seule fourmi peut être présente par salle et par tour.

## Lancer lem-in
```
make && ./lem-in < PATH_TO_MAP
```
#### Output classique :

![classic_output](https://user-images.githubusercontent.com/42733388/88646654-9549d500-d0c5-11ea-841e-454ed5f89f4d.png)

### Exemple de visualisation
* 0 en vert correspond à la salle `##start`
* 21 en rouge correspond à la salle `##end`
* En jaune, les deux chemins trouvés.

![for_lemin_readme](https://user-images.githubusercontent.com/42733388/88639474-1cdf1600-d0bd-11ea-8e3c-18b446aa0901.png)

Pour la résolution du problème, nous avons décidé d'utiliser le BFS comme base pour construire notre algorithme.

# Construction de notre algorithme :

Chaque pièce a une `distance` variable
distance = combien de pas il y a entre le départ et la pièce concernée

Chaque lien aura une variable booléenne `disponible`

Nous parcourons la liste de manière naturelle, premier entré, premier sorti.

Lorsque bfs atteint END :
si plusieurs chemins ont la même distance, nous ajoutons un seul chemin valide (uniquement des nœuds inutilisés et pas de doubles liens croisés) dans nos solutions.

Chaque nouvelle exploration se fera sur une copie du graphe, (dup de la liste d'adjacence).

Chaque solution BFS possible est stockée dans un darray. Chaque bucket contient une liste chaînée avec tous les chemins trouvés. Chaque chemin a sa propre liste chaînée avec tous la pièce qu'il traverse.

## Phase d'exploration BFS :
Chaque fois que l'on visite une salle :
* Mise à jour de l'état du lien et de la distance.
* Une salle n'est considérée comme VISITE que lorsque tous ses liens ont été vérifiés.
* On ne peut visiter une salle que si le lien vers celle-ci est disponible dans notre direction.
* Si la distance d'une pièce a été définie, on ne modifie pas la distance.
* Le BFS s'arrêtera si :
  * Chaque pièce a été visitée
  * La salle END est atteinte

BFS retourne et trouve le chemin :
* Comme dit précédemment, premier entré, premier sorti.
* Chaque fois que l'on retourne dans une salle, nous l'ajoutons à la liste chaînée.

Chemin BFS trouvé :
* Si un lien (ou plus) est égal à 3 (les DEUX sens sont utilisés):
  * On enregistre uniquement des chemins valides à la structure `t_solution`.
  * Supprimer le lien utilisé. (tous)
  * On réinitialise l'ensemble du graphique (distance, lien).
  * Redémarre le BFS.
* Sinon:
  * On ajoute le chemin valide à la structure `t_solution`.
  * Redémarre le BFS.

En parallel ou après que tous les solutions de BFS aient été explorés:
* On fait une simulation en fonction du nombre de fourmis a déplacer et les solutions possibles que l'on trouve.
* On prent la solution la plus optimale pour déplacer les fourmis le plus rapidement possible.

# Unit test
Vous pouvez tester le parsing de lem-in, la map de votre choix (/path_de_la_map) ou le generator.
Le generator doit porter ce nom `generator`, dans notre dossier vous trouverez `generator_linux` et `generator_macos`, pensez à changer le nom et utiliser le generator correspondant à votre OS.

Comment lancer le tester :
```
bash unit_test.sh
```
![teste_lemin](https://user-images.githubusercontent.com/42733388/88645837-ddb4c300-d0c4-11ea-8036-a8b4d0be5901.png)

## Comment cloner le repo ?

Ce repo inclus des submodules. Si vous voulez le cloner, il faut utiliser la commande suivante :
```
git clone --recurse-submodules <repository url>
```
Par exemple si vous clonez avec `git clone <repository url>` il vous manquera le dossier `libft`.

## Auteurs :
* [Alexandre Martino](https://github.com/Kipitup)
* [Francis KANTE](https://github.com/fkante)
