#include <EEPROM.h>

char data;     // Varriabel for reading incoming byte over serial port 
char res[100]; // Character array for storing read bytes
int i;         // Varriable for incrementing char array index


int R;  // Red color value (0-255)
int G;  // Green color value  (0-255)
int B;  // Blue color value (0-255)


int addR=0;  // Address for storing Red color value (0-255) in EEPROM
int addG=1;  // Address for storing Red color value (0-255) in EEPROM
int addB=2;  // Address for storing Red color value (0-255) in EEPROM

void setup()
{
pinMode(9,OUTPUT);   // Blue
pinMode(10,OUTPUT);  // Green
pinMode(11,OUTPUT);  // Red

digitalWrite(9,LOW);
digitalWrite(10,LOW);
digitalWrite(11,LOW);

Serial.begin(9600);
Serial.flush();
//delay(1000);

    analogWrite(11,EEPROM.read(addR));  //Write last value stored in EEPROM for Red color
    analogWrite(10,EEPROM.read(addG));  //Write last value stored in EEPROM for Green color
    analogWrite(9,EEPROM.read(addB));   //Write last value stored in EEPROM for Blue color
}
void loop()
{
  i=0;   
  while( data!=')')     
        {
          while(Serial.available())
          {
          data=Serial.read();
           res[i]=data;
            i++;
        }
        }
        data=0;
    String r(res);   
    String red=r.substring(0,r.indexOf('.'));                           // Red color value in string format                            
    String r2=r.substring(r.indexOf('.')+1, r.indexOf(')'));
    
    String green=r2.substring(0,r2.indexOf('.'));                      // Green color value in string format  
    String r3=r2.substring(r2.indexOf('.')+1, r2.indexOf(')'));

    String blue=r3.substring(0,r3.indexOf('.'));                       // Blue color value in string format  

    //String color=red + "," + green + "," + blue;
    
    R=red.toInt();     //convert string to int
    G=green.toInt();   //convert string to int
    B=blue.toInt();    //convert string to int
    
EEPROM.write(addR, R);  // Save Red color value to its correspondig address in EEPROM
EEPROM.write(addG, G);  // Save Green color value to its correspondig address in EEPROM
EEPROM.write(addB, B);  // Save Blue color value to its correspondig address in EEPROM
    
    analogWrite(11,EEPROM.read(addR));  //Write last value stored in EEPROM for Red color
    analogWrite(10,EEPROM.read(addG));  //Write last value stored in EEPROM for Green color
    analogWrite(9,EEPROM.read(addB));   //Write last value stored in EEPROM for Blue color
    
}
