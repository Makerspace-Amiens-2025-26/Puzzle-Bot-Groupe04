---
layout: default
title: Assemblage
parent: Etapes de fabrication
nav_order: 2
---

# Assemblage

Après la phase de découpe et de préparation des différents matériaux, l'étape suivante consiste à assembler mécaniquement la structure porteuse et les modules fonctionnels du **PuzzleBot**.

## Étapes d'Assemblage

1. **Organisation et Inventaire** : Disposez l'ensemble des composants préparés sur un plan de travail propre. Classez d'un côté la visserie (écrous en T, vis M4/M5, écrous hexagonaux noyés), de l'autre les profilés d'aluminium usinés, les plaques de support en bois, ainsi que les modules en impression 3D (berceau Arduino, boîtier pneumatique, supports de capteurs).
2. **Assemblage Initial du Châssis (Bâti)** : Commencez par ériger l'ossature fixe en connectant les profilés d'aluminium à l'aide des équerres de fixation renforcées à 90°. Fixez fermement les supports d'ancrage en bois aux extrémités pour stabiliser la structure globale au-dessus de l'aire de travail.
3. **Intégration des Équipages Mobiles** : Insérez le chariot de tête mobile sur le rail principal en ajustant la compression des trois galets à gorge pour obtenir un glissement fluide et sans jeu longitudinal. Montez ensuite l'axe Z mécanique (système pignon-crémaillère droit) sur le chariot avant d'y coupler l'adaptateur du servomoteur pour l'axe $\theta$.
4. **Fixation et Fixations Définitives** : Fixez solidement les boîtiers fonctionnels (boîtier d'arrêt d'urgence en bord de châssis, berceau Arduino ajouré, et boîtier pneumatique à proximité de la tête). Utilisez les lumières oblongues pour ajuster finement les positions avant le serrage complet au couple approprié.

## Vérifications à Effectuer

- **Alignement et Parallélisme des Axes** : Assurez-vous à l'aide d'un réglet ou d'un trusquin que le profilé de guidage horizontal est parfaitement parallèle au plan de travail. Un défaut d'alignement entraînerait un point dur lors des translations du chariot.
- **Course utile et Butées matérielles** : Faites glisser manuellement le chariot et la crémaillère sur toute leur course pour valider l'absence d'arc-boutement ou de frottement excessif. Vérifiez que les supports de capteurs de fin de course entrent bien en contact avec les butées avant que la mécanique ne talonne.
- **Stabilité et rigidité structurelle** : Vérifiez la solidité de l'assemblage global en appliquant de légères contraintes manuelles. L'ossature ne doit présenter aucune torsion ni micro-oscillation afin de garantir la précision future de la caméra de vision.

## Problèmes Communs et Solutions

- **Jeu mécanique ou flottement du chariot** : Si le chariot mobile présente du jeu sur le rail d'aluminium, ajustez l'excentrique des galets à gorge pour resserrer l'appui isostatique contre le profilé.
- **Résistance lors de la descente de l'axe Z** : Si l'engrènement pignon-crémaillère force ou bloque, desserrez légèrement les fixations des glissières de guidage en U, recentrez la crémaillère dans son axe, puis resserrez progressivement le système.
- **Défaut d'alignement des écrous noyés** : Si les vis de fixation ne s'alignent pas avec les plaques de support en bois, desserrez les vis adjacentes pour redonner de la liberté aux lumières oblongues, engagez toutes les vis dans leurs pas respectifs, puis effectuez un serrage en croix.
