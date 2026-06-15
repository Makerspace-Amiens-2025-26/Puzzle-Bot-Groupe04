---
layout: default
nav_order: 5
title: Conception et prototypage
---

# Conception et prototypage
# PUZZLEBOT — DOSSIER TECHNIQUE FINAL
## 🛠️ Dossier d'Architecture Robotique, Mécanique & Informatique Clé en Main

**Statut du Projet :** `Validé et Finalisé`  
*Ce document constitue le livret de certification mécanique, électronique, logicielle et optique du robot de tri automatisé **PuzzleBot** pour la soutenance finale.*

---

## 🏗️ Description Sommaire des Modules Matériels

### 1. Module : Boîtier d'Arrêt d'Urgence (STOP)
Ce module assure la sécurité immédiate de l'opérateur et de la machine par coupure matérielle directe de la puissance électrique.

* **Composants :** Coque de protection isolante et couvercle amovible configurés pour un bouton coup de poing standard.
* **Liaison OnShape :** Fixation déportée en bord de châssis pour une accessibilité optimale en cas d'anomalie.

| Aperçu Vue Clé 1 | Aperçu Vue Clé 2 |
| :---: | :---: |
| <img src="{{ site.baseurl }}/images/stop_couvercle.png" alt="Couvercle STOP" width="200"/> | <img src="{{ site.baseurl }}/images/stop_boitier.png" alt="Boîtier STOP" width="200"/> |

---

### 2. Module : Berceau de Support Électronique (Arduino)
Interface de fixation et d'isolation électrique protégeant le circuit imprimé de commande.

* **Géométrie :** Socle ajouré épousant l'empreinte de la carte, équipé de quatre bras de fixation suspendus en "L" inversé.
* **Ajustement :** Lumières oblongues intégrées pour tolérer les variations de montage sur le bâti.

| Vue de Dessus (Carte Intégrée) | Vue de Dessous (Structure Seule) |
| :---: | :---: |
| <img src="{{ site.baseurl }}/images/arduino_integ.png" alt="Arduino Intégration" width="200"/> | <img src="{{ site.baseurl }}/images/arduino_berceau.png" alt="Berceau Fixation" width="200"/> |

---

### 3. Module : Adaptateur d'Accouplement pour Servomoteur
Pièce d'accouplement direct gérant l'orientation angulaire de l'effecteur final (Axe $\theta$).

* **Transmission :** Bloc cylindrique compact bloqué radialement par une vis pointeau pour interdire tout glissement sous charge.
* **Sécurité :** Conçu pour faire office de fusible mécanique et rompre avant les pignons internes du servomoteur en cas de collision.

<p align="center">
  <img src="{{ site.baseurl }}/images/adaptateur_servo.png" alt="Adaptateur Servomoteur" width="300"/>
</p>

---

### 4. Module : Système d'Actionnement Vertical et Guidage (Pignon-Crémaillère)
Mécanisme robuste assurant la translation linéaire verticale de la tête de préhension (Axe Z).

* **Cinématique :** Conversion du mouvement rotatif par un engrènement pignon-crémaillère droit assurant un positionnement sans élongation.
* **Guidage :** Double glissière enveloppante en "U" empêchant l'arc-boutement et les flexions structurales.

| Pignon Droit | Crémaillère Mobile | Glissières de Guidage en U |
| :---: | :---: | :---: |
| <img src="{{ site.baseurl }}/images/pignon.png" alt="Pignon Z" width="180"/> | <img src="{{ site.baseurl }}/images/cremaillere.png" alt="Crémaillère Z" width="180"/> | <img src="{{ site.baseurl }}/images/guidage_1.png" alt="Guidage U 1" width="130"/> <img src="{{ site.baseurl }}/images/guidage_2.png" alt="Guidage U 2" width="130"/> |

---

### 5. Module : Boîtier d'Intégration Pneumatique (Pompe & Électrovanne)
Centrale de gestion de dépression pour la préhension des pièces de puzzle par effet ventouse.

* **Intégration :** Cavité cylindrique ventilée dédiée à la mini-pompe à vide couplée à un logement pour l'électrovanne de décharge.
* **Avantage :** Réduction maximale des longueurs de tuyaux pour éliminer les pertes de charge et garantir un relâchement instantané.

<p align="center">
  <img src="{{ site.baseurl }}/images/boitier_pneumatique.png" alt="Boîtier Pneumatique" width="350"/>
</p>

---

### 6. Module : Chariot de Tête Mobile et Effecteur Terminal
Équipage mobile principal regroupant l'ensemble des fonctionnalités de manipulation.

* **Guidage horizontal :** Platine à trois galets à gorge assurant un appui isostatique parfait sur le rail.
* **Entraînement :** Support de motorisation pas-à-pas avec poulie crantée pour la translation autonome (Axe X/Y).

| Face Avant (Effecteur & Z) | Face Arrière (Moteur & Galets) |
| :---: | :---: |
| <img src="{{ site.baseurl }}/images/chariot_face.png" alt="Chariot Face" width="220"/> | <img src="{{ site.baseurl }}/images/chariot_dos.png" alt="Chariot Dos" width="220"/> |

---

### 7. Module : Supports d'Ancrage et Fixation de Profilé Suspendu
Éléments d'extrémité fixes maintenant l'axe linéaire principal au-dessus de l'aire
