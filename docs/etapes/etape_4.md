---
layout: default
nav_order: 5
title: Conception et prototypage
---

# 4. Architecture Informatique, Vision IA et Algorithmique (Software Stack)

L'intelligence opérationnelle du **PuzzleBot** repose sur la synergie entre un script d'analyse de haut niveau exécuté sur l'ordinateur hôte (Python / OpenCV) et un microcontrôleur embarqué temps réel (Arduino Uno) assurant l'actionnement mécanique.

---

## 4.1 Phase 1 : La Fondation Matérielle & Cinématique (Les Muscles)
La première étape a consisté à concevoir l'architecture de bas niveau et à prendre le contrôle direct des actionneurs. Le robot exploite une cinématique cartésienne (X, Y) construite sur une base de type CNC DIY, supervisée par le calculateur embarqué.

* **Contrôle Moteur :** Écriture du micrologiciel (*firmware*) Arduino pour coordonner les mouvements des moteurs pas-à-pas (Axe Y dédié au grand portique, Axe X gérant le bras transversal mobile).
* **Actionnement de la Tête :** Intégration algorithmique du servomoteur de plongée (Axe Z vertical) pour commande la descente et la remontée de l'effecteur terminal.
* **Banc d'Essai Cinématique :** Validation des déplacements fondamentaux par l'envoi de commandes série brutes afin de vérifier le respect des repères orthonormés et l'absence de point dur mécanique.

| Métrique de Validation | Objectif Technique | Indicateur de Succès |
| :---: | :---: | :---: |
| Pilotage Direct des Axes | Validation des sens de rotation | Absence d'inversion logique |
| Course Maximale Z | Course utile d'approche | Fluidité sans arc-boutement |

---

## 4.2 Phase 2 : La Métrologie de Précision & Étalonnage (Le Sens du Réel)
Afin d'interagir précisément avec son environnement, le robot doit s'affranchir des coordonnées machine abstraites (impulsions) pour travailler en coordonnées physiques métriques (millimètres).

* **Protocole d'Impulsion Pure :** Injection d'une commande calibrée de $1000 \text{ pas}$ exacts sur chaque axe de translation.
* **Mesure Physique :** Relevé au réglet de précision de la distance réelle parcourue (ex: $205 \text{ mm}$ mesurés pour 1000 pas sur l'axe Y).
* **Calcul des Ratios d'Étalonnage :** Détermination mathématique des coefficients de conversion injectés dans le firmware :
    $$\text{Ratio}_Y = 4.88 \text{ pas/mm} \quad | \quad \text{Ratio}_X = 3.45 \text{ pas/mm}$$
* **Tuning de la Dynamique :** Ajustement fin du délai entre les impulsions (`vitesseDelay`) afin d'éradiquer les phénomènes de résonance acoustique (bruit de grattement mécanique) et d'optimiser le couple moteur.

---

## 4.3 Phase 3 : La Vision par Ordinateur & Cartographie Tactique (L'Œil)
Cette phase vise à doter le robot d'un système de perception zénithal (webcam) et à implémenter le pipeline de traitement d'image nécessaire à la cartographie de l'aire de jeu.

* **Calibration de la Caméra :** Utilisation d'un motif en damier (*Chessboard calibration*) pour extraire la matrice intrinsèque de la lentille (`mtx`, `dist`) et corriger numériquement la distorsion optique de type *fisheye*.
* **Transformation Homographique (Perspective Transform) :** Détermination des quatre sommets de l'espace de travail à l'écran. L'algorithme calcule une matrice de projection pour redresser virtuellement le flux vidéo incliné, renvoyant un plan 2D orthonormé parfait.
* **Mise à l'Échelle Absolue :** Configuration du ratio de conversion pixel/millimètre ($1 \text{ pixel} \approx 0.5 \text{ mm}$). Les tests de validation par rapport à une règle physique confirment une erreur de mesure inférieure à $0.5 \text{ mm}$.
* **Origine Machine Dynamique (Home) :** Implémentation logicielle d'un point de référence mobile (via interaction Clic Droit) pour synchroniser instantanément le repère physique du robot avec la cartographie de l'IA avant chaque cycle.

| Module de Vision | Algorithme Appliqué | Résultat Attendu |
| :---: | :---: | :---: |
| Correction Optique | Équations de Brown-Conrady | Suppression de la distorsion |
| Redressement Plan | Matrice d'Homographie 3x3 | Espace de travail à plat |

---

## 4.4 Phase 4 : L'Intelligence Artificielle de Détection (Le Cerveau)
L'objectif est d'automatiser l'identification des pièces de puzzle, la localisation de leur centre de gravité et le calcul de leur orientation angulaire.

* **Arbitrage Matériau (Pivot Stratégique) :** Suite à des limitations de contraste lors de l'usage de pièces en bois brut (teinte trop proche du gantry), le choix s'est porté sur un polymère jaune vif mat, optimisant la réflectance.
* **Filtrage Chromatique HSV :** Implémentation d'un masque de seuillage dans l'espace Couleur-Saturation-Valeur (HSV) pour isoler le spectre du jaune, éliminant instantanément les artefacts du fond (ombres, perçages du plateau).
* **Binarisation d'Otsu (Seuillage Dynamique) :** Utilisation de l'algorithme d'Otsu pour calculer automatiquement le seuil de coupure idéal entre le corps de la pièce et le repère noir de l'arc de cercle, assurant la robustesse du système face aux variations de l'éclairage ambiant.
* **Analyse de Quadrants Angulaires :** Division de la matrice de la pièce isolée en 4 quadrants distincts. Le décompte des pixels noirs de forte densité permet à l'IA de localiser le pôle de l'arc de cercle (ex: `Quadrant Nord-Est`) et d'en déduire l'orientation angulaire exacte.

> ⚠️ **Note d'Ingénierie :** Le passage à l'espace colorimétrique HSV plutôt que RGB est indispensable pour ce type d'application industrielle, car il dissocie l'information de chrominance (couleur pure) de la luminance (luminosité), rendant le script insensible aux ombres portées par le portique.

---

## 4.5 Phase 5 : Intégration Système & État Avancé
Le projet est actuellement dans sa phase d'unification des actionneurs finaux pour assurer le déroulement autonome du cycle complet de manipulation.

* **Mise à Niveau Pneumatique :** Substitution de la ventouse passive par une préhension active combinant une mini-pompe à vide 12V et une électrovanne de décharge pilotée pour un cycle *Pick & Place* instantané.
* **Isolation Électronique de Puissance :** Conception d'un étage de commutation à transistor MOSFET pour interfacer la logique 5V de l'Arduino avec la puissance 12V requise par les actionneurs pneumatiques.
* **Axe de Rotation Terminal (Axe R / $\theta$) :** Intégration d'un servomoteur à rotation continue (360°) faisant office de poignet motorisé, indispensable pour corriger l'assiette angulaire de la pièce avant sa dépose.
* **Interface Superviseur (GUI) :** Finalisation d'un tableau de bord de contrôle sous Python (Tkinter/OpenCV), fusionnant le retour vidéo analysé par l'IA et un pupitre de commande manuelle (commande angulaire par molette, activation de la pompe par barre d'espace).

| Composant Intégré | Type
