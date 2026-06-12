---
layout: default
title: Préparation du Matériels
parent: Etapes de fabrication
nav_order: 1
---

# Intégration et Validation de la Chaîne Électronique

Ce module central regroupe l'ensemble des systèmes nécessaires aux fonctions de déplacement linéaire, de positionnement angulaire et de manipulation par le vide du **PuzzleBot**.

---

### 1. Partie Motorisation et Guidage (Axes X, Y et Z)

Ce sous-ensemble gère la cinématique cartésienne et la précision des déplacements physiques du robot au-dessus de l'aire de tri.

* **Moteur Pas-à-Pas NEMA 17 :**
    * *Fonction :* Assure la translation horizontale principale (Axe X/Y) du chariot le long du rail de guidage. Couplé à une poulie synchrone, il convertit les impulsions électriques en un positionnement micrométrique.
* **Servomoteur MG996R (Pignons métalliques) :**
    * *Fonction :* Gère l'actionnement mécanique vertical (Axe Z ou $\theta$). Sa configuration à pignons renforcés supporte les cycles répétitifs de descente et de remontée de l'effecteur terminal sans jeu mécanique.
* **Galets de guidage (Roues en V / V-Slot Wheels) :**
    * *Fonction :* Positionnés en configuration isostatique sous le chariot imprimé, ces galets épousent les rainures du profilé d'aluminium pour garantir un coulissement fluide et supprimer les vibrations.
* **Courroie crantée GT2 (6 mm) et Clips de serrage :**
    * *Fonction :* Assure la transmission mécanique directe entre la poulie du moteur NEMA 17 et le corps du chariot mobile.

| Vue Face Avant (Axe Z & Guidage) | Vue Face Arrière (Intégration Moteur) |
| :---: | :---: |
| ![Chariot Face](images/chariot_face.png) | ![Chariot Dos](images/chariot_dos.png) |

---

### 2. Partie Préhension (Système d'Aspiration Pneumatique)

Ce bloc assure la saisie et la dépose des pièces par gestion des flux pneumatiques et création d'une dépression localisée.

* **Mini Pompe à Vide (12V DC) :**
    * *Fonction :* Génère le vide pneumatique au sein du circuit d'aspiration. Sa puissance permet d'établir une force d'adhérence instantanée dès le contact avec la pièce.
* **Électrovanne de relâche (Solenoid Valve 12V) :**
    * *Fonction :* Module de rupture de charge. En s'ouvrant sur commande de l'Arduino, elle réintroduit instantanément la pression atmosphérique dans le circuit de fluide, cassant la dépression pour libérer proprement la pièce.
* **Ventouse en silicone (avec connecteur pneumatique) :**
    * *Fonction :* Effecteur final en contact direct avec l'objet. Sa souplesse compense les micro-irrégularités de surface pour maximiser l'étanchéité sans marquer le matériau.

<p align="center">
  <img src="images/boitier_pneumatique.png" alt="Bloc d'Intégration Pneumatique" width="450"/>
</p>

---

### 3. Composants Électroniques de Puissance et Commande

Ce bloc superposé centralise l'intelligence embarquée de la machine ainsi que la distribution d'énergie vers les différents actionneurs.

* **Calculateur Arduino Uno :**
    * *Fonction :* Unité centrale de traitement. Il interprète les commandes de mouvement, synchronise les signaux de commande et supervise la sécurité globale du système.
* **CNC Shield V3 :**
    * *Fonction :* Carte d'extension d'interface de puissance. Directement empilée sur l'Arduino, elle distribue les lignes d'alimentation stabilisées et rassemble la connectique des moteurs, capteurs de fin de course et vannes de fluide.
* **Drivers de moteurs pas-à-pas (A4988 / DRV8825) :**
    * *Fonction :* Convertisseurs de puissance hacheurs. Ils traduisent les signaux logiques de bas niveau de l'Arduino en impulsions de courant calibrées (réglées via $V_{ref}$) adaptées aux bobinages des moteurs.

<p align="center">
  <img src="images/arduino_integ.png" alt="Intégration Centrale Arduino et Shield" width="450"/>
</p>

---

### 4. Quincaillerie et Structure Bâtie

* **Profilé Aluminium 2020 (V-Slot noir) :**
    * *Fonction :* Poutre structurelle maîtresse de la machine, servant simultanément de châssis rigide et de chemin de roulement mécanique de précision.
* **Inserts filetés en laiton (M3) & Visserie métrique (M3 / M5) :**
    * *Fonction :* Liaison mécanique durable. Insérés à chaud au sein de la structure polymère imprimée en 3D, ces inserts fournissent des filetages métalliques résistants aux contraintes mécaniques et aux vibrations répétées.
