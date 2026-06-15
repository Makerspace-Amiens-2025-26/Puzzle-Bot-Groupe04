/* =====================================================================
 * TEST UNITAIRE : PORTIQUE SECURISÉ 
 * Inversion logicielle du moteur droit (X) + Arrêt d'urgence (Endstop)
 * ===================================================================== */

#define EN_PIN      8

// Moteur Gauche (Emplacement Y)
#define Y_STEP      3
#define Y_DIR       6

// Moteur Droit (Branché sur l'emplacement X en dépannage)
#define X_STEP      2
#define X_DIR       5

// Pins des Endstops sur CNC Shield V3 (Arduino Uno)
#define Y_LIMIT_PIN 10 // Le pin de l'axe Y sur le shield est le 10

int vitesseDelay = 100; // Vitesse lente pour les tests de sécurité

void setup() {
  Serial.begin(115200);
  pinMode(EN_PIN, OUTPUT);
  pinMode(Y_STEP, OUTPUT);
  pinMode(Y_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT);
  pinMode(X_DIR, OUTPUT);
  
  // Configuration du capteur avec résistance interne
  pinMode(Y_LIMIT_PIN, INPUT_PULLUP);

  digitalWrite(EN_PIN, LOW); // Activation des drivers
  Serial.println("--- Systeme pret ---");
  Serial.println("Appuyez sur Y pour avancer vers le capteur.");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();  
    if (cmd == 'y' || cmd == 'Y') {
      Serial.println("Mouvement en cours... Surveillance capteur active.");
      // On lance un long mouvement pour avoir le temps de tester le capteur
      bougerAvecSecurite(5000, HIGH); 
    }
  }
}

// Fonction unifiée : Inversion Moteur + Capteur
void bougerAvecSecurite(int nbPas, int sens) {
  
  // 1. On donne la direction avec l'inversion logicielle pour le moteur droit
  digitalWrite(Y_DIR, sens);
  
  // Si Y avance (HIGH), on force X à reculer (LOW) pour que le portique aille droit
  if (sens == HIGH) {
    digitalWrite(X_DIR, LOW); 
  } else {
    digitalWrite(X_DIR, HIGH);
  }

  // 2. On envoie les impulsions avec surveillance du capteur à chaque pas
  for (int i = 0; i < nbPas; i++) {
    
    // VERIFICATION DU CAPTEUR (LOW = Appuyé si cablé en NC ou avec Pullup)
    if (digitalRead(Y_LIMIT_PIN) == LOW) {
      Serial.println("!!! ARRET D'URGENCE : Capteur touche !!!");
      break; // Le "break" stoppe immédiatement la boucle for, les moteurs s'arrêtent
    }

    digitalWrite(Y_STEP, HIGH);
    digitalWrite(X_STEP, HIGH);
    
    delayMicroseconds(vitesseDelay); 
    
    digitalWrite(Y_STEP, LOW);
    digitalWrite(X_STEP, LOW);
    
    delayMicroseconds(vitesseDelay);
  }
}