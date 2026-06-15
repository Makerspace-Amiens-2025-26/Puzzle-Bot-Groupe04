import cv2
import os

# CORRECTION 1 : Le 'r' avant les guillemets dit à Python d'ignorer les '\'
dossier_images = r"C:\Users\ALAEFAABE2025\Desktop\CODES PROJET ROBOT\calibration_camera"

if not os.path.exists(dossier_images):
    os.makedirs(dossier_images)

# CORRECTION 2 : Ajout de cv2.CAP_DSHOW pour forcer DirectShow (contourne le bug Windows)
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

print("--- OUTIL D'ACQUISITION POUR CALIBRATION ---")
print("Touche 'S' : Sauvegarder l'image actuelle")
print("Touche 'Q' : Quitter le programme")

# Vérification si la caméra s'ouvre bien
if not cap.isOpened():
    print("Erreur : Impossible d'ouvrir la caméra. Vérifie qu'elle n'est pas utilisée par une autre application.")
else:
    compteur = 0
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Erreur de lecture du flux vidéo.")
            break

        # Affichage du flux en direct
        cv2.imshow('Acquisition Calibration', frame)
        
        touche = cv2.waitKey(1) & 0xFF

        # Si on appuie sur 's', on enregistre l'image
        if touche == ord('s'):
            compteur += 1
            # Utilisation de os.path.join pour créer le chemin du fichier proprement
            nom_fichier = os.path.join(dossier_images, f"calib_{compteur}.png")
            cv2.imwrite(nom_fichier, frame)
            print(f"Photo {compteur} sauvegardée : calib_{compteur}.png")

        # Si on appuie sur 'q', on ferme
        elif touche == ord('q'):
            print(f"Fin de l'acquisition. {compteur} photos sauvegardées.")
            break

cap.release()
cv2.destroyAllWindows()