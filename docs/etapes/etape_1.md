---
layout: default
title: Préparation du Matériels
parent: Etapes de fabrication
nav_order: 1
---

# Préparation des Matériaux

Cette section décrit la première étape du processus de fabrication : la préparation des matériaux.

## Liste des Matériaux

| Visuel | Composant | Description & Rôle | Spécifications / Usage |
| :---: | :--- | :--- | :---: |
| <img src="https://makerspace-amiens.fr/puzzle-bot/docs/hardware/arduino-uno/image.png" width="80"> | **Arduino Uno** | Carte à microcontrôleur principale. C'est le cerveau du robot qui exécute la logique de commande. | 1 unité |
| <img src="https://makerspace-amiens.fr/puzzle-bot/docs/hardware/cnc-shield/image.png" width="80"> | **CNC Shield (V3)** | Carte d'extension pour l'Arduino. Permet de centraliser le câblage et de piloter facilement plusieurs axes. | 1 unité |
| <img src="https://makerspace-amiens.fr/puzzle-bot/docs/hardware/driver/image-1.png" width="80"> | **Driver de moteur (A4988 / DRV8825)** | Petit module de puissance s'insérant sur la CNC Shield pour contrôler le courant envoyé aux moteurs pas-à-pas. | 1 par moteur |
| <img src="https://www.robot-maker.com/forum/uploads/monthly_02_2025/post-26938-0-02246500-1739972912.jpg" width="80"> | **Kit préhenseur pneumatique** | Ensemble comprenant une mini-pompe à vide et une électrovanne (EV) reliées à une ventouse pour la saisie des pièces. | 1 kit |
| <img src="https://makerspace-amiens.fr/puzzle-bot/docs/hardware/servomotor/image.png" width="80"> | **Servomoteur** | Actionneur rotatif idéal pour piloter un mouvement angulaire limité (par exemple, l'orientation de la ventouse ou un mécanisme d'échappement). | Selon design |
| <img src="https://makerspace-amiens.fr/puzzle-bot/docs/hardware/stepper/17HE12-1204S-500x500.jpg" width="80"> | **Moteur pas-à-pas (NEMA 17)** | Moteur haute précision pour gérer les déplacements linéaires ou angulaires précis des axes du robot. | Selon axes |
| <img src="https://sp.yimg.com/ib/th?id=OPEC.P%2fF%2flbnDYJb0oA474C474&o=5&pid=21.1&w=160&h=105" width="80"> | **Profilés Aluminium** (Type V-Slot 2020) | Structure principale et axes linéaires du châssis. | 4 x 400mm |
## Procédure de Préparation

Cette phase de préparation se divise en trois étapes obligatoires pour sécuriser la fabrication : s'approprier la documentation, valider le matériel par des tests unitaires, puis procéder aux découpes mécaniques.

### 1.  Étude de la Documentation des Matériaux
Avant toute manipulation, il est indispensable de consulter les fiches techniques (*datasheets*) des composants disponibles dans le dossier `docs/datasheets/` du dépôt.
* **Vérification des tensions :** Identifier la tension nominale de chaque élément (5V pour l'Arduino, 12V/24V pour la CNC Shield et la pompe pneumatique).
* ** brochage (Pinout) :** Repérer les broches de commande des drivers et le sens d'insertion sur la CNC Shield pour éviter les inversions.
* **Limites mécaniques :** Prendre connaissance du couple maximal des moteurs pas-à-pas et de la course utile des axes pour ajuster les futurs fins de course.

### 2.  Tests Individuels (Tests Unitaires du Matériel)
Chaque composant doit être validé indépendamment "sur table" avant l'assemblage final.

* **L'Arduino Uno :** Brancher la carte seule en USB. Téléverser un programme servant à allumer les LED par exemple pour s'assurer que le microcontrôleur est fonctionnel.
* **La CNC Shield & Drivers :** Insérer un seul driver. Alimenter la carte en puissance (12V) et mesurer la tension de référence ($V_{ref}$) au multimètre sur le potentiomètre du driver. Ajuster le courant pour qu'il corresponde au courant nominal du moteur pas-à-pas.
* **Les Moteurs Pas-à-Pas :** Connecter un moteur au driver testé, charger un script de rotation simple (Grbl ou script d'essai standard) et vérifier que le moteur tourne sans sauter de pas ni surchauffer.
* **Le Kit Pneumatique :** Alimenter brièvement la mini-pompe en 12V pour vérifier l'aspiration. Tester le déclenchement de l'électrovanne.
* **Le Servomoteur :** Connecter à l'arduino, lancer un programme visant à le faire tourner 

### 3.  Découpage et Usinage
Une fois l'électronique validée, on prépare la structure physique au MakerSpace.

* **Profilés Aluminium :** Mesurer et marquer les longueurs de profilés nécessaires à l'aide d'un trusquin ou d'un réglet de précision. Effectuer la découpe à la scie à ruban ou à la scie circulaire à métaux. Ébavurer soigneusement les bords à la lime plate.
* **Plaques de Support (Plexiglas/PMMA) :** Exporter les plans de la base du robot au format `.DXF`. Charger le fichier dans le logiciel de la découpeuse laser du MakerSpace. Ajuster la vitesse et la puissance selon l'épaisseur de la plaque pour obtenir une coupe nette sans brûlure.
* **Pièces Imprimées 3D :** Générer les fichiers `.GCODE` via le slicer (Cura, PrusaSlicer) pour les pièces de fixation. Lancer les impressions et retirer délicatement les supports à la pince coupante.
>  **Rappel majeur :** L'autonomie au MakerSpace repose sur la responsabilité de chacun. Le respect de ces consignes protège les utilisateurs et garantit la longévité du matériel pédagogique.

## ⚠️ Conseils de Sécurité & Gestion des Blocages
### 1. Sécurité Électrique : Protection du Matériel
* **Double vérification des alimentations :** Avant de mettre le système sous tension, validez systématiquement les polarités au multimètre. Une inversion de polarité ou une tension trop élevée (ex: envoyer du 12V directement sur une broche 5V de l'Arduino) détruira instantanément vos composants.
* **Manipulations hors tension :** Ne connectez et ne déconnectez **jamais** un moteur pas-à-pas ou un driver de la CNC Shield lorsque la carte est alimentée. Cela crée des arcs électriques internes qui grillent les puces instantanément.

### 2. Sécurité des Machines & Qualité de Fabrication
* **Vérification de l'imprimante 3D :** Avant de lancer une longue impression, inspectez la machine : nettoyage du plateau (adhérence), vérification du niveau du lit (*bed leveling*) et état de la buse. Une mauvaise configuration entraîne des décollages (*warping*) ou des tolérances géométriques faussées, rendant les pièces mécaniques inutilisables pour l'assemblage.
* **Règle de la machine inconnue :** Si une machine nécessaire au projet (découpeuse laser, scie à ruban, thermoformeuse) n'est pas maîtrisée par l'équipe, **il est strictement obligatoire de demander l'aide ou une formation** à un encadrant ou au fabmanager avant toute utilisation. Ne prenez aucun risque inutile.
