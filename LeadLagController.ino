int outputu = 9; //PIN 2 input to the plant, output of the shield
int inputy = A0; //PIN 7 output of the plant, input to the shield
int referencia = A1; 
int y=0;
int error=0;
int ref=0;
int u = 0;
int u_1 = 0;
int u_2 = 0;
int error_1 = 0;
int error_2 = 0;
int k=20;

void setup(){
 //initialize the pins
 pinMode(outputu, OUTPUT);
 pinMode(inputy, INPUT);
 pinMode(referencia, INPUT);

}


void loop(){
 //ref = analogRead(referencia); //si se quiere leer una ref. externa
 ref = 204; //1 V
 y = analogRead(inputy);
 error = (ref -  y); 
 u= (20*error) - (23*error_1) - (3.8*error_2) + (0.96*u_1) + (0.0297*u_2);
 
 
if (u>0){
 analogWrite(outputu, map(u,0,1023,0,255));
 } else{
 analogWrite(outputu,0);
 }
 
 error_2 = error_1;
 error_1 = error;
 u_1 = u;
 u_2 = u_1;
 delay(180);
}

/////
