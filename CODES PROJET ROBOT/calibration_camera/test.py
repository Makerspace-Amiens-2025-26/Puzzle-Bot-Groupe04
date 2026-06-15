import cv2
import numpy as np
import os

print("--- REINITIALISATION JAVIS : ETAPE 1 (VISION PURE) ---")

# =====================================================================
# 1. PARAMETRES DE VOTRE ZONE PHYSIQUE (EN MILLIMETRES)
# =====================================================================
LARGEUR_REELLE_MM = 280
HAUTEUR_REELLE_MM = 260
ECHELLE = 2 # 2 pixels à l'écran représenteront 1 mm dans la vraie vie

largeur_plan = LARGEUR_REELLE_MM * ECHELLE # 560 pixels
hauteur_plan = HAUTEUR_REELLE_MM * ECHELLE # 520 pixels

# =====================================================================
# 2. INITIALISATION CAMERA ET LENTILLE
# =====================================================================
cap = None
for index_test in [0, 1, 2]:
    temp_cap = cv2.VideoCapture(index_test)
    ret, _ = temp_cap.read()
    if ret:
        cap = temp_cap
        print(f"✅ Camera trouvee sur l'index {index_test}")
        break
    else:
        temp_cap.release()

if cap is None:
    print("❌ ERREUR : Aucune camera detectee.")
    exit()

dossier_travail = r"C:\Users\ALAEFAABE2025\Desktop\CODES PROJET ROBOT\calibration_camera"
chemin_donnees_cam = os.path.join(dossier_travail, "donnees_calibration.npz")
chemin_plan_2D = os.path.join(dossier_travail, "points_plan_2D_v2.npy") # Nouveau fichier pour repartir à zéro

with np.load(chemin_donnees_cam) as X: 
    mtx, dist = X['mtx'], X['dist']

ret, frame_test = cap.read()
h, w = frame_test.shape[:2]
newcameramtx, _ = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h), 1, (w,h))

# =====================================================================
# 3. RECALIBRATION DES 4 COINS (A, B, C, D)
# =====================================================================
points_cliques = []

def capture_4_coins(event, x, y, flags, param):
    global points_cliques
    if event == cv2.EVENT_LBUTTONDOWN and len(points_cliques) < 4:
        points_cliques.append((x, y))
        print(f"Point {len(points_cliques)}/4 valide : ({x}, {y})")

def definir_nouveau_plan():
    global points_cliques
    points_cliques = []
    print("\n>>> CLIQUEZ SUR LES 4 COINS DE VOTRE ZONE 28x26cm <<<")
    print("Ordre : Haut-Gauche -> Haut-Droit -> Bas-Droit -> Bas-Gauche")
    
    cv2.namedWindow('Calibration Zone')
    cv2.setMouseCallback('Calibration Zone', capture_4_coins)

    while len(points_cliques) < 4:
        ret, frame = cap.read()
        frame_corrigee = cv2.undistort(frame, mtx, dist, None, newcameramtx)
        
        for pt in points_cliques:
            cv2.circle(frame_corrigee, pt, 5, (0, 0, 255), -1)
            
        cv2.imshow('Calibration Zone', frame_corrigee)
        cv2.waitKey(1)

    cv2.destroyWindow('Calibration Zone')
    np.save(chemin_plan_2D, np.float32(points_cliques))
    return np.float32(points_cliques)

# Forcer la redéfinition si le fichier n'existe pas, ou si on veut recommencer
pts_source = definir_nouveau_plan()

pts_destination = np.float32([[0, 0], [largeur_plan, 0], [largeur_plan, hauteur_plan], [0, hauteur_plan]])
matrice_plan_2D = cv2.getPerspectiveTransform(pts_source, pts_destination)

# =====================================================================
# 4. AFFICHAGE DE LA NOUVELLE MAP
# =====================================================================
print("\n✅ MAP GENEREE. Appuyez sur 'Q' pour quitter.")

while True:
    ret, frame = cap.read()
    if not ret: break
    
    frame_corrigee = cv2.undistort(frame, mtx, dist, None, newcameramtx)
    plan_2D = cv2.warpPerspective(frame_corrigee, matrice_plan_2D, (largeur_plan, hauteur_plan))
    
    cv2.imshow('Radar Javis - Vraie Map', plan_2D)
    
    if cv2.waitKey(1) & 0xFF == ord('q'): break

cap.release()
cv2.destroyAllWindows()