import cv2
import numpy as np
import os

print("--- REINITIALISATION JAVIS : ETAPE 2 (TEST MILLIMETRIQUE) ---")

# =====================================================================
# 1. PARAMETRES DE LA MAP
# =====================================================================
LARGEUR_REELLE_MM = 280
HAUTEUR_REELLE_MM = 260
ECHELLE = 2

largeur_plan = LARGEUR_REELLE_MM * ECHELLE 
hauteur_plan = HAUTEUR_REELLE_MM * ECHELLE 

# On définit le "Home" au centre exact de votre zone de 28x26cm
OFFSET_X = largeur_plan // 2
OFFSET_Y = hauteur_plan // 2

# =====================================================================
# 2. INITIALISATION CAMERA
# =====================================================================
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

dossier_travail = r"C:\Users\ALAEFAABE2025\Desktop\CODES PROJET ROBOT\calibration_camera"
chemin_donnees_cam = os.path.join(dossier_travail, "donnees_calibration.npz")
chemin_plan_2D = os.path.join(dossier_travail, "points_plan_2D_v2.npy") # Votre nouvelle map !

with np.load(chemin_donnees_cam) as X: 
    mtx, dist = X['mtx'], X['dist']

ret, frame_test = cap.read()
h, w = frame_test.shape[:2]
newcameramtx, _ = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h), 1, (w,h))

if not os.path.exists(chemin_plan_2D):
    print("❌ ERREUR : Fichier map introuvable. Refaites l'étape 1.")
    exit()

pts_source = np.load(chemin_plan_2D)
pts_destination = np.float32([[0, 0], [largeur_plan, 0], [largeur_plan, hauteur_plan], [0, hauteur_plan]])
matrice_plan_2D = cv2.getPerspectiveTransform(pts_source, pts_destination)

# =====================================================================
# 3. LE SIMULATEUR DE CLIC
# =====================================================================
cible_x, cible_y = 0, 0
cible_active = False

def viser_et_simuler(event, x, y, flags, param):
    global cible_x, cible_y, cible_active
    if event == cv2.EVENT_LBUTTONDOWN:
        cible_x, cible_y = x, y
        cible_active = True
        
        # Calcul de la distance en pixels depuis le centre
        dist_px_x = x - OFFSET_X
        dist_px_y = y - OFFSET_Y
        
        # Inversion (pour corriger le sens de votre caméra)
        dist_px_x = -dist_px_x
        dist_px_y = -dist_px_y
        
        # Conversion absolue en millimètres
        dist_mm_x = dist_px_x / ECHELLE
        dist_mm_y = dist_px_y / ECHELLE
        
        print("\n=================================================")
        print(f"🎯 SIMULATION DE CLIC :")
        print(f" -> Ordre Axe X (Bras) : {int(dist_mm_x)} mm")
        print(f" -> Ordre Axe Y (Portique) : {int(dist_mm_y)} mm")
        print("=================================================")

cv2.namedWindow('Radar Javis - Simulation')
cv2.setMouseCallback('Radar Javis - Simulation', viser_et_simuler)

print("\n>>> MAP CHARGEE. CLIQUEZ POUR TESTER LES DISTANCES. <<<")

while True:
    ret, frame = cap.read()
    if not ret: break
    
    frame_corrigee = cv2.undistort(frame, mtx, dist, None, newcameramtx)
    plan_2D = cv2.warpPerspective(frame_corrigee, matrice_plan_2D, (largeur_plan, hauteur_plan))
    
    # Dessin du centre (Home)
    cv2.circle(plan_2D, (OFFSET_X, OFFSET_Y), 6, (0, 0, 255), -1)
    cv2.putText(plan_2D, "HOME", (OFFSET_X + 10, OFFSET_Y), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
    
    if cible_active:
        cv2.drawMarker(plan_2D, (cible_x, cible_y), (255, 255, 0), cv2.MARKER_CROSS, 20, 2)

    cv2.imshow('Radar Javis - Simulation', plan_2D)
    
    if cv2.waitKey(1) & 0xFF == ord('q'): break

cap.release()
cv2.destroyAllWindows()