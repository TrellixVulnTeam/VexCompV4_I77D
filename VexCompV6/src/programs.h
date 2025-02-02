#include "Intergration.h"

/*
Name: programs.h
Written By: Carson Easterling

Implements the use function in intergation into robot programs that will run durign 15 second rounds or 1 minute skills round. Also contains implementation of a GUI for selection of which program to run
*/


//Programs
void blueLeft(int mod){
  moveCV(10, 0, 100);
  moveCV(40, 10, 92);
  frontPne.set(true);
  wait(300, msec);

  moveCV(-8, 0, -50);

  backPne.set(false);
  moveCV(16, 33, -80);

  backPne.set(true);
  wait(250, msec);
  moveCV(-30, -30, 80);

  moveAbs(0, 3, false);
  backPne.set(false);
  moveAbs(3, 6);
  moveCV(4, 5, 20);
}

void specialLeft(int mod){
  moveCV(10, 0, 100);
  moveCV(40, 10, 100);
  frontPne.set(true);
  wait(350, msec);

  moveCV(-25, -7, -80);
  backPne.set(false);
  turnTo(135);
  robot.usePIDControls(false);
  double t = Brain.timer(timeUnits::msec);
  while(((Brain.timer(timeUnits::msec) - t) <= 800) && (!LimitBack.pressing())){
    setLeft(-60);
    setRight(-60);
    wait(motionDelay, msec);
  }
  backPne.set(true);
  setLeft(0);
  setRight(0);

  moveTime(60, 800);
  arm.rotateTo(700, rotationUnits::deg, 90, velocityUnits::pct);
  setIntake(-80);
}

void blueRight(int mod){
  moveCV(50, 0, 100);
  frontPne.set(true);
  wait(250, msec);
  moveCV(-15, -11, -40);
  backPne.set(false);

  moveCV(20, -23, -100);
  backPne.set(true);
  wait(250, msec);


  moveCV(-38, 33, 90);
  moveCV(-9, 9, -90);

  backPne.set(false);
  moveAbs(4, 18, true);
  turnTo(180);
  robot.usePIDControls(false);
  double t = Brain.timer(timeUnits::msec);
  while(((Brain.timer(timeUnits::msec) - t) <= 800) && (!LimitBack.pressing())){
    setLeft(-40);
    setRight(-40);
    wait(motionDelay, msec);
  }
  backPne.set(true);
  setLeft(0);
  setRight(0);
}

void rightSpecial(int mod){
  moveCV(50, 0, 100);
  frontPne.set(true);
  wait(250, msec);
  moveCV(-22, 0, -70);
  backPne.set(false);
  moveCV(0, 20, -80);
  backPne.set(true);
  wait(250, msec);
  arm.rotateTo(700, rotationUnits::deg, 90, velocityUnits::pct);
  setIntake(-80);
  moveCV(0, -10, 70);
}


//Storage of program functions for use in the GUI
typedef struct {
  std::string name;
  void (*function)(int);
  int mod;
} autoEntry;

//Use of a table allows programs to be easily added or removed
autoEntry entries[] = {
  {"Right", blueRight},
  {"Right Special", rightSpecial},
  {"Left", blueLeft},
  {"Left Special", specialLeft},
};
int indexAuto = 0;


//START OF GUI------------------------------------------------------------------------
bool programRunning = false;

//Abstract Button Class
class ButtonGUI {
  public:
    int x;
    int y;
    int width;
    int height;
    void (*callback)();
    void (*drawing)(int x, int y, int w, int h, bool press);
    int *point;
    bool isPressed = false;

    ButtonGUI(int X, int Y, int W, int H, void (*call)(), void (*drawFunct)(int x, int y, int w, int h, bool press)){
      x = X;
      y = Y;
      width = W;
      height = H;
      callback = call;
      drawing = drawFunct;
    }

    bool call(int X, int Y){
      if((X >= x) && (X <= (x+width))){
        if((Y >= y) && (Y <= (y+height))){
          callback();
          isPressed = true;
          return true;
        }
      }
      return false;
    }

    void draw(){
      drawing(x, y, width, height, isPressed);
    }
};

//Implementation of a button to increase the auto index to change which function is selected
void increaseIndex(){
  indexAuto += 1;
  if(indexAuto > (sizeof(entries)/sizeof(entries[0]))-1){
    indexAuto = 0;
  }
}

void drawAAA(int x, int y, int w, int h, bool press){
  if(press){
    Brain.Screen.setFillColor(green);
  }else{
    Brain.Screen.setFillColor(red);
  }
  Brain.Screen.drawRectangle(x, y, w, h);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawLine((w/4)+x, (3*h/4)+y, (w/2)+x, (h/4)+y);
  Brain.Screen.drawLine((3*w/4)+x, (3*h/4)+y, (w/2)+x, (h/4)+y);
}
ButtonGUI increaseBTN(480-50,0,50,70, increaseIndex, drawAAA);

void decreaseIndex(){
  indexAuto -= 1;
  if(indexAuto < 0){
    indexAuto = (sizeof(entries)/sizeof(entries[0]))-1;
  }
}
void drawAAB(int x, int y, int w, int h, bool press){
  if(press){
    Brain.Screen.setFillColor(green);
  }else{
    Brain.Screen.setFillColor(red);
  }
  Brain.Screen.drawRectangle(x, y, w, h);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawLine((w/4)+x, (h/4)+y, (w/2)+x, (3*h/4)+y);
  Brain.Screen.drawLine((3*w/4)+x, (h/4)+y, (w/2)+x, (3*h/4)+y);
}
ButtonGUI decreaseBTN(480-50,80,50,70, decreaseIndex, drawAAB);

bool GUIActivate = true;
void setAuto(){
  GUIActivate = false;
}
void drawAAC(int x, int y, int w, int h, bool press){
  if(press){
    Brain.Screen.setFillColor(white);
  }else{
    Brain.Screen.setFillColor(red);
  }
  Brain.Screen.drawRectangle(x, y, w, h);
  if(press){
    Brain.Screen.setFillColor(green);
  }else{
    Brain.Screen.setFillColor(white);
  }
  Brain.Screen.drawCircle((w/2)+x, (h/2)+y, (w/4));
}
ButtonGUI setBTN(480-50,160,50,70, setAuto, drawAAC);

//All buttons used in GUI
ButtonGUI buttons[] = {increaseBTN, decreaseBTN, setBTN};

//Calls a button if pressed
void pressHandler(){
  if(!GUIActivate){return;}
  static bool free = true;

  if(free){
    free = false;
  }else{
    return;
  }
  
  if(Brain.Screen.pressing()){
    for(int i=(sizeof(buttons)/sizeof(ButtonGUI))-1; i >= 0; i--){
      if(buttons[i].call(Brain.Screen.xPosition(), Brain.Screen.yPosition())){
        buttons[i].draw();
        waitUntil(!Brain.Screen.pressing());
        buttons[i].isPressed = false;
        free = true;
        return;
      }
    }
  }
}

//Main GUI loop that draws/animates button objects
void BrainGUIProgram(){
  Brain.Screen.pressed(pressHandler);

  while(GUIActivate){
    Brain.Screen.setFillColor(black);
    Brain.Screen.setPenColor(white);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);

    std::string out = entries[indexAuto].name;
    Brain.Screen.print(out.c_str());
    updateControllerDisplay();

    for(int i=0; i < (sizeof(buttons)/sizeof(ButtonGUI)); i++){
      buttons[i].draw();
    }
    Brain.Screen.render();
    wait(50, msec);
  }

  Brain.Screen.setFillColor(black);
  Brain.Screen.setPenColor(white);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  std::string out = entries[indexAuto].name;
  Brain.Screen.print("Selected: %s", out.c_str());
  Brain.Screen.render();
}

//Auto function used by competition template
void autonomous(void){
  GUIActivate = false;

  Inertial.setHeading(360-startingHead, rotationUnits::deg); //90 deg CCW but inertial sensor only measures in CW
  resetEncoders();
  task traker = task(trakerFunction);
  wait(updateTime+1, msec);

  entries[indexAuto].function(entries[indexAuto].mod);
}

//Brain.SDcard.isInserted();