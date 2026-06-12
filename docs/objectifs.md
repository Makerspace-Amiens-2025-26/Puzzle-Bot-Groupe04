---
layout: default
nav_order: 3
title: Objectifs du projet
---

# Introduction

Dans le cadre de l'automatisation industrielle et de la robotique de précision, la manipulation d'objets aux formes complexes et irrégulières représente un défi technique majeur. Le projet **PuzzleBot** s'inscrit dans cette dynamique en proposant une solution robotisée capable d'identifier, de saisir, de réorienter et d'assembler des pièces de puzzle de manière totalement autonome. Ce système combine l'ingénierie mécanique, l'électronique embarquée et la vision par ordinateur pour recréer un cycle complet de tri intelligent.

## Contexte du Projet

La conception de ce robot s'articule autour des ressources et des technologies disponibles au sein du MakerSpace. Face aux solutions industrielles souvent lourdes et rigides, le PuzzleBot explore une approche agile basée sur une architecture en portique (*Gantry system*) optimisée, exploitant la synergie entre la fabrication numérique (impression 3D, usinage du bois) et des composants électroniques standardisés du marché (écosystème Arduino). L'enjeu est de démontrer qu'une intégration matérielle et logicielle maîtrisée permet d'atteindre des standards de précision rigoureux avec un coût de développement maîtrisé.

## Objectifs du Projet

L'appareil doit répondre à plusieurs jalons de performance et de viabilité technique :
* **Automatisation complète :** Réduire l'intervention humaine au strict paramétrage initial de la machine.
* **Précision spatiale et angulaire :** Assurer un positionnement millimétrique lors de la dépose et une correction angulaire exacte via l'axe $\theta$.
* **Saisie universelle :** Fiabiliser la préhension des pièces par un système d'aspiration pneumatique, indépendamment des contours de la cible.
* **Sécurité opératoire :** Garantir l'intégrité physique de l'utilisateur et du matériel grâce à des arrêts d'urgence physiques et des butées de fin de course redondantes.

# Existant

Les systèmes de tri automatisés traditionnels reposent majoritairement sur des bras articulés de type SCARA ou des convoyeurs à bandes triant des pièces géométriques simples (puces, boîtes, composants calibrés). Cependant, ces structures s'avèrent complexes à programmer pour de la correction angulaire fine et nécessitent souvent des pinces mécaniques spécifiques, inadaptées à la fragilité et à la diversité des pièces de puzzle. Le PuzzleBot se démarque en transposant ces technologies industrielles dans une structure compacte à coordonnées cartésiennes en trois axes, optimisant ainsi l'espace et la vitesse de traitement.

# Cahier des Charges

Pour valider la conformité du système lors de la soutenance finale, le robot doit respecter les spécifications techniques suivantes :

* **Contraintes Mécaniques :** Structure rigide à base de profilés d'aluminium et de supports en bois pour absorber les vibrations ; course utile des axes X, Y et Z configurée pour couvrir l'intégralité du plateau de jeu.
* **Contraintes Électroniques :** Alimentation stabilisée séparant la puissance (12V/24V pour les moteurs et la pompe) et la commande (5V pour l'Arduino) ; isolation complète des circuits dans des boîtiers dédiés.
* **Contraintes Pneumatiques :** Maintien d'une dépression constante durant la phase de transfert et chute immédiate de la pression lors de la phase de dépose par ouverture de l'électrovanne.
* **Contraintes Optiques :** Positionnement fixe et alignement zénithal parfait de la caméra pour éviter toute distorsion géométrique lors de l'acquisition des formes par le logiciel de vision.
