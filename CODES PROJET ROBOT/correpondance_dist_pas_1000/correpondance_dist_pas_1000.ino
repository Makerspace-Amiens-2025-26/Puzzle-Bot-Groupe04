/* =====================================================================
 * JAVIS : OUTIL DE CALIBRATION METROLOGIQUE ABSOLUE (1000 PAS)
 * ===================================================================== */
#define EN_PIN   8
#define Y_STEP   3
#define Y_DIR    6
#define X_STEP   2
#define X_DIR    5
#define Z_STEP   4
#define Z_DIR    7

int vitesseDelay = 1500;

void setup() {
  Serial.begin(115200);
  pinMode(EN_PIN, OUTPUT);
  pinMode(Y_STEP, OUTPUT); pinMode(Y_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT); pinMode(X_DIR, OUTPUT);
  pinMode(Z_STEP, OUTPUT); pinMode(Z_DIR, OUTPUT);
  digitalWrite(EN_PIN, LOW); 
  
  Serial.println("--- JAVIS : METROLOGIE PRETE ---");
  Serial.println("Tapez 'Y' pour avancer le grand portique (Axe Y) de 1000 pas.");
  Serial.println("Tapez 'Z' pour avancer le bras (Axe X) de 1000 pas.");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    
    // Test du grand portique (Axe Y/X synchronisés)
    if (cmd == 'Y' || cmd == 'y') {
      Serial.println("TIR Y : 1000 pas en cours...");
      digitalWrite(Y_DIR, HIGH); digitalWrite(X_DIR, HIGH);
      for(int i=0; i<1000; i++) {
        digitalWrite(Y_STEP, HIGH); digitalWrite(X_STEP, HIGH); delayMicroseconds(vitesseDelay);
        digitalWrite(Y_STEP, LOW); digitalWrite(X_STEP, LOW); delayMicroseconds(vitesseDelay);
      }
      Serial.println("TIR Y : Termine. Veuillez mesurer la distance exacte au millimetre.");
    }
    
    // Test du bras transversal (Axe Z)
    else if (cmd == 'Z' || cmd == 'z') {
      Serial.println("TIR Z : 1000 pas en cours...");
      digitalWrite(Z_DIR, HIGH);
      for(int i=0; i<1000; i++) {
        digitalWrite(Z_STEP, HIGH); delayMicroseconds(vitesseDelay);
        digitalWrite(Z_STEP, LOW); delayMicroseconds(vitesseDelay);
      }
      Serial.println("TIR Z : Termine. Veuillez mesurer la distance exacte au millimetre.");
    }
  }
}