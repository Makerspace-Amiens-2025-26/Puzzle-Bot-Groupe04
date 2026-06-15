import cv2
import numpy as np
import glob
import os

print("--- DEMARRAGE DU CALCUL DE CALIBRATION ---")

# 1. Paramètres physiques de ton damier (BoofCV 9x6 carrés = 8x5 intersections)
CHECKERBOARD = (8, 5)
TAILLE_CARRE_MM = 30.0

# Critère d'arrêt pour l'algorithme d'affinement des pixels
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# 2. Préparation des coordonnées 3D théoriques parfaites (0,0,0), (30,0,0), (60,0,0)...
objp = np.zeros((CHECKERBOARD[0] * CHECKERBOARD[1], 3), np.float32)
objp[:, :2] = np.mgrid[0:CHECKERBOARD[0], 0:CHECKERBOARD[1]].T.reshape(-1, 2) * TAILLE_CARRE_MM

# Tableaux pour stocker les points de toutes les images
objpoints = [] # Points 3D dans le monde réel (parfaits)
imgpoints = [] # Points 2D dans l'image (déformés par la lentille)

# 3. Récupération de tes 19 photos
chemin_images = r"C:\Users\ALAEFAABE2025\Desktop\CODES PROJET ROBOT\calibration_camera\*.png"
images = glob.glob(chemin_images)

print(f"{len(images)} images trouvées. Analyse en cours (ça peut prendre quelques secondes)...")

images_valides = 0

for fname in images:
    img = cv2.imread(fname)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Recherche des coins du damier
    ret, corners = cv2.findChessboardCorners(gray, CHECKERBOARD, None)

    # Si les coins sont trouvés, on les affine et on les stocke
    if ret == True:
        objpoints.append(objp)
        
        # Affinement de la précision au sous-pixel
        corners2 = cv2.cornerSubPix(gray, corners, (11,11), (-1,-1), criteria)
        imgpoints.append(corners2)
        
        images_valides += 1
        
        # Dessine le damier trouvé sur l'image pour te montrer ce qu'il a vu
        cv2.drawChessboardCorners(img, CHECKERBOARD, corners2, ret)
        cv2.imshow('Analyse des coins (Appuie sur une touche ou attends)', cv2.resize(img, (800, 600)))
        cv2.waitKey(200) # Montre l'image pendant 0.2 secondes

cv2.destroyAllWindows()

# 4. Le cœur du calcul de la matrice
if images_valides > 0:
    print(f"\nCalcul de la matrice avec {images_valides} images valides...")
    ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)

    # Sauvegarde des données dans un fichier mathématique (.npz)
    chemin_sauvegarde = r"C:\Users\ALAEFAABE2025\Desktop\CODES PROJET ROBOT\calibration_camera\donnees_calibration.npz"
    np.savez(chemin_sauvegarde, mtx=mtx, dist=dist)
    
    print("--------------------------------------------------")
    print("✅ CALIBRATION RÉUSSIE !")
    print(f"Fichier de correction sauvegardé sous : {chemin_sauvegarde}")
    print(f"Erreur de reprojection (RMS) : {ret:.4f} pixels")
    print("--------------------------------------------------")
else:
    print("❌ ECHEC : L'algorithme n'a trouvé le damier complet sur aucune image.")