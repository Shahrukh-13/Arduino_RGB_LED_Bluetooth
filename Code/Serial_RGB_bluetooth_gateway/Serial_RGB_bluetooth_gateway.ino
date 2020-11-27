

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
pinMode(9,INPUT);
pinMode(10,INPUT);
pinMode(11,INPUT);

digitalWrite(9,HIGH);
digitalWrite(10,HIGH);
digitalWrite(11,HIGH);

Serial.begin(9600);
Serial.flush();

}
void loop()
{
  i=0;   
  j=0;

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
    String red=r.substring(0,r.indexOf('.'));
    String r2=r.substring(r.indexOf('.')+1, r.indexOf(')'));
    
    String green=r2.substring(0,r2.indexOf('.'));
    String r3=r2.substring(r2.indexOf('.')+1, r2.indexOf(')'));

    String blue=r3.substring(0,r3.indexOf('.'));

    //String color=red + "," + green + "," + blue;
    
    /*R=red.toInt();
    G=green.toInt();
    B=blue.toInt();*/
    
    if(digitalRead(9) == HIGH && digitalRead(10) == HIGH && digitalRead(11) == HIGH)
    {
      id = 0;
    }

    if(digitalRead(9) == LOW && digitalRead(10) == HIGH && digitalRead(11) == HIGH)
    {
      id = 1;
    }

     if(digitalRead(9) == HIGH && digitalRead(10) == LOW && digitalRead(11) == HIGH)
    {
      id = 2;
    }

      if(digitalRead(9) == HIGH && digitalRead(10) == HIGH && digitalRead(11) == LOW)
    {
      id = 3;
    }
    String ID(id);

    String RGB = ID + "." + red + "." + green + "." + blue + "." + ")" + "\n";

   //Serial.println(RGB);   
   
  while(RGB[j]!='\0')
{
  Serial.write(RGB[j]);
  j++;
}
    
}
