/* =====================================================================
 * CYCLE FLUIDE : SERVOMOTEUR DE PLONGÉE (Axe Z Ventouse)
 * ===================================================================== */

#include <Servo.h>

#define SERVO_PLONGEE_PIN 12  // Broche SpnEn du CNC Shield

Servo servoPlongee;

// --- PARAMÈTRES À AJUSTER ---
int angleHaut = 0;       // REMPLACE PAR TON ANGLE HAUT
int angleBas = 90;       // REMPLACE PAR TON ANGLE BAS
int vitessePlongee = 15; // Délai en ms entre chaque degré (Augmente pour ralentir)

void setup() {
  Serial.begin(115200);
  
  servoPlongee.attach(SERVO_PLONGEE_PIN);
  
  // Placement initial en position Haute
  servoPlongee.write(angleHaut);  

  Serial.println("--- SYSTEME JAVIS : Cycle Ventouse Fluide ---");
  Serial.println("Tapez 'C' pour lancer le cycle complet (Monte -> Descend)");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    
    if (cmd == 'C' || cmd == 'c') {
      Serial.println("Action : MONTEE...");
      allerAngleFluide(angleHaut);
      
      delay(1000); // Pause de 1 seconde en l'air
      
      Serial.println("Action : DESCENTE...");
      allerAngleFluide(angleBas);
      
      Serial.println("Cycle termine. En attente...");
    }
  }
}

// =====================================================================
// FONCTION DE LISSAGE DU MOUVEMENT (Évite les à-coups)
// =====================================================================
void allerAngleFluide(int angleCible) {
  int angleActuel = servoPlongee.read(); // Récupère la position actuelle du servo
  
  // Si on doit avancer (ex: de 0 vers 90)
  if (angleActuel < angleCible) {
    for (int pos = angleActuel; pos <= angleCible; pos++) {
      servoPlongee.write(pos);
      delay(vitessePlongee); 
    }
  } 
  // Si on doit reculer (ex: de 90 vers 0)
  else {
    for (int pos = angleActuel; pos >= angleCible; pos--) {
      servoPlongee.write(pos);
      delay(vitessePlongee);
    }
  }
}
