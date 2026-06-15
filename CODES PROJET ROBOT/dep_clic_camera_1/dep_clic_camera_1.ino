/* =====================================================================
 * FIRMWARE ARDUINO : EXECUTION METROLOGIQUE FINALE
 * ===================================================================== */
#include <Servo.h>

#define EN_PIN   8
#define Y_STEP   3
#define Y_DIR    6
#define X_STEP   2
#define X_DIR    5
#define Z_STEP   4
#define Z_DIR    7
#define Y_LIMIT_PIN 10 
#define Z_LIMIT_PIN 11 
#define SERVO_PLONGEE_PIN 12

Servo servoPlongee;
int vitesseDelay = 1200; 

// --- LES RATIOS CALCULES PAR METROLOGIE ---
float pas_par_mm_X = 3.45; // Bras transversal (Z_STEP)
float pas_par_mm_Y = 4.88; // Grand portique (Y_STEP / X_STEP)

// --- LES LIMITES PHYSIQUES ABSOLUES (En millimètres) ---
long MAX_COURSE_X_MM = 450; 
long MAX_COURSE_Y_MM = 370; 

void setup() {
  Serial.begin(115200);
  pinMode(EN_PIN, OUTPUT);
  pinMode(Y_STEP, OUTPUT); pinMode(Y_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT); pinMode(X_DIR, OUTPUT);
  pinMode(Z_STEP, OUTPUT); pinMode(Z_DIR, OUTPUT);
  
  pinMode(Y_LIMIT_PIN, INPUT_PULLUP);
  pinMode(Z_LIMIT_PIN, INPUT_PULLUP);
  digitalWrite(EN_PIN, LOW); 
  
  servoPlongee.attach(SERVO_PLONGEE_PIN);
  servoPlongee.write(180); 
  Serial.println("--- FIRMWARE MUSCULAIRE OPERATIONNEL ---");
}

void loop() {
  if (Serial.available() > 0) {
    String chaineEntrante = Serial.readStringUntil('\n');
    int separateur = chaineEntrante.indexOf(',');
    
    if (separateur > 0) {
      long dist_mm_X = chaineEntrante.substring(0, separateur).toInt();
      long dist_mm_Y = chaineEntrante.substring(separateur + 1).toInt();
      
      // Sécurité anti-crash
      if (abs(dist_mm_X) > MAX_COURSE_X_MM) dist_mm_X = (dist_mm_X > 0) ? MAX_COURSE_X_MM : -MAX_COURSE_X_MM;
      if (abs(dist_mm_Y) > MAX_COURSE_Y_MM) dist_mm_Y = (dist_mm_Y > 0) ? MAX_COURSE_Y_MM : -MAX_COURSE_Y_MM;

      // CONVERSION PARFAITE
      long pasZ_Transversal = abs(dist_mm_X) * pas_par_mm_X;
      long pasY_Portique = abs(dist_mm_Y) * pas_par_mm_Y;

      // Note : Si un axe part dans le mauvais sens, inverser HIGH et LOW ici
      int sensAllerZ = (dist_mm_X >= 0) ? HIGH : LOW;
      int sensRetourZ = (dist_mm_X >= 0) ? LOW : HIGH;
      
      int sensAllerY = (dist_mm_Y >= 0) ? HIGH : LOW;
      int sensRetourY = (dist_mm_Y >= 0) ? LOW : HIGH;
      
      Serial.print("Assaut lance : "); Serial.print(pasY_Portique); 
      Serial.print(" pas Y | "); Serial.print(pasZ_Transversal); Serial.println(" pas X");

      bool trajetReussi = bougerDiagonale(pasY_Portique, pasZ_Transversal, sensAllerY, sensAllerZ);
      delay(400); 

      if (trajetReussi) {
        servoPlongee.write(0);   
        delay(1000);             
        servoPlongee.write(180); 
        delay(400);
      } else {
        Serial.println("! ANNULATION : Capteur d'arret percute !");
      }

      bougerDiagonale(pasY_Portique, pasZ_Transversal, sensRetourY, sensRetourZ);
    }
  }
}

bool bougerDiagonale(long pasPortique, long pasBras, int sensPortique, int sensBras) {
  digitalWrite(Y_DIR, sensPortique);
  if (sensPortique == HIGH) { digitalWrite(X_DIR, HIGH); } else { digitalWrite(X_DIR, LOW); } 
  digitalWrite(Z_DIR, sensBras);

  long maxPas = max(pasPortique, pasBras);

  for (long i = 0; i < maxPas; i++) {
    // Si un capteur est percuté, arrêt d'urgence
    if (digitalRead(Y_LIMIT_PIN) == LOW || digitalRead(Z_LIMIT_PIN) == LOW) return false;

    if (i < pasPortique) { digitalWrite(Y_STEP, HIGH); digitalWrite(X_STEP, HIGH); }
    if (i < pasBras) { digitalWrite(Z_STEP, HIGH); }
    
    delayMicroseconds(vitesseDelay); 
    
    if (i < pasPortique) { digitalWrite(Y_STEP, LOW); digitalWrite(X_STEP, LOW); }
    if (i < pasBras) { digitalWrite(Z_STEP, LOW); }
    
    delayMicroseconds(vitesseDelay);
  }
  return true; 
}