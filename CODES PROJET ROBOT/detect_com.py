import cv2

print("--- JAVIS : SCAN DES CAMERAS EN COURS ---")

for index in range(5):
    cap = cv2.VideoCapture(index, cv2.CAP_DSHOW)
    if cap.isOpened():
        ret, frame = cap.read()
        if ret:
            print(f"✅ Caméra détectée sur l'Index : {index}")
            # Affiche une petite fenêtre pour que tu voies quelle caméra c'est
            cv2.imshow(f"Camera Index {index}", frame)
        cap.release()
    else:
        print(f"❌ Pas de caméra sur l'Index : {index}")

print("\nRegarde les fenêtres qui se sont ouvertes pour identifier ta caméra.")
print("Appuie sur n'importe quelle touche sur l'une des fenêtres vidéo pour fermer.")
cv2.waitKey(0)
cv2.destroyAllWindows()