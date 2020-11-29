import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.*; 
import java.awt.Toolkit; 
import java.awt.datatransfer.StringSelection; 
import java.awt.datatransfer.Clipboard; 
import controlP5.*; 
import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class RGB_Serial_color_selector extends PApplet {

/*
Simple Processing HSB Color Picker by qewer3322

Normally it copies the color codes when you click
on them but doesnt work with Processing.js since
it's deprecated. Will work if you copy the code
and paste it to te Processing IDE.
*/







ControlP5 cp5;
Serial myPort;  // Create object from Serial class


String portName;
String portList[];


PFont font;
PFont font2;
int s1 = 20;
int ex = 20;
int ey = 60;
boolean s1b = false;
boolean s2b = false;
boolean c1 = false;
boolean c2 = false;
boolean c3 = false;
int c;

boolean i;
boolean port_con;

public void setup() {
  //if you paste this into the processing IDE,
  //delete size() and uncomment these lines
  //surface.setSize(460, 180);
  //surface.setLocation(displayWidth - 465, displayHeight - 230);
  //surface.setAlwaysOnTop(true);
  //fullScreen();
  
  colorMode(HSB, 360, 100, 100);
  font = createFont("Georgia", 32);
  font2 = createFont("Georgia", 32);
  
  i=false;
  port_con=false;
  
  portList=Serial.list();

  // Initialize the Ports list
  cp5 = new ControlP5(this);
  //List l = Arrays.asList("red", "green", "blue");
  List l = Arrays.asList(portList);
  /* add a ScrollableList, by default it behaves like a PortsList */
  cp5.addScrollableList("Ports")
    .setPosition(20, 200)
    .setSize(200, 100)
    .setBarHeight(20)
    .setItemHeight(20)
    .addItems(l)
    ;
    
 cp5.addButton("connect")
    .setValue(0)
    .setPosition(250,200)
    .setSize(100,19)
    ;
}

public void draw() {
  textFont(font);
  int f1 = s1 - 20;
  int f2 = ex - 20;
  int f3 = ey - 60;
  c = color(f1, f2, f3);

  background(0, 0, 100);

  //hue slider
  noStroke();
  for (int i = 20; i < 380; i++) {
    fill(i - 20, 100, 100);
    rect(i, 20, 1, 20);
  }

  stroke(255, 100, 0);
  noFill();
  rect(20, 20, 360, 20);

  fill(s1 - 20, 100, 100);
  triangle(s1-7, 9, s1 + 7, 9, s1, 25);

  if (s1b == true && s2b == false) s1 = mouseX;

  if (s2b == false && mousePressed && mouseX > 20 && mouseY > 20 && mouseX < 380 && mouseY < 40) s1b = true;

  if (s1 >= 380) s1 = 380;  
  if (s1 <= 20) s1 = 20;  

  //saturation and brightness display
  for (int i = 21; i < 120; i++) {
    for (int z = 61; z < 160; z++) {
      int v = color(s1 - 21, i - 20, z-61);
      set(i, z, v);
    }
  }

  //saturation and brightness 2d slider
  noFill();
  rect(20, 60, 100, 100);
  fill(c);
  if (ey > 110) stroke(0,0,0);
  else stroke(0,0,100);
  ellipse(ex, ey, 10, 10);
  stroke(0,0,0);

  if (s2b == true && s1b == false) {
    ex = mouseX;
    ey = mouseY;
  }

  if (s1b == false && mousePressed && mouseX > 20 && mouseY > 60 && mouseX < 120 && mouseY < 160) s2b = true;

  if (ex <= 20) ex = 20;
  if (ey <= 60) ey = 60;
  if (ex >= 120) ex = 120;
  if (ey >= 160) ey = 160;

  //color display
  fill(c);
  rect(140, 60, 100, 100);

  //main frame
  noFill();
  rect(0, 0, width - 1, height - 1);

  //exit button
  noFill();
  rect(400, 20, 40, 20);
  fill(0, 100, 100);
  if (mouseX > 400 && mouseY > 20 && mouseX < 440 && mouseY < 40) {
    rect(400, 20, 40, 20);
    stroke(0, 0, 100);
  } else stroke(0, 100, 0);
  line(415, 25, 425, 35);
  line(415, 35, 425, 25);

  //texts
  fill(0);
  textSize(20);
  colorMode(HSB, 360, 100, 100);
  text("HSB  (" + PApplet.parseInt(hue(c)) + ", " + PApplet.parseInt(saturation(c)) + ", " + PApplet.parseInt(brightness(c)) + ")", 253, 85);
  colorMode(RGB, 255, 255, 255);
  text("RGB (" + PApplet.parseInt(red(c)) + ", " + PApplet.parseInt(green(c)) + ", " + PApplet.parseInt(blue(c)) + ")", 253, 116);
  
  String Red=str(PApplet.parseInt(red(c)));
  String Green=str(PApplet.parseInt(green(c)));
  String Blue=str(PApplet.parseInt(blue(c)));
  String message= Red + "." + Green + "." + Blue + "." + ")";
  
  
  text("HEX  #" + hex(c, 6), 253, 145);
  colorMode(HSB, 360, 100, 100);
  
  //copy texts
  //1
  if (c1 == false && mouseX > 253 && mouseY > 70 && mouseX < 253 + textWidth("HSB  (" + PApplet.parseInt(hue(c)) + ", " + PApplet.parseInt(saturation(c)) + ", " + PApplet.parseInt(brightness(c)) + ")") && mouseY < 85) {
    textFont(font2);
    fill(0,0,100);
    rect(mouseX + 10,mouseY + 13,63,13);
    textSize(9);
    fill(0,0,0);
    text("Click to copy!",mouseX + 13,mouseY + 23);
  }
  if (c1 == true) {
    textFont(font2);
    fill(0,0,100);
    rect(mouseX + 10,mouseY + 13,39,13);
    textSize(9);
    fill(0,0,0);
    text("Copied!",mouseX + 13,mouseY + 23);
  }
  textFont(font);
  textSize(20);
  if (mouseX < 253 || mouseY < 70 || mouseX > 253 + textWidth("HSB  (" + PApplet.parseInt(hue(c)) + ", " + PApplet.parseInt(saturation(c)) + ", " + PApplet.parseInt(brightness(c)) + ")") || mouseY > 85) c1 = false;
  
  //2
  if (c2 == false && mouseX > 253 && mouseY > 100 && mouseX < 253 + textWidth("RGB (" + PApplet.parseInt(red(c)) + ", " + PApplet.parseInt(green(c)) + ", " + PApplet.parseInt(blue(c)) + ")") && mouseY < 115) {
    textFont(font2);
    fill(0,0,100);
    rect(mouseX + 10,mouseY + 13,63,13);
    textSize(9);
    fill(0,0,0);
    text("Click to copy!",mouseX + 13,mouseY + 23);
  }
  if (c2 == true) {
    textFont(font2);
    fill(0,0,100);
    rect(mouseX + 10,mouseY + 13,39,13);
    textSize(9);
    fill(0,0,0);
    text("Copied!",mouseX + 13,mouseY + 23);
  }
  textFont(font);
  textSize(20);
  if (mouseX < 253 || mouseY < 100 || mouseX > 253 + textWidth("RGB (" + PApplet.parseInt(red(c)) + ", " + PApplet.parseInt(green(c)) + ", " + PApplet.parseInt(blue(c)) + ")") || mouseY > 115) c2 = false;
  
  //3
  if (c3 == false && mouseX > 253 && mouseY > 130 && mouseX < 253 + textWidth("HEX  #" + hex(c, 6)) && mouseY < 145) {
    textFont(font2);
    fill(0,0,100);
    rect(mouseX + 10,mouseY + 13,63,13);
    textSize(9);
    fill(0,0,0);
    text("Click to copy!",mouseX + 13,mouseY + 23);
  }
  if (c3 == true) {
    textFont(font2);
    fill(0,0,100);
    rect(mouseX + 10,mouseY + 13,39,13);
    textSize(9);
    fill(0,0,0);
    text("Copied!",mouseX + 13,mouseY + 23);
  }
  textFont(font);
  textSize(32);
  if (mouseX < 253 || mouseY < 130 || mouseX > 253 + textWidth("HEX  #" + hex(c, 6)) || mouseY > 145) c3 = false;
  textFont(font);
  
  //println(mouseX);
  //println(mouseY);
  //text("RGB (" + int(red(c)) + ", " + int(green(c)) + ", " + int(blue(c)) + ")", 253, 116);

  println(message);
  if(port_con==true)
  {
  myPort.write(message);
  }
}



public void mouseReleased() {
  s1b = false;
  s2b = false;
  //this line quits the application when x button is pressed
  //commented it out cause it doesn't work in web
  //if (mouseX > 400 && mouseY > 20 && mouseX < 440 && mouseY < 40) exit();
  
  //copy to clipboard
  //1
  if (mouseX > 253 && mouseY > 70 && mouseX < 253 + textWidth("HSB  (" + PApplet.parseInt(hue(c)) + ", " + PApplet.parseInt(saturation(c)) + ", " + PApplet.parseInt(brightness(c)) + ")") && mouseY < 85) {
    StringSelection selection = new StringSelection(PApplet.parseInt(hue(c)) + ", " + PApplet.parseInt(saturation(c)) + ", " + PApplet.parseInt(brightness(c)));
    Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
    clipboard.setContents(selection, selection); 
    println(PApplet.parseInt(hue(c)) + ", " + PApplet.parseInt(saturation(c)) + ", " + PApplet.parseInt(brightness(c)));
    c1 = true;
  }
  
  //2
  colorMode(RGB, 255, 255, 255);
  if (mouseX > 253 && mouseY > 100 && mouseX < 253 + textWidth("RGB (" + PApplet.parseInt(red(c)) + ", " + PApplet.parseInt(green(c)) + ", " + PApplet.parseInt(blue(c)) + ")") && mouseY < 115) {
    StringSelection selection = new StringSelection(PApplet.parseInt(red(c)) + ", " + PApplet.parseInt(green(c)) + ", " + PApplet.parseInt(blue(c)));
    Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
    clipboard.setContents(selection, selection); 
    println(PApplet.parseInt(red(c)) + ", " + PApplet.parseInt(green(c)) + ", " + PApplet.parseInt(blue(c)));
    c2 = true;
  }
  
  //3
  if (mouseX > 253 && mouseY > 130 && mouseX < 253 + textWidth("HEX  #" + hex(c, 6)) && mouseY < 145) {
    StringSelection selection = new StringSelection("#" + hex(c, 6));
    Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
    clipboard.setContents(selection, selection); 
    println("#" + hex(c, 6));
    c3 = true;
   }
  colorMode(HSB, 360, 100, 100);
 }
 
 // Ports callback function fromthe ScrollableList, triggered when you select an item
public void Ports(int n) {
  /* request the selected item based on index n and store in a char */
  String string = cp5.get(ScrollableList.class, "Ports").getItem(n).get("name").toString();
  //println(string);
  portName=string;
} 

public void connect() 
{
  if(i==true)
  {
    if(portName != null)
    {
     myPort = new Serial(this, portName, 9600);
     port_con = true;
    }
   print("connect");
  }
  
  i = true;
}
  public void settings() {  size(460, 400); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "RGB_Serial_color_selector" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
