/* =====================================================================
 * TEST UNITAIRE : PORTIQUE (BASE CONSERVEE) + BRAS TRANSVERSAL (Z)
 * ===================================================================== */

#define EN_PIN   8

// Moteur Gauche (Emplacement Y)
#define Y_STEP   3
#define Y_DIR    6

// Moteur Droit (Branché sur l'emplacement X en dépannage)
#define X_STEP   2
#define X_DIR    5

// Bras Transversal (Emplacement Z)
#define Z_STEP   4
#define Z_DIR    7

int vitesseDelay = 900; // Vitesse mesurée pour le portique bas (Y/X)
int vitesseBras = 900; // Vitesse pour le bras du haut (Z)

void setup() {
  Serial.begin(115200);
  Serial.println("--- SYSTEME JAVIS PRET : Mouvements Manuels ---");
  Serial.println("Tapez 'Y' : Cycle Avance/Recule du portique (Y+X)");
  Serial.println("Tapez 'Z' : Cycle Avance/Recule du bras (Z)");
  Serial.println("Tapez '3' : Mouvement simultane (Diagonale)");

  pinMode(EN_PIN, OUTPUT);
  pinMode(Y_STEP, OUTPUT); pinMode(Y_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT); pinMode(X_DIR, OUTPUT);
  pinMode(Z_STEP, OUTPUT); pinMode(Z_DIR, OUTPUT);

  digitalWrite(EN_PIN, LOW); // Activation des drivers
}

void loop() {
  if (Serial.available() > 0) {
    char commande = Serial.read();

    if (commande == 'Y' || commande == 'y') {
      Serial.println("Portique : Avance (1400 pas)...");
      bougerDeuxMoteurs(1350, HIGH); 
      
      delay(1300);
      
      Serial.println("Portique : Recule (1400 pas)...");
      bougerDeuxMoteurs(1350, LOW);
    }
    else if (commande == 'Z' || commande == 'z') {
      Serial.println("Bras : Avance (1500 pas)...");
      bougerBras(1690, HIGH); 
      
      delay(1300);
      
      Serial.println("Bras : Recule (1350 pas)...");
      bougerBras(1690, LOW);
    }
    else if (commande == '3') {
      Serial.println("Diagonale : Avance simultanee...");
      bougerDiagonale(1300, HIGH, HIGH); 
      
      delay(1300);
      
      Serial.println("Diagonale : Recule simultanee...");
      bougerDiagonale(1300, LOW, LOW);
    }
  }
}

// =====================================================================
// VOTRE FONCTION DE BASE EXACTE CONSERVEE (Y et X)
// =====================================================================
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

// =====================================================================
// FONCTION POUR LE BRAS SEUL (Z)
// =====================================================================
void bougerBras(int nbPas, int sens) {
  digitalWrite(Z_DIR, sens);
  
  for (int i = 0; i < nbPas; i++) {
    digitalWrite(Z_STEP, HIGH);
    delayMicroseconds(vitesseBras); 
    digitalWrite(Z_STEP, LOW);
    delayMicroseconds(vitesseBras);
  }
}

// =====================================================================
// FONCTION SIMULTANEE (Y, X et Z)
// =====================================================================
void bougerDiagonale(int nbPas, int sensPortique, int sensBras) {
  // Application de votre logique de direction pour le portique
  digitalWrite(Y_DIR, sensPortique);
  if (sensPortique == HIGH) {
    digitalWrite(X_DIR, HIGH); 
  } else {
    digitalWrite(X_DIR, LOW);
  } 
  
  // Direction pour le bras
  digitalWrite(Z_DIR, sensBras);

  for (int i = 0; i < nbPas; i++) {
    digitalWrite(Y_STEP, HIGH);
    digitalWrite(X_STEP, HIGH);
    digitalWrite(Z_STEP, HIGH);
    
    // On utilise la vitesse du portique pour synchroniser tout le monde
    delayMicroseconds(vitesseDelay); 
    
    digitalWrite(Y_STEP, LOW);
    digitalWrite(X_STEP, LOW);
    digitalWrite(Z_STEP, LOW);
    
    delayMicroseconds(vitesseDelay);
  }
}
