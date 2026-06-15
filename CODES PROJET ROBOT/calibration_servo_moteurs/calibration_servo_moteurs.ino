/* =====================================================================
 * TEST UNITAIRE : TÊTE DE PRÉHENSION (PLONGÉE + ROTATION)
 * ===================================================================== */
#include <Servo.h>

#define SERVO_PLONGEE_PIN  12  // Broche SpnEn : Montée/Descente
#define SERVO_ROTATION_PIN 13  // Broche SpnDir : Rotation de la pièce

Servo servoPlongee;
Servo servoRotation;

void setup() {
  Serial.begin(115200);
  
  servoPlongee.attach(SERVO_PLONGEE_PIN);
  servoRotation.attach(SERVO_ROTATION_PIN);
  
  // Positions de sécurité au démarrage
  servoPlongee.write(180); // 180 = Ventouse en haut
  servoRotation.write(90); // 90 = Position neutre au centre

  Serial.println("--- JAVIS : TEST TETE DE PREHENSION ---");
  Serial.println("Commandes :");
  Serial.println("- Tapez P suivi de l'angle (ex: P0 ou P180) pour la Plongee");
  Serial.println("- Tapez R suivi de l'angle (ex: R45 ou R135) pour la Rotation");
}

void loop() {
  if (Serial.available() > 0) {
    char moteur = Serial.read(); // Lit 'P' ou 'R'
    delay(10); // Laisse le temps aux chiffres d'arriver dans le buffer
    
    if (moteur == 'P' || moteur == 'p' || moteur == 'R' || moteur == 'r') {
      int angle = Serial.parseInt(); // Lit le nombre qui suit la lettre
      
      // Nettoyage du buffer pour éviter les bugs de saut de ligne
      while(Serial.available() > 0) { Serial.read(); }
      
      // Sécurité anti-casse mécanique
      if (angle >= 0 && angle <= 180) {
        if (moteur == 'P' || moteur == 'p') {
          Serial.print("Action : Plongee (Z) -> "); Serial.println(angle);
          servoPlongee.write(angle);
        } else {
          Serial.print("Action : Rotation -> "); Serial.println(angle);
          servoRotation.write(angle);
        }
      } else {
        Serial.println("Erreur : L'angle doit etre compris entre 0 et 180.");
      }
    }
  }
}