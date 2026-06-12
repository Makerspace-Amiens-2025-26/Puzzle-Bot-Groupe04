---
layout: default
nav_order: 4
title: Études et choix techniques
---

# Études et choix techniques
## 📐 Études et Choix Techniques

Cette section détaille les arbitrages technologiques et les justifications d'ingénierie ayant guidé la conception du **PuzzleBot**. L'objectif clé était d'équilibrer robustesse mécanique, précision de positionnement et contraintes budgétaires.

### 1. Architecture Cinématique et Motorisation (Axes X, Y, Z)
* **Structure de type Portique (Gantry Assembly) :** Ce choix a été privilégié par rapport à un bras articulé pour garantir une rigidité structurelle maximale et une zone de travail parfaitement rectangulaire, simplifiant la transposition mathématique des coordonnées de la caméra de vision.
* **Moteurs Pas-à-Pas (NEMA) & CNC Shield :** Pour le déplacement horizontal (X/Y), les moteurs pas-à-pas associés aux drivers A4988 (ou similaires) permettent un contrôle en boucle ouverte extrêmement précis et économique, éliminant le besoin de capteurs de position coûteux.
* **Transmission Axe Z (Pignon-Crémaillère droit) :** Contrairement à une transmission par courroie susceptible d'élongation ou à une vis sans fin trop lente, le système pignon-crémaillère offre une excellente répétabilité, une vitesse de descente rapide et la réversibilité nécessaire pour éviter d'endommager l'effecteur en cas de contact brutal.

### 2. Choix des Matériaux et Processus de Fabrication
* **Ossature en Profilés d'Aluminium :** Les profilés rainurés standardisés ont été choisis pour leur excellent rapport poids/rigidité et la modularité qu'ils offrent, facilitant l'ajustement des supports d'ancrage et des capteurs de fin de course.
* **Plaques de Support en Bois (Médium/MDF) :** Le choix s'est porté sur des panneaux de bois de précision usinés au MakerSpace (via découpe laser ou fraiseuse CNC). Ce matériau offre une excellente absorption des micro-vibrations générées par les moteurs, une grande facilité de modification (perçage, taraudage additionnel) et un impact environnemental réduit par rapport aux polymères de type Plexiglas.
* **Composants Structurels en Impression 3D :** Les pièces de géométrie complexe (berceau Arduino, adaptateur de servomoteur, boîtier pneumatique) ont été modélisées sur OnShape et imprimées en polymère thermoplastique. Cela a permis un prototypage rapide et l'intégration de fonctions de sécurité comme le "fusible mécanique" sur l'accouplement du servomoteur.

### 3. Système de Saisie et Préhension (Effecteur Terminal)
* **Système par Dépression (Préhension Pneumatique) :** L'utilisation d'une mini-pompe à vide combinée à une ventouse a été préférée à une pince mécanique (gripper). Cette solution technique permet de saisir les pièces de puzzle de manière universelle, sans se soucier de leur géométrie extérieure, de leur orientation initiale ou des risques de glissement mécanique.
* **Électrovanne de Décharge :** L'intégration d'une électrovanne directement à proximité immédiate de la tête de préhension permet de casser le vide instantanément. Ce choix technique est indispensable pour assurer la productivité du cycle de tri et une dépose d'une précision millimétrique, sans effet de rémanence ou de collage de la pièce.

### 4. Environnement de Contrôle et Vision Optique
* **Calculateur Arduino Uno :** Choisi pour sa robustesse, sa faible consommation et sa compatibilité immédiate avec le firmware open-source de contrôle numérique (GRBL ou scripts de commande sur table).
* **Caméra Zénithale Fixe :** Le positionnement de la caméra sur un portique de vision dédié et stabilisé par des équerres renforcées en T élimine toute parallaxe. Ce choix technique permet de traiter l'image sur un plan strictement bidimensionnel (2D), réduisant drastiquement la complexité des algorithmes de détection de contours et de calcul d'orientation ($\theta$).
