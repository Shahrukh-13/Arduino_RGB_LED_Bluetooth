

char data;       // Varriabel for reading incoming byte over serial port
char res[100];   // Receiver character array for storing read bytes
int i;           // Varriable for incrementing char array index
int j;           // Varriable for incrementing string index

int R;          // Red color value (0-255)
int G;          // Green color value  (0-255)
int B;          // Blue color value (0-255)

int id;         // model ID  

void setup()
{
pinMode(9,INPUT);    // Switch-3
pinMode(10,INPUT);   // Switch-2
pinMode(11,INPUT);   // Switch-1

digitalWrite(9,HIGH);      // External 10K pullup
digitalWrite(10,HIGH);     // External 10K pullup
digitalWrite(11,HIGH);     // External 10K pullup


pinMode(8,OUTPUT);  // Switch-1 LED
pinMode(7,OUTPUT);  // Switch-2 LED
pinMode(6,OUTPUT);  // Switch-3 LED

digitalWrite(8,LOW);
digitalWrite(7,LOW);
digitalWrite(6,LOW);

Serial.begin(9600);
Serial.flush();

}
void loop()
{

  
  
  i=0;                   // Set the index of receiver character array to 0 at the start of loop
  j=0;                  // Set the index of receiver string array to 0 at the start of loop

  while( data!=')')               // The incoming data is in format "ID.R.G.B.)" ; therefore read data until ')' is received
        {
          updateID();              // Read switches and update IDs and LEDs
          while(Serial.available())
          {
          data=Serial.read();               // read incoming data byte
           res[i]=data;                    // Add data to receiver character array
            i++;                           // increment index of receiver character array
        }
        }
        data=0;                            // After reading the message set 'data' to 0
        
    String r(res);                                                      // Convert character array to string r
    
    String red=r.substring(0,r.indexOf('.'));                          // Red color value in string format
                                                                       // From start of string r to character '.'
                                                            
    String r2=r.substring(r.indexOf('.')+1, r.indexOf(')'));          // r2 is Substring of r with Red color value removed
    
    String green=r2.substring(0,r2.indexOf('.'));                    // Green color value in string format
                                                                     // From start of string r2 to character '.'
                                                                     
    String r3=r2.substring(r2.indexOf('.')+1, r2.indexOf(')'));      // r3 is Substring of r2 with Green color value removed

    String blue=r3.substring(0,r3.indexOf('.'));                     // Blue color value in string format
                                                                     // From start of string r3 to character '.'

    //String color=red + "," + green + "," + blue;
    
    /*R=red.toInt();
    G=green.toInt();
    B=blue.toInt();*/
    
    //updateID();
    
    String ID(id);                //convert string to int

    String RGB = ID + "." + red + "." + green + "." + blue + "." + ")" + "\n";     // Create a string containing ID and R,G,B color values

   //Serial.println(RGB);   
   
  while(RGB[j]!='\0')     // Send string RGB to serial port
{
  Serial.write(RGB[j]);
  j++;
}
    
}

void updateID()   // This function reads switches and updates IDs and LEDs accordingly
{
    if(digitalRead(11) == LOW && digitalRead(10) == LOW && digitalRead(9) == LOW)    // All Switches Low (All models selected)
    {
      id = 0;                 // All models (Broadcast)
      
      digitalWrite(8,HIGH);   // All lEDs High
      digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
    }
    else if(digitalRead(11) == LOW && digitalRead(10) == HIGH && digitalRead(9) == HIGH)  // Model 1 selected
    {
      id = 1;                // Model 1
      
      digitalWrite(8,HIGH);  // Model 1 LED High
      digitalWrite(7,LOW);   // Model 2 LED Low
      digitalWrite(6,LOW);   // Model 3 LED Low
    }

     else if(digitalRead(11) == HIGH && digitalRead(10) == LOW && digitalRead(9) == HIGH)  // Model 2 selecterd
    {
      id = 2;                 // Model 2
      
      digitalWrite(8,LOW);    // Model 1 LED Low
      digitalWrite(7,HIGH);   // Model 2 LED High
      digitalWrite(6,LOW);    // Model 3 LED Low
    }

      else if(digitalRead(11) == HIGH && digitalRead(10) == HIGH && digitalRead(9) == LOW)   // Model 3 selected
    {
      id = 3;                 // Model 3
      
      digitalWrite(8,LOW);    // Model 1 LED Low
      digitalWrite(7,LOW);    // Model 2 LED Low
      digitalWrite(6,HIGH);   // Model 3 LED High
    }
    
    else     // For anyother switch combination
    {
      id = 999;                        
      digitalWrite(8,LOW);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
    }
}


