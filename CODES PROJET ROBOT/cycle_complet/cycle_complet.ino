/* =====================================================================
 * SYSTEME JAVIS : SEQUENCE AUTOMATIQUE COMPLETE (STEPPERS + SERVO)
 * ===================================================================== */

#include <Servo.h>

// --- BROCHES MOTEURS PAS-A-PAS ---
#define EN_PIN   8
#define Y_STEP   3
#define Y_DIR    6
#define X_STEP   2
#define X_DIR    5
#define Z_STEP   4
#define Z_DIR    7

// --- BROCHE SERVOMOTEUR ---
#define SERVO_PLONGEE_PIN 12

// --- PARAMETRES DE VITESSE ET ANGLES ---
int vitesseDelay = 900;  // Vitesse Portique (Y/X)
int vitesseBras = 900;   // Vitesse Bras (Z)

int angleHaut = 180;     // Position de sécurité (Levée)
int angleBas = 0;        // Position d'action sur la table (Baissée)
int vitessePlongee = 3;  // TRÈS RAPIDE (3ms au lieu de 15ms) pour plus de punch

Servo servoPlongee;

void setup() {
  Serial.begin(115200);
  
  // Initialisation Steppers
  pinMode(EN_PIN, OUTPUT);
  pinMode(Y_STEP, OUTPUT); pinMode(Y_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT); pinMode(X_DIR, OUTPUT);
  pinMode(Z_STEP, OUTPUT); pinMode(Z_DIR, OUTPUT);
  digitalWrite(EN_PIN, LOW); 

  // Initialisation Servo
  servoPlongee.attach(SERVO_PLONGEE_PIN);
  servoPlongee.write(angleHaut); // On démarre en sécurité (en l'air)

  Serial.println("--- SYSTEME JAVIS PRET : Mode Automatique ---");
  Serial.println("Tapez 'A' pour lancer la simulation complete de la trajectoire.");
}

void loop() {
  if (Serial.available() > 0) {
    char commande = Serial.read();

    if (commande == 'A' || commande == 'a') {
      Serial.println("\n>>> DEMARRAGE SEQUENCE AUTOMATIQUE <<<");
      
      // 1. Rails du bas (Y/X)
      Serial.println("Etape 1 : Portique bas...");
      bougerDeuxMoteurs(1200, HIGH); 
      delay(500);
      bougerDeuxMoteurs(1200, LOW);
      delay(1000);

      // 2. Rail du haut (Z transversal)
      Serial.println("Etape 2 : Bras transversal...");
      bougerBras(1490, HIGH); 
      delay(500);
      bougerBras(1490, LOW);
      delay(1000);

      // 3. Les deux en même temps (Diagonale pure)
      Serial.println("Etape 3 : Diagonale simultanee...");
      bougerDiagonale(1250, HIGH, HIGH); 
      delay(500);
      bougerDiagonale(1250, LOW, LOW);
      delay(1000);

      // 4. Le combo final : Déplacement -> Plongée -> Levée -> Retour
      Serial.println("Etape 4 : ASSAUT COMPLET (Diagonale + Servo)...");
      bougerDiagonale(1250, HIGH, HIGH);  // Va vers la cible
      delay(300); // Petit temps de stabilisation
      
      Serial.println("   -> Descente rapide !");
      allerAngleFluide(angleBas);         // Frappe la pièce
      delay(800); // Simulation d'aspiration de la ventouse
      
      Serial.println("   -> Remontee rapide !");
      allerAngleFluide(angleHaut);        // Remonte la pièce
      delay(300);
      
      bougerDiagonale(1250, LOW, LOW);    // Retourne à la base avec la pièce
      
      Serial.println(">>> SEQUENCE TERMINEE <<<");
    }
  }
}

// =====================================================================
// FONCTIONS MOTEURS PAS-A-PAS
// =====================================================================
void bougerDeuxMoteurs(int nbPas, int sens) {
  digitalWrite(Y_DIR, sens);
  if (sens == HIGH) { digitalWrite(X_DIR, HIGH); } 
  else { digitalWrite(X_DIR, LOW); } 
  
  for (int i = 0; i < nbPas; i++) {
    digitalWrite(Y_STEP, HIGH); digitalWrite(X_STEP, HIGH);
    delayMicroseconds(vitesseDelay); 
    digitalWrite(Y_STEP, LOW); digitalWrite(X_STEP, LOW);
    delayMicroseconds(vitesseDelay);
  }
}

void bougerBras(int nbPas, int sens) {
  digitalWrite(Z_DIR, sens);
  for (int i = 0; i < nbPas; i++) {
    digitalWrite(Z_STEP, HIGH); delayMicroseconds(vitesseBras); 
    digitalWrite(Z_STEP, LOW); delayMicroseconds(vitesseBras);
  }
}

void bougerDiagonale(int nbPas, int sensPortique, int sensBras) {
  digitalWrite(Y_DIR, sensPortique);
  if (sensPortique == HIGH) { digitalWrite(X_DIR, HIGH); } 
  else { digitalWrite(X_DIR, LOW); } 
  digitalWrite(Z_DIR, sensBras);

  for (int i = 0; i < nbPas; i++) {
    digitalWrite(Y_STEP, HIGH); digitalWrite(X_STEP, HIGH); digitalWrite(Z_STEP, HIGH);
    delayMicroseconds(vitesseDelay); 
    digitalWrite(Y_STEP, LOW); digitalWrite(X_STEP, LOW); digitalWrite(Z_STEP, LOW);
    delayMicroseconds(vitesseDelay);
  }
}

// =====================================================================
// FONCTION SERVOMOTEUR PUNCHY
// =====================================================================
void allerAngleFluide(int angleCible) {
  int angleActuel = servoPlongee.read(); 
  if (angleActuel < angleCible) {
    for (int pos = angleActuel; pos <= angleCible; pos++) {
      servoPlongee.write(pos);
      delay(vitessePlongee); // Très rapide
    }
  } else {
    for (int pos = angleActuel; pos >= angleCible; pos--) {
      servoPlongee.write(pos);
      delay(vitessePlongee); // Très rapide
    }
  }
}
