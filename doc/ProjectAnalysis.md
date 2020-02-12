# Project Analysis
Ce fichier résume nos idées et premiers projets au premier jour du projet. Il présente ensuite un résumé de l'état final du projet et une comparaison avec ce que nous attendions, et ce que nous pourrions espérer améliorer.
Voici les aspects initiaux dont nous avons discuté au premier jour du projet :
* Analyse d'usage (Contexte, fonctions souhaitées par l'utilisateur, interactions, fonctions de base)
* Analyse fonctionnelle (Blocs fonctionnels, interactions avec l'environnement)
* Architecture gros grains (Classes principales, modularité/extensibilité, interactions)

## Analyse d'usage
### Contexte 
Le logiciel que nous allons créer devra être dans un premier temps utilisé dans un contexte de rendu d'une scène sur un plan (pas de prise en compte des déplacements de l'oeil pour le moment) qui pourrait être utilisé pour faire des affiches/images/scènes sur un plan fixe.

### Fonctions souhaitées
Le logiciel devra pouvoir fournir une interface utilisateur lui permettant de choisir une scène ou bien des objets à afficher avec le nombre et la couleur des sources lumineuses.
Il devra pouvoir tourner sur le CPU ou le GPU de l'utilisateur s'il en possède.

### Interactions 
Pour la représentation des objets, on pourra utiliser un format de fichier OBJ [Voir ici](https://fr.wikipedia.org/wiki/Objet_3D_(format_de_fichier)) et pour transférer les données entre machine et logiciel, on nous propose d'utiliser XML. Pour accélérer les calculs, on pourrait faire du multithreading avec MPI ou OpenMP et/ou utiliser le GPU avec OpenCL.
Il faudra réfléchir à l'interaction entre machine et logiciel plus en profondeur.

### Fonctions de test de base 
Verification du format des fichiers utilisés
Test d'un 'hit' par un rayon lumineux
Test de la bonne communication entre la machine et le logiciel; le CPU et le GPU.

## Analyse fonctionnelle 
### Blocs fonctionnels 
Les fonctions (ou blocs fonctionnels) de base auxquelles nous devrions réfléchir sont les suivantes : 
* Fonction de création dans la scène d'objets (plans, sphères etc ou autres formes plus complexes)
* Fonction de calcul du rendu des rayons pour un objet (ou un point) et une ou plusieurs sources
* Fonction d'affichage du rendu
* Fonction de récupération des données utilisateur utilisées pour l'initialisation
* Fonction de transmission des informations entre la machine et le logiciel

### Interactions 
La fonction de récupération des données utilisateurs devra transmettre ses résultats à la machine pour démarrer la création de la scène puis le calcul des rayons. Ce résultat sera à nouveau transmis au logiciel pour le rendu.

## Architecture gros grains
### Classes principales
Pour le moment j'ai pensé aux classes principales suivantes :
* Object (qui définit un objet représenté dans la scène avec couleur texture etc) dont les classes dérivées correspondraient chacune à un forme différent et au sein desquelles on pourrait peut etre créer automatiquement un fichier au format OBJ (Voir s'il ne faudrait pas séparer l'objet et sa surface comme expliqué dans le pdf du projet) C'est notamment dans cette classe que l'on effectuera les calculs de rayons (intrersection, reflexion/refraction/diffraction) 
* Source : Source lumineuse (avec couleur, eventuelle direction et puissance etc.)
* Rayon : On pourrait représenter les rayons eux même par un objet (voir pdf du projet)

### Modularité/Extensibilité
Les classes et objets devront pouvoir supporter un ajout de sous classe qui ne perturberait pas le calcul de rayons.

### Interactions
Les sources emettent des rayons (en fonction de leur cone directionnel). Lors de l'intersection d'un rayon avec la surface d'un objet, on calcule le rendu.

## Retour sur le projet

