#include "motor.h"

motor::motor(int pwm, int in1, int in2) {
  pwmPin = pwm;
  in1Pin = in1;
  in2Pin = in2;

  aktuellerWert = 2047; // Panzer startet im absoluten Stillstand
  zielWert = 2047;
  letzteZeit = 0;

  
  pinMode(pwmPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

}


// Nimmt nur noch den Wunschwert vom Browser entgegen und speichert ihn
void motor::setspeed(int wert) {
  if(abs( wert - 2047) < DEADZONE){
    wert = 2047;
  }
  zielWert = wert; 
}



void motor::update() {
  
// Wir ändern die Geschwindigkeit nur alle 5 Millisekunden
  if (millis() - letzteZeit > 5) {
    letzteZeit = millis();

    // 1. SCHRITT: Aktuellen Wert weich in Richtung Zielwert schieben
    if (aktuellerWert < zielWert) {
      aktuellerWert += 15; // Beschleunigungs-Schritt (Größer = Schneller)
      if (aktuellerWert > zielWert) aktuellerWert = zielWert; // Nicht übers Ziel hinausschießen
    } 
    else if (aktuellerWert > zielWert) {
      aktuellerWert -= 15; // Brems-/Rückwärts-Schritt
      if (aktuellerWert < zielWert) aktuellerWert = zielWert;
    }







  // Hier definieren wir das absolute Hardware-Limit für die Motoren.
  // 4095 = 100% | 2047 = 50% | 1023 = 25%
  // 2. SCHRITT: Deine alte Logik, aber sie nutzt jetzt den WEICHEN 'aktuellerWert'
    int gas; 
    int maxgas = 600; // Dein Hardware-Limit

    if (aktuellerWert >= 2047) {
      // Eine Richtung
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);
      gas = map(aktuellerWert, 2047, 4095, 0, maxgas);
    } 
    else {
      // Andere Richtung
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
      gas = map(aktuellerWert, 2046, 0, 0, maxgas);
    }

    // Gibt das weiche Signal an den Motortreiber weiter
    analogWrite(pwmPin, gas); 
  }
}