
#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

const int DEADZONE = 240;

class motor {
  private:
    int pwmPin;
    int in1Pin;
    int in2Pin;

// NEU: Variablen für den Soft-Start
    int aktuellerWert;      // Wo der Motor gerade steht (Startet bei 2047 = Stopp)
    int zielWert;           // Wo der Motor hin soll
    unsigned long letzteZeit; // Für den Millisekunden-Timer (Ramping-Geschwindigkeit)


  public:
    // Der neue Konstruktor verlangt 3 Pins
    motor(int pwm, int in1, int in2); 
    void setspeed(int wert);
    void update();          // NEU: Diese Funktion rechnet das weiche Anfahren
};


#endif