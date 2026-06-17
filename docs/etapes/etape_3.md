---
layout: default
title:  Intégration et Validation de la Chaîne Électronique
parent: Etapes de fabrication
nav_order: 3
---

# 3. Architecture Électronique, Câblage et Gestion de Puissance (Le Système Physique)

Cette partie décrit l'architecture matérielle électrique, la distribution des signaux de commande depuis le microcontrôleur Arduino Uno / CNC Shield, et la résolution des problématiques de puissance pour les actionneurs pneumatiques et mécaniques.

---

## 3.1 Gestion et Calibrage de l'Axe Horizontal (Axes X et Y)
Le déplacement horizontal synchrone repose sur un couplage de deux moteurs pas-à-pas configurés en mode Maître/Esclave.
* **Cinématique :** Le moteur situé à gauche agit comme le moteur principal (Maître) ; c'est lui qui initie et entraîne mécaniquement le mouvement du moteur situé à droite (Esclave).
* **Raccordement Pilotes (Drivers) :** Chaque moteur est piloté individuellement via un driver dédié (A4988 ou DRV8825) inséré sur le CNC Shield.
* **Brochage Arduino/Shield :** * Le moteur de gauche (Maître) est connecté aux broches de l'axe **Y**.
  * Le moteur de droite (Esclave) est connecté aux broches de l'axe **X**.

---

## 3.2 Gestion et Calibrage de l'Axe Vertical (Axe Z)
La translation verticale permettant l'approche et la plongée de l'équipage mobile est gérée par un moteur pas-à-pas indépendant.
* **Cinématique :** Il déplace verticalement le compartiment supérieur supportant l'effecteur.
* **Raccordement :** Le moteur est relié à son driver dédié, directement interfacé avec les broches de l'axe **Z** de la carte de commande Arduino.

---

## 3.3 Sécurité Matérielle : Boîtier d'Arrêt d'Urgence (Coupure Directe)
Le système intègre un protocole de sécurité à déclenchement matériel pur.
* **Principe Électrique :** Le bouton "coup de poing" d'arrêt d'urgence est câblé **en série** directement sur la ligne d'alimentation principale **12V** qui alimente la puissance de la carte de commande.
* **Avantage Sécurité :** Cette configuration coupe instantanément l'énergie mécanique par rupture de ligne. Elle est 100 % matérielle et **ne nécessite aucun code ni programmation Arduino** pour fonctionner, éliminant tout risque de défaillance logicielle (*freeze* du script).

---

## 3.4 Calibration des Capteurs Fins de Course (*Endstops*)
Afin de sécuriser la structure contre les collisions et de permettre le calage de l'origine machine (*Homing*), le montage utilise deux capteurs électromécaniques (butées).
* **Configuration des Axes :**
  1. **Capteur Bas :** Positionné pour intercepter et stopper la course du gantry horizontal (liant les moteurs gauche et droit).
  2. **Capteur Haut :** Positionné pour intercepter et stopper la course verticale du moteur de l'axe Z.
* **Brochage d'un Capteur (3 Broches) :**
  * `VCC` : Alimentation logique (5V).
  * `GND` : Masse commune, reliée directement au pôle GND de l'Arduino.
  * `SIGNAL` : Relié à une broche d'entrée numérique (PIN) au choix sur le CNC Shield (ex: `X-Minus` / `Y-Minus`).

---

## 3.5 Actionnement de l'Effecteur Terminal (Pignon-Crémaillère)
La manipulation fine et l'orientation des pièces d'assemblage font intervenir deux servomoteurs distincts configurés pour les mouvements de translation et de rotation :
* **Translation (Axe Z secondaire) :** Gère la descente fine de la tête.
* **Rotation (Axe R / $\theta$) :** Assure la correction angulaire de la pièce avant dépose.
* **Connexion :** Ils sont branchés directement sur les sorties PWM dédiées (généralement associées aux broches de commande des servomoteurs du CNC Shield).

---

## 3.6 Isolation de Puissance Pneumatique (Pompe, Électrovanne & Module MOSFET)
L'étape de saisie active par dépression a nécessité la résolution d'un conflit de tension entre la logique de commande et la puissance des actionneurs.

* **Problématique Initiale :** Le signal logique délivré par l'Arduino est limité à **5V**, ce qui était insuffisant pour alimenter simultanément la mini-pompe à vide et l'électrovanne, ces deux composants nécessitant une alimentation stable et puissante en **12V**.
* **Solution Technique :** Intégration d'une carte d'interface de puissance à **transistor MOSFET**, imprimée et gravée en suivant le schéma technique de référence fourni par l'enseignant. Ce module fait office de relais statique électronique.
* **Logique de Fonctionnement et Câblage :**
  * **Côté Commande (Basse Puissance) :** L'Arduino envoie un signal logique 5V (état `HIGH`) sur la grille (*Gate*) du MOSFET.
  * **Côté Puissance (Haute Puissance) :** Le MOSFET commute et ferme le circuit de puissance **12V**, délivrant l'ampérage nécessaire pour activer de concert la pompe (aspiration) et l'électrovanne (maintien/décharge).

| Actionneur Pneumatique | Tension requise | Rôle Système | Commande Logicielle |
| :---: | :---: | :---: | :---: |
| Mini-Pompe à Vide | 12 V | Génération de la dépression (Saisie) | Signal numérique via MOSFET |
| Électrovanne 3 voies | 12 V | Cassage du vide (Relâchement instantané) | Signal inversé/coordonné |

*(Note : Pour le compte-rendu final sur votre site GitHub Pages, vous pourrez insérer ci-dessous le schéma de câblage réel ou la photo de votre carte MOSFET afin d'illustrer la correspondance exacte des borniers d'alimentation `V+ / V-` de la pompe et de la vanne).*
