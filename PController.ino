int outputu = 9; //PIN 2 input to the plant, output of the shield
int inputy = A0; //PIN 7 output of the plant, input to the shield
int referencia = A1; 
int y=0;
int error=0;
int ref=0;
int u = 0;
int u_1 = 0;
int error_1 = 0;
int error_2 = 0;
int k=12;

void setup(){
 //initialize the pins
 pinMode(LED_BUILTIN, OUTPUT);
 pinMode(outputu, OUTPUT);
 pinMode(inputy, INPUT);
 pinMode(referencia, INPUT);
 Serial.begin(9600);

}


void loop(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
  
 //ref = analogRead(referencia); //si se quiere leer una ref. externa
 ref = 204; //1 V - 2V 408
 y = analogRead(inputy);
 //if (y < 0) { y = 0;}
 error = (ref -  y); 
 u=k*error;
 
 if (u>0){
 analogWrite(outputu, map(u,0,1023,0,255));
 } else{
 analogWrite(outputu,0); 
 }
 
 //Serial.println(map(u,0,1023,0,255));
 Serial.println(y);
 //Serial.println(error);
 delay(180);
}

/////
