import cv2
import numpy as np
import serial
import time
import os

print("--- SYSTEME JAVIS : ARMEMENT DU SYSTEME COMPLET ---")

# =====================================================================
# 1. CONNEXION ARDUINO
# =====================================================================
port_arduino = 'COM22'
try:
    arduino = serial.Serial(port_arduino, 115200, timeout=1)
    time.sleep(2)
    print("✅ Liaison serie avec les moteurs : OPERATIONNELLE")
except:
    print(f"❌ ERREUR : Le port {port_arduino} est introuvable. Fermez le Moniteur Serie Arduino !")
    exit()

# =====================================================================
# 2. GEOMETRIE DE LA VRAIE MAP
# =====================================================================
LARGEUR_REELLE_MM = 260
HAUTEUR_REELLE_MM = 295
ECHELLE = 2

largeur_plan = LARGEUR_REELLE_MM * ECHELLE 
hauteur_plan = HAUTEUR_REELLE_MM * ECHELLE 

OFFSET_X = largeur_plan // 2
OFFSET_Y = hauteur_plan // 2

# =====================================================================
# 3. VISION CAMERA
# =====================================================================
cap = None
for i in [0, 1, 2]:
    temp_cap = cv2.VideoCapture(i)
    ret, _ = temp_cap.read()
    if ret:
        cap = temp_cap
        break
    else:
        temp_cap.release()

dossier_travail = r"C:\Users\ALAEFAABE2025\Desktop\CODES PROJET ROBOT\calibration_camera"
chemin_donnees_cam = os.path.join(dossier_travail, "donnees_calibration.npz")
chemin_plan_2D = os.path.join(dossier_travail, "points_plan_2D_v2.npy")

with np.load(chemin_donnees_cam) as X: 
    mtx, dist = X['mtx'], X['dist']

ret, frame_test = cap.read()
h, w = frame_test.shape[:2]
newcameramtx, _ = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h), 1, (w,h))

pts_source = np.load(chemin_plan_2D)
pts_destination = np.float32([[0, 0], [largeur_plan, 0], [largeur_plan, hauteur_plan], [0, hauteur_plan]])
matrice_plan_2D = cv2.getPerspectiveTransform(pts_source, pts_destination)

# =====================================================================
# 4. INTERFACE TACTIQUE (CIBLAGE & ENVOI)
# =====================================================================
cible_x, cible_y = 0, 0
cible_active = False

def viser_et_envoyer(event, x, y, flags, param):
    global cible_x, cible_y, cible_active, OFFSET_X, OFFSET_Y
    
    if event == cv2.EVENT_RBUTTONDOWN:
        OFFSET_X, OFFSET_Y = x, y
        print("\n[MAJ] 🏠 BASE ROBOT DEFINIE.")

    elif event == cv2.EVENT_LBUTTONDOWN:
        cible_x, cible_y = x, y
        cible_active = True
        
        # Calcul et Inversion cinématique
        dist_mm_x = (-(x - OFFSET_X)) / ECHELLE
        dist_mm_y = (-(y - OFFSET_Y)) / ECHELLE
        
        # Envoi de l'ordre à l'Arduino
        commande_serie = f"{int(dist_mm_x)},{int(dist_mm_y)}\n"
        arduino.write(commande_serie.encode())
        print(f"🎯 ORDRE ENVOYE : X={int(dist_mm_x)}mm | Y={int(dist_mm_y)}mm")

cv2.namedWindow('Radar Javis - Arme')
cv2.setMouseCallback('Radar Javis - Arme', viser_et_envoyer)

print("\n>>> SYSTEME PRET. CLIC DROIT POUR LA BASE, CLIC GAUCHE POUR ATTAQUER. <<<")

while True:
    ret, frame = cap.read()
    if not ret: break
    
    frame_corrigee = cv2.undistort(frame, mtx, dist, None, newcameramtx)
    plan_2D = cv2.warpPerspective(frame_corrigee, matrice_plan_2D, (largeur_plan, hauteur_plan))
    
    cv2.circle(plan_2D, (OFFSET_X, OFFSET_Y), 6, (0, 0, 255), -1)
    cv2.putText(plan_2D, "BASE ROBOT", (OFFSET_X + 10, OFFSET_Y), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
    
    if cible_active:
        cv2.drawMarker(plan_2D, (cible_x, cible_y), (255, 255, 0), cv2.MARKER_CROSS, 20, 2)
        cv2.line(plan_2D, (OFFSET_X, OFFSET_Y), (cible_x, cible_y), (0, 255, 0), 1)

    cv2.imshow('Radar Javis - Arme', plan_2D)
    if cv2.waitKey(1) & 0xFF == ord('q'): break

cap.release()
cv2.destroyAllWindows()
arduino.close()