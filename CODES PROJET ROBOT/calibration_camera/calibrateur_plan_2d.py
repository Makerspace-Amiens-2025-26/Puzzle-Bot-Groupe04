import cv2
import numpy as np

# Variables globales pour la capture des clics souris
points_cliques = []

def capture_clic(event, x, y, flags, param):
    global points_cliques
    if event == cv2.EVENT_LBUTTONDOWN:
        if len(points_cliques) < 4:
            points_cliques.append((x, y))
            print(f"Point {len(points_cliques)} enregistré : ({x}, {y})")

# 1. Chargement de la matrice de calibration (tes lunettes)
chemin_donnees = r"C:\Users\ALAEFAABE2025\Desktop\CODES PROJET ROBOT\calibration_camera\donnees_calibration.npz"
with np.load(chemin_donnees) as X:
    mtx, dist = X['mtx'], X['dist']

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

# 2. Phase de définition du Plan 2D (Saisie des 4 coins)
print("--- INITIALISATION DU PLAN DE TRAVAIL ---")
print("Clique sur 4 points de ta table pour définir la zone de travail.")
print("Ordre : 1.Haut-Gauche -> 2.Haut-Droit -> 3.Bas-Droit -> 4.Bas-Gauche")

cv2.namedWindow('Definition du Plan')
cv2.setMouseCallback('Definition du Plan', capture_clic)

while len(points_cliques) < 4:
    ret, frame = cap.read()
    h, w = frame.shape[:2]
    newcameramtx, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h), 1, (w,h))
    frame_corrigee = cv2.undistort(frame, mtx, dist, None, newcameramtx)
    
    # Dessiner les points déjà cliqués
    for pt in points_cliques:
        cv2.circle(frame_corrigee, pt, 5, (0, 0, 255), -1)
        
    cv2.imshow('Definition du Plan', frame_corrigee)
    cv2.waitKey(1)

cv2.destroyWindow('Definition du Plan')

# Calcul de la matrice de transformation 2D
# On décide que notre zone de travail fera 800x600 pixels à l'écran
largeur_plan, hauteur_plan = 800, 600
pts_source = np.float32(points_cliques)
pts_destination = np.float32([[0, 0], [largeur_plan, 0], [largeur_plan, hauteur_plan], [0, hauteur_plan]])
matrice_plan_2D = cv2.getPerspectiveTransform(pts_source, pts_destination)

print("✅ Plan 2D généré. Démarrage de l'analyse en direct.")

# 3. Boucle principale d'analyse
while True:
    ret, frame = cap.read()
    
    # Correction optique (Undistortion)
    frame_corrigee = cv2.undistort(frame, mtx, dist, None, newcameramtx)
    
    # Aplatissement en Plan 2D (Perspective Warp)
    plan_2D = cv2.warpPerspective(frame_corrigee, matrice_plan_2D, (largeur_plan, hauteur_plan))
    
    # Préparation pour la détection
    gray = cv2.cvtColor(plan_2D, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)
    _, thresh = cv2.threshold(blurred, 90, 255, cv2.THRESH_BINARY_INV)
    
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    for cnt in contours:
        area = cv2.contourArea(cnt)
        
        # On ignore la poussière et les trous de la table (Surface < 400)
        if area > 400: 
            M = cv2.moments(cnt)
            if M["m00"] != 0:
                cx = int(M["m10"] / M["m00"])
                cy = int(M["m01"] / M["m00"])
            
            # FILTRE INTELLIGENT : Est-ce une pièce de puzzle ?
            # (Surface généreuse ET forme complexe)
            # Tu devras ajuster ces valeurs "1500" et "5000" selon la taille réelle de tes pièces à l'écran
            is_puzzle_piece = 1500 < area < 5000
            
            if is_puzzle_piece:
                # C'est une pièce ! Contour VERT et point ROUGE
                cv2.drawContours(plan_2D, [cnt], -1, (0, 255, 0), 2)
                cv2.circle(plan_2D, (cx, cy), 5, (0, 0, 255), -1)
                cv2.putText(plan_2D, f"PIECE X:{cx} Y:{cy}", (cx - 40, cy - 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
            else:
                # C'est un autre objet (Main, Outil, etc.) Contour ROUGE et texte BLEU
                x, y, w_obj, h_obj = cv2.boundingRect(cnt)
                cv2.rectangle(plan_2D, (x, y), (x+w_obj, y+h_obj), (0, 0, 255), 1)
                cv2.putText(plan_2D, f"Obj X:{cx} Y:{cy}", (cx - 30, cy - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.4, (255, 0, 0), 1)

    cv2.imshow('Radar Puzzle-Bot (Plan 2D Euclidien)', plan_2D)

    if cv2.waitKey(1) == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()