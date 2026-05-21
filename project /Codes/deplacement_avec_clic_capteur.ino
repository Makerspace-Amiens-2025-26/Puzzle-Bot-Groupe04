#define EN_PIN      8
#define Y_STEP      3
#define Y_DIR       6
#define X_STEP      2
#define X_DIR       5

// Pins des Endstops sur CNC Shield V3 (Arduino Uno)
#define Y_LIMIT_PIN 10 // Le pin de l'axe Y sur le shield est le 10

int vitesseDelay = 1500; // Vitesse plus lente pour les tests de sécurité

void setup() {
  Serial.begin(115200);
  pinMode(EN_PIN, OUTPUT);
  pinMode(Y_STEP, OUTPUT);
  pinMode(Y_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT);
  pinMode(X_DIR, OUTPUT);
  
  // Configuration du capteur avec résistance interne
  pinMode(Y_LIMIT_PIN, INPUT_PULLUP);

  digitalWrite(EN_PIN, LOW); 
  Serial.println("Systeme pret. Appuyez sur Y pour bouger.");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();  
    if (cmd == 'y' || cmd == 'Y') {
      Serial.println("Mouvement en cours... Surveillance capteur active.");
      bougerAvecSecurite(2000, HIGH); 
    }
  }
}

void bougerAvecSecurite(int nbPas, int sens) {
  digitalWrite(Y_DIR, sens);
  digitalWrite(X_DIR, sens);

  for (int i = 0; i < nbPas; i++) {
    // VERIFICATION DU CAPTEUR (LOW = Appuyé si cablé en NC)
    if (digitalRead(Y_LIMIT_PIN) == LOW) {
      Serial.println("!!! ARRET D'URGENCE : Capteur touche !!!");
      break; // On sort immédiatement de la boucle for
    }

    digitalWrite(Y_STEP, HIGH);
    digitalWrite(X_STEP, HIGH);
    delayMicroseconds(vitesseDelay);
    digitalWrite(Y_STEP, LOW);
    digitalWrite(X_STEP, LOW);
    delayMicroseconds(vitesseDelay);
  }
}