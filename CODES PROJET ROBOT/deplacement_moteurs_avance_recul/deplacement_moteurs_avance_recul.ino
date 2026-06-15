/* =====================================================================
 * TEST UNITAIRE : DOUBLE MOTEUR (CLONAGE LOGICIEL Y + X)
 * On utilise l'emplacement X car le A semble défectueux.
 * ===================================================================== */

#define EN_PIN   8

// Moteur Gauche (Emplacement Y)
#define Y_STEP   3
#define Y_DIR    6

// Moteur Droit (Branché sur l'emplacement X en dépannage)
#define X_STEP   2
#define X_DIR    5

int vitesseDelay = 900; // Vitesse (microsecondes)

void setup() {
  Serial.begin(115200);
  Serial.println("--- Test Clonage Logiciel (Y + X) ---");
  Serial.println("Tapez 'Y' pour faire avancer le Yportique.");

  pinMode(EN_PIN, OUTPUT);
  pinMode(Y_STEP, OUTPUT);
  pinMode(Y_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT);
  pinMode(X_DIR, OUTPUT);

  digitalWrite(EN_PIN, LOW); // Activation des drivers
}

void loop() {
  if (Serial.available() > 0) {
    char commande = Serial.read();

    if (commande == 'Y' || commande == 'y') {
      Serial.println("Avance (1200 pas)...");
      bougerDeuxMoteurs(1200, HIGH); 
      
      delay(1000);
      
      Serial.println("Recule (1200 pas)...");
      bougerDeuxMoteurs(1200, LOW);
    }
  }
}

// Fonction pour piloter Y et X en parfaite synchronisation
void bougerDeuxMoteurs(int nbPas, int sens) {
  // 1. On donne la direction
digitalWrite(Y_DIR, sens);

// Si Y est HIGH, X sera LOW, et inversement
if (sens == HIGH) {
  digitalWrite(X_DIR, HIGH); 
} else {
  digitalWrite(X_DIR, LOW);
} 
  
// 2. On envoie les impulsions simultanément
  for (int i = 0; i < nbPas; i++) {
    digitalWrite(Y_STEP, HIGH);
    digitalWrite(X_STEP, HIGH);
    
    delayMicroseconds(vitesseDelay); 
    
    digitalWrite(Y_STEP, LOW);
    digitalWrite(X_STEP, LOW);
    
    delayMicroseconds(vitesseDelay);
  }
}