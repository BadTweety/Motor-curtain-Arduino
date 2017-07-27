/*************************************************************
Revamped Motor Shield Stepper Demo, by Randy Sarafan
For more information see:
https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/
BadTweety,Sumic
*************************************************************/
//buttons and button states
const int buttonPinUp = 7;
const int buttonPinStop = 6;
const int buttonPinDown = 5;
const int buttonPinSensorUp = 4;
const int buttonPinSensorDown = 2;

int buttonStateUp = 0;
int buttonStateStop = 0;
int buttonStateDown = 0;
int buttonStateSensorUp = 0;
int buttonStateSensorDown = 0;

int delaylegnthUp = 2;
int delaylegnthDown = 1;

void setup() { 
  //establish motor direction toggle pins
  pinMode(12, OUTPUT); //CH A -- HIGH = forwards and LOW = backwards???
  pinMode(13, OUTPUT); //CH B -- HIGH = forwards and LOW = backwards???
  
  //establish motor brake pins
  pinMode(9, OUTPUT); //brake (disable) CH A
  pinMode(8, OUTPUT); //brake (disable) CH B

  pinMode(buttonPinUp, INPUT_PULLUP); //gumb za gor
  pinMode(buttonPinDown, INPUT_PULLUP); //gumb za dol
  pinMode(buttonPinStop, INPUT_PULLUP); // gumb za stop
  pinMode(buttonPinSensorUp, INPUT_PULLUP); //gumb za stop zgoraj
  pinMode(buttonPinSensorDown, INPUT_PULLUP); // gumb za stop spodaj  
}

void loop(){
  while(1){
    buttonStateUp = digitalRead(buttonPinUp);
    buttonStateDown = digitalRead(buttonPinDown);
    buttonStateStop = digitalRead(buttonPinStop);
    //GOR
    if(buttonStateUp == LOW) { //če je za gor, pojdi gor
      buttonStateSensorUp = digitalRead(buttonPinSensorUp);
      if(buttonStateSensorUp == LOW){ // če je zgornji senzor gumb pritisnjen, ne naredi nič
        continue;
      }
      else{ // drugače pojdi gor
        while(digitalRead(buttonPinSensorUp)==HIGH){ // dokler gremo lahko gor, gremo gor
            buttonStateStop = digitalRead(buttonPinStop);
            if(buttonStateStop == LOW){ // prekini na STOP
              analogWrite(3,0);
              analogWrite(11,0);
              break;
            }
            gorEnPulz();          
        }
      }
    }    
    //DOL
      if(buttonStateDown == LOW) { //če je za gor, pojdi dol
      buttonStateSensorDown = digitalRead(buttonPinSensorDown);
      if(buttonStateSensorDown == LOW){ // če je zgornji senzor gumb pritisnjen, ne naredi nič
        continue;
      }
      else{ // drugače pojdi gor
        while(digitalRead(buttonPinSensorDown)==HIGH){ // dokler gremo lahko dol, gremo dol
            buttonStateStop = digitalRead(buttonPinStop);
            if(buttonStateStop == LOW){ // prekini na STOP
              analogWrite(3,0);
              analogWrite(11,0);
              break;
            }
            dolEnPulz();          
        }
      }
    }
    //STOP
    if(buttonStateStop == LOW){ //če je stop, ustavi vse
      analogWrite(3,0);
      analogWrite(11,0);     
    }     
  }
}

void dolEnPulz(){
   digitalWrite(12, HIGH);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  delay(delaylegnthDown);

  analogWrite(3,0);

  digitalWrite(13, LOW);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  
  delay(delaylegnthDown);

  analogWrite(11,0);

  digitalWrite(12, LOW);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  delay(delaylegnthDown);

  analogWrite(3,0);
 
  digitalWrite(13, HIGH);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  
  delay(delaylegnthDown);

  analogWrite(11,0);

}

void gorEnPulz(){
  digitalWrite(12, HIGH);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  delay(delaylegnthUp);

  analogWrite(3,0);

  digitalWrite(13, HIGH);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  
  delay(delaylegnthUp);

  analogWrite(11,0);


  digitalWrite(12, LOW);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  delay(delaylegnthUp);

  analogWrite(3,0);
 
  digitalWrite(13, LOW);   //Sets direction of CH B
  analogWrite(11, 255);   //Moves CH B
  
  delay(delaylegnthUp);

  analogWrite(11,0);
}


