#include <EEPROM.h>

char data;     // Varriabel for reading incoming byte over serial port 
char res[100]; // Receiver character array for storing read bytes
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
  i=0;     // Set the index of receiver character array to 0 at the start of loop
  
  while( data!=')')                             // The incoming data is in format "R.G.B.)" ; therefore read data until ')' is received
        {
          while(Serial.available())
          {
          data=Serial.read();                 // read incoming data byte
           res[i]=data;                       // Add data to receiver character array
            i++;                              // increment index of receiver character array
        }
        }
        data=0;                   // After reading the message set 'data' to 0
        
    String r(res);                                              // Convert character array to string r

    //Serial.println(r);
    String red=r.substring(0,r.indexOf('.'));                           // Red color value in string format
                                                                        // From start of string r to character '.'
                                                                                                    
    String r2=r.substring(r.indexOf('.')+1, r.indexOf(')'));           // r2 is Substring of r with Red color value removed
             
    
    String green=r2.substring(0,r2.indexOf('.'));                      // Green color value in string format  
                                                                       // From start of string r2 to character '.'

                                                                       
    String r3=r2.substring(r2.indexOf('.')+1, r2.indexOf(')'));       // r3 is Substring of r2 with Green color value removed

    String blue=r3.substring(0,r3.indexOf('.'));                       // Blue color value in string format
                                                                       // From start of string r3 to character '.'  

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
