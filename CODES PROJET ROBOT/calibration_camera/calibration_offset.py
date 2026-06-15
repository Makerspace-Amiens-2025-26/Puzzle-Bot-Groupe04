import cv2
import numpy as np
import os

print("--- CALIBRATION ETAPE 2 : MESURE DE L'OFFSET ---")

# --- CONFIGURATION DE LA CAMERA ---
cap = None
for index_test in [0, 1, 2]:
    temp_cap = cv2.VideoCapture(index_test)
    ret, _ = temp_cap.read()
    if ret:
        cap = temp_cap
        break
    else:
        temp_cap.release()

if cap is None:
    print("❌ ERREUR : Aucune camera detectee.")
    exit()

# --- CHARGEMENT DE LA GEOMETRIE ---
dossier_travail = r"C:\Users\ALAEFAABE2025\Desktop\CODES PROJET ROBOT\calibration_camera"
chemin_donnees_cam = os.path.join(dossier_travail, "donnees_calibration.npz")
chemin_plan_2D = os.path.join(dossier_travail, "points_plan_2D.npy")

largeur_plan, hauteur_plan = 1280, 720

with np.load(chemin_donnees_cam) as X: 
    mtx, dist = X['mtx'], X['dist']

ret, frame_test = cap.read()
h, w = frame_test.shape[:2]
newcameramtx, _ = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h), 1, (w,h))

pts_source = np.load(chemin_plan_2D)
pts_destination = np.float32([[0, 0], [largeur_plan, 0], [largeur_plan, hauteur_plan], [0, hauteur_plan]])
matrice_plan_2D = cv2.getPerspectiveTransform(pts_source, pts_destination)

# --- CAPTURE DU CLIC ---
def recuperer_coordonnees(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        print("\n=============================================")
        print(f"🎯 VOICI VOTRE POINT ZERO (A me communiquer) :")
        print(f"PIXEL X = {x}")
        print(f"PIXEL Y = {y}")
        print("=============================================\n")
        
        cv2.circle(plan_2D, (x, y), 5, (0, 0, 255), -1)
        cv2.imshow('Calibration Offset', plan_2D)

cv2.namedWindow('Calibration Offset')
cv2.setMouseCallback('Calibration Offset', recuperer_coordonnees)

print(">>> CLIQUEZ SUR LA CROIX SUR LA TABLE. <<<")

while True:
    ret, frame = cap.read()
    if not ret: break
    
    frame_corrigee = cv2.undistort(frame, mtx, dist, None, newcameramtx)
    plan_2D = cv2.warpPerspective(frame_corrigee, matrice_plan_2D, (largeur_plan, hauteur_plan))
    
    cv2.imshow('Calibration Offset', plan_2D)
    
    if cv2.waitKey(1) & 0xFF == ord('q'): 
        break

cap.release()
cv2.destroyAllWindows()