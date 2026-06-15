import cv2

# Initialisation de la caméra. 
# Le chiffre '0' cible la première caméra branchée. 
# Si tu es sur un ordinateur portable avec une webcam intégrée, il faudra peut-être mettre '1' ou '2'.
cap = cv2.VideoCapture(0)

# Vérification de la connexion
if not cap.isOpened():
    print("Erreur : Impossible de trouver ou d'ouvrir la caméra DFROBOT.")
    exit()

print("Caméra connectée ! Appuie sur la touche 'q' de ton clavier pour fermer la fenêtre.")

# Boucle infinie pour lire la vidéo image par image
while True:
    # Capture de la frame (l'image à l'instant T)
    ret, frame = cap.read()

    if not ret:
        print("Erreur : Coupure du flux vidéo.")
        break

    # Affichage de l'image dans une fenêtre nommée 'Vue du Puzzle-Bot'
    cv2.imshow('Vue du Puzzle-Bot', frame)

    # Condition d'arrêt : Si on appuie sur la touche 'q', on casse la boucle
    if cv2.waitKey(1) == ord('q'):
        break

# Extinction proprement et nettoyage de la mémoire
cap.release()
cv2.destroyAllWindows()