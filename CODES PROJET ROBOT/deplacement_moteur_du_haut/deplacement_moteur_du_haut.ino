/* =====================================================================
 * TEST UNITAIRE : BRAS COULISSANT TRANSVERSAL (Axe Z) - MANUEL + CAPTEUR
 * ===================================================================== */

#define EN_PIN      8

// Moteur du bras coulissant (Emplacement Z du Shield)
#define Z_STEP      4
#define Z_DIR       7

// Capteur de fin de course du bras coulissant
#define Z_LIMIT_PIN 11 

// Paramètres de mouvement
int vitesseDelay = 1200; // Vitesse régulée
int nbPasTest = 3000;    // Nombre de pas par commande

void setup() {
  Serial.begin(115200);
  
  pinMode(EN_PIN, OUTPUT);
  pinMode(Z_STEP, OUTPUT);
  pinMode(Z_DIR, OUTPUT);
  
  // Configuration du capteur avec résistance interne
  pinMode(Z_LIMIT_PIN, INPUT_PULLUP);

  digitalWrite(EN_PIN, LOW); // Activation des drivers
  
  Serial.println("--- SYSTEME ACTIF : Axe Transversal + Securite ---");
  Serial.println("Tapez 'A' pour Avancer, 'R' pour Reculer.");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();  
    
    if (cmd == 'a' || cmd == 'A') {
      Serial.println("Mouvement : AVANT. Surveillance capteur active.");
      bougerMoteur(nbPasTest, HIGH); 
    } 
    else if (cmd == 'r' || cmd == 'R') {
      Serial.println("Mouvement : ARRIERE. Surveillance capteur active.");
      bougerMoteur(nbPasTest, LOW);  
    }
  }
}

// Fonction de mouvement avec vérification du capteur à chaque pas
void bougerMoteur(int nbPas, int sens) {
  digitalWrite(Z_DIR, sens);

  for (int i = 0; i < nbPas; i++) {
    
    // VERIFICATION DU CAPTEUR DU BRAS
    if (digitalRead(Z_LIMIT_PIN) == LOW) {
      Serial.println("!!! ARRET D'URGENCE BRAS : Capteur touche !!!");
      break; // Sortie immédiate de la boucle, le moteur s'arrête
    }

    digitalWrite(Z_STEP, HIGH);
    delayMicroseconds(vitesseDelay); 
    digitalWrite(Z_STEP, LOW);
    delayMicroseconds(vitesseDelay);
  }
  
  Serial.println("Position atteinte. En attente d'instruction...");
}