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
Avant de commencer toute manipulation physique, il est impératif de prendre connaissance des notices techniques (*datasheets*) des différents composants, disponibles au sein du répertoire `docs/datasheets/` du projet.
* **Vérification des tensions :** Déterminer la tension nominale requise par chaque composant (5V concernant l'Arduino, 12V/24V pour la pompe pneumatique ainsi que la CNC Shield).
* **Brochage (Pinout) :** Identifier l'emplacement des broches de contrôle des drivers et prêter attention au sens de montage sur la CNC Shield afin d'écarter tout risque d'inversion.
* **Limites mécaniques :** Relever le couple maximal supporté par les moteurs pas-à-pas ainsi que la course maximale des différents axes pour configurer correctement les futurs capteurs de fin de course.

### 2.  Tests Individuels (Tests Unitaires du Matériel)
Chaque élément matériel doit impérativement être testé et validé de manière isolée sur le plan de travail avant de procéder à l'assemblage général.

* **L'Arduino Uno :** Connecter la carte informatique seule via le port USB. Charger un programme basique (comme le clignotement de LED) dans le but de confirmer le bon fonctionnement du microcontrôleur.
* **La CNC Shield & Drivers :** Mettre en place un unique driver sur la carte. Raccorder le système à l'alimentation de puissance (12V) puis utiliser un multimètre pour relever la tension de référence ($V_{ref}$) au niveau du potentiomètre du driver. Ajuster le signal pour qu'il soit en adéquation avec l'intensité nominale du moteur pas-à-pas.
* **Les Moteurs Pas-à-Pas :** Relier un moteur au driver préalablement calibré, puis exécuter un code de rotation basique (Grbl ou un script de test générique). S'assurer que la rotation s'effectue de manière fluide, sans perte de pas ni élévation excessive de la température.
* **Le Kit Pneumatique :** Brancher brièvement la micro-pompe sur une source 12V pour attester de sa capacité d'aspiration. Contrôler également le bon déclenchement de l'électrovanne.
* **Le Servomoteur :** Effectuer le raccordement à la carte Arduino et téléverser un script permettant de tester son amplitude de mouvement.

### 3.  Découpage et Usinage
Dès que la partie électronique est validée, la fabrication des éléments structurels peut débuter au sein du MakerSpace.

* **Profilés Aluminium :** Déterminer et tracer les repères de coupe sur les profilés en employant un réglet de précision ou un trusquin. Réaliser le tronçonnage à l'aide de la scie circulaire à métaux ou de la scie à ruban. Utiliser une lime plate pour éliminer soigneusement toutes les bavures sur les sections coupées.
* **Plaques de Support (Bois/Médium) :** Transférer les modélisations de la structure et de la base du robot sous le format `.DXF`. Importer ce fichier dans le programme de la machine (découpeuse laser ou fraiseuse CNC) du MakerSpace. Configurer les paramètres de découpe selon l'essence et l'épaisseur du bois pour obtenir des contours nets et des dimensions ajustées.
* **Pièces Imprimées 3D :** Utiliser un logiciel de tranchage (Cura, PrusaSlicer) pour convertir les fixations en fichiers `.GCODE`. Lancer les cycles d'impression, puis employer une pince coupante pour retirer proprement les structures de support.
>  **Rappel majeur :** Le bon fonctionnement et l'autonomie au sein du MakerSpace reposent sur le sens des responsabilités de chacun. L'application stricte de ces règles assure la sécurité des usagers et préserve la durabilité des équipements pédagogiques.

## ⚠️ Conseils de Sécurité & Gestion des Blocages
### 1. Sécurité Électrique : Protection du Matériel
* **Double vérification des alimentations :** Contrôlez impérativement les polarités à l'aide d'un multimètre avant toute mise sous tension. Une inversion des pôles ou l'application d'une tension inappropriée (par exemple injecter du 12V sur une entrée 5V de l'Arduino) causera la destruction immédiate du matériel.
* **Manipulations hors tension :** Ne procédez **en aucun cas** au branchement ou au débranchement d'un driver ou d'un moteur pas-à-pas lorsque la CNC Shield est active. Les arcs électriques générés en interne détruiraient instantanément les composants électroniques.

### 2. Sécurité des Machines & Qualité de Fabrication
* **Vérification de l'imprimante 3D :** Inspectez l'état général de la machine avant d'initier un long cycle de fabrication : propreté du plateau (pour garantir l'accroche), calibrage de la hauteur du plateau (*bed leveling*) et examen de la buse. Un mauvais paramétrage initial provoque des défauts de décollement (*warping*) ou des écarts de cotes, rendant les pièces impropres à l'assemblage final.
* **Règle de la machine inconnue :** Si les membres de l'équipe ne maîtrisent pas l'usage d'un équipement requis pour le projet (scie à ruban, thermoformeuse, découpeuse laser), **il est formellement requis de solliciter l'accompagnement ou une initiation** auprès d'un encadrant ou du fabmanager avant de manipuler l'outil. Ne vous exposez à aucun danger inutile.
