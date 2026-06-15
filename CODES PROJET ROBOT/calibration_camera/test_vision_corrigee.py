import cv2
import numpy as np

print("--- DEMARRAGE DU FLUX VIDEO CORRIGE ---")

# 1. Chargement de tes "lunettes correctrices" (le fichier .npz)
chemin_donnees = r"C:\Users\ALAEFAABE2025\Desktop\CODES PROJET ROBOT\calibration_camera\donnees_calibration.npz"

try:
    with np.load(chemin_donnees) as X:
        mtx = X['mtx']
        dist = X['dist']
    print("✅ Matrice de calibration chargée avec succès.")
except FileNotFoundError:
    print(f"❌ Erreur : Fichier introuvable au chemin {chemin_donnees}")
    exit()

# 2. Allumage de la caméra DFROBOT
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

if not cap.isOpened():
    print("Erreur caméra.")
    exit()

print("Appuie sur 'Q' pour quitter.")

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # 3. Le calcul d'optimisation (pour gérer les bords de l'image grand-angle)
    h, w = frame.shape[:2]
    # getOptimalNewCameraMatrix permet de garder tous les pixels valides
    newcameramtx, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h), 1, (w,h))

    # 4. LE REDRESSEMENT (La magie d'OpenCV)
    frame_corrigee = cv2.undistort(frame, mtx, dist, None, newcameramtx)

    # (Optionnel) Découpage pour enlever les bordures noires créées par le redressement
    x, y, w_roi, h_roi = roi
    frame_corrigee_crop = frame_corrigee[y:y+h_roi, x:x+w_roi]

    # 5. Affichage comparatif
    cv2.imshow('1. Vision Brute (Grand-Angle deforme)', frame)
    cv2.imshow('2. Vision Robot (Geometrie parfaite)', frame_corrigee_crop)

    if cv2.waitKey(1) == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
