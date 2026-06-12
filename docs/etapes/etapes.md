---
layout: default
title: Etapes de fabrication
nav_order: 6
has_children: true
---

# 🛠️ Étapes de Fabrication

Bienvenue dans la section dédiée aux étapes de fabrication et de prototypage industriel du projet **PuzzleBot**. Ce guide rassemble les protocoles techniques requis pour usiner, structurer et assembler les différents modules de notre robot de tri automatisé.

## Aperçu des Étapes

Le processus de fabrication et d'intégration est divisé en plusieurs étapes clés, à suivre méthodiquement :

1. **[Étude de la Documentation et Préparation des Matériaux](#1-étude-de-la-documentation-et-préparation-des-matériaux)** : Phase d'ingénierie préliminaire, contrôle des tensions nominales ($5V$, $12V/24V$) et calibrage initial des drivers de moteurs.
2. **[Découpage et Usinage Numérique](#2-découpage-et-usinage-numérique)** : Découpe laser ou fraisage des plaques de support en bois (Médium/MDF) via fichiers `.DXF` et impression 3D FDM des pièces de liaison (fichiers `.GCODE`).
3. **[Assemblage Mécanique et Structurel](#3-assemblage-mécanique-et-structurel)** : Montage du bâti en profilés d'aluminium 2020, insertion isostatique du chariot mobile et calage de l'axe Z par pignon-crémaillère.
4. **[Intégration et Validation de la Chaîne Électronique](#4-intégration-et-validation-de-la-chaîne-électronique)** : Insertion à chaud des inserts filetés en laiton, câblage de la pile Arduino/CNC Shield V3, et configuration du circuit pneumatique (pompe à vide et électrovanne).

## Commencer

Avant d'initier les manipulations au sein du MakerSpace, assurez-vous d'avoir validé vos compétences sur les machines requises (découpeuse laser, imprimante 3D, scie à métaux) auprès du fabmanager. 

Le respect rigoureux de l'ordre de ces étapes garantit le respect des tolérances géométriques de la structure, condition *sine qua non* pour la précision de l'analyse algorithmique de la caméra de vision zénithale.

---

### ⚠️ Rappel de Sécurité Majeur
Toute manipulation sur le câblage des moteurs pas-à-pas NEMA 17 ou sur les drivers de puissance doit s'effectuer **strictement hors tension** pour éviter la destruction instantanée des puces logiques par arc électrique. Utilisez systématiquement un multimètre pour valider vos polarités avant l'allumage général de la machine.

Pour toute question ou anomalie bloquante durant le processus, veuillez vous référer aux guides de gestion des blocages ou ouvrir
