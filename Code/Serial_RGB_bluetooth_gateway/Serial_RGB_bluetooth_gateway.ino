

int i;
int j;
char data;
char res[100];

int R;
int G;
int B;

int id;

void setup()
{
pinMode(9,INPUT);    // Switch-3
pinMode(10,INPUT);   // Switch-2
pinMode(11,INPUT);   // Switch-1

digitalWrite(9,HIGH);
digitalWrite(10,HIGH);
digitalWrite(11,HIGH);


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

  
  
  i=0;   
  j=0;

  while( data!=')')   
        {
          updateID();
          while(Serial.available())
          {
          data=Serial.read();
           res[i]=data;
            i++;
        }
        }
        data=0;
    String r(res);
    String red=r.substring(0,r.indexOf('.'));
    String r2=r.substring(r.indexOf('.')+1, r.indexOf(')'));
    
    String green=r2.substring(0,r2.indexOf('.'));
    String r3=r2.substring(r2.indexOf('.')+1, r2.indexOf(')'));

    String blue=r3.substring(0,r3.indexOf('.'));

    //String color=red + "," + green + "," + blue;
    
    /*R=red.toInt();
    G=green.toInt();
    B=blue.toInt();*/
    
    //updateID();
    
    String ID(id);

    String RGB = ID + "." + red + "." + green + "." + blue + "." + ")" + "\n";

   //Serial.println(RGB);   
   
  while(RGB[j]!='\0')
{
  Serial.write(RGB[j]);
  j++;
}
    
}

void updateID()   // This function reads switches and updates IDs and LEDs accordingly
{

    if(digitalRead(11) == LOW && digitalRead(10) == HIGH && digitalRead(9) == HIGH)
    {
      id = 1;
      digitalWrite(8,HIGH);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
    }

     else if(digitalRead(11) == HIGH && digitalRead(10) == LOW && digitalRead(9) == HIGH)
    {
      id = 2;
      digitalWrite(8,LOW);
      digitalWrite(7,HIGH);
      digitalWrite(6,LOW);
    }

      else if(digitalRead(11) == HIGH && digitalRead(10) == HIGH && digitalRead(9) == LOW)
    {
      id = 3;
      digitalWrite(8,LOW);
      digitalWrite(7,LOW);
      digitalWrite(6,HIGH);
    }
    else
    {
      id = 0;
      digitalWrite(8,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
    }
}


