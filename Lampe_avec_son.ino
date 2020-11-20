int capteur_clap = 3;
int relais = 2;
int powerPin = A2;
int gndPin = A1;


int clap = 0;
long debut_plage_detection = 0;
long plage_detection = 0;
boolean etat_lampe = false;
 
void setup() {
  pinMode(capteur_clap, INPUT);
  pinMode(relais, OUTPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin,LOW);
  digitalWrite(powerPin,HIGH);
  Serial.begin(9600);
}
 
void loop() {
  
  int etat_capteur_clap = digitalRead(capteur_clap);
  
  if (etat_capteur_clap == 1)
  {
      if (clap == 0)
      {
        debut_plage_detection = plage_detection = millis();
        clap++;
      }
      else if (clap > 0 && millis()- plage_detection >= 50)
      {
        plage_detection = millis();
        clap++;
      }
  }
  
  if (millis()- debut_plage_detection >= 400)
  {
      if (clap == 2)
      {
          if (!etat_lampe)
            {
              etat_lampe = true;
              digitalWrite(relais, HIGH);
              Serial.println(1);
            }
          else if (etat_lampe)
            {
              etat_lampe = false;
              digitalWrite(relais, LOW);
            }
      }
      clap = 0;
  }
}
