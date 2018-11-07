

#include <cstdio>
#include <sstream>
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdlib.h> 
#include <ctime>


#ifdef __APPLE__
#  pragma clang diagnostic ignored "-Wdeprecated-declarations"
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

// //  Rotation constants
// static int rotating = 0;
// static float y_angle = 0;
// //static int y_angle = 0;
// static float y_delta = 0.1;
// static float x_angle = 0;
// //static int x_angle = 0;
// static float x_delta = 0.1;

// Window handles
static int window_cube;
static int window_green;
static int window_red;
static int window_blue;

// Display list constants
const int cube = 1;
const int green = 2;
const int red = 3;
const int blue = 4;

// Color variables
static float g = -1.0;
static float r = -1.0;
static float b = -1.0;

static int color_tgl = 1;

// main window initial dimensions
const int WINDOW_SIZE = 800;

// color slider initial dimensions
const int SLIDER_HEIGHT = 20;
static int green_window_width = 200;
static int red_window_width = 200;
static int blue_window_width = 200;

// void mouse(int btn, int state, int x, int y)
// {
//   if (btn == GLUT_LEFT_BUTTON) 
//   rotating = 1 - rotating;  
// }

// void motion(int x, int y)
// {
//   static int prev_x = 0, prev_y = 0;

//   if (rotating == 1)
//     {
//       if (x > prev_x)
//   {
//     y_angle += y_delta;
//     prev_x = x;
//   }
//       else if (x < prev_x)
//   {
//     y_angle -= y_delta;
//     prev_x = x;
//   }


//       if (y > prev_y)
//   {
//     x_angle += x_delta;
//     prev_y = y;
//   }
//       else if (y < prev_y)
//   {
//     x_angle -= x_delta;
//     prev_y = y;
//   }
//       glutPostRedisplay();
//     }
// }

GLUquadricObj *cyl = gluNewQuadric();
GLfloat diffuseMaterial[4] = { 0.2, 0.2, 0.2, 1.0 };
  
int userChoice = 0;
int treeSize = 1;
int seasonChoice = 0;
char userAx;
std::string userRule;
float userAngle;


std::string mainString;

void handleKeys(unsigned char key, int x, int y){
  switch(key){
    case 'q':   // q - quit
    case 'Q':
    case 27:    // esc - quit
      exit(0);

    default:    // not a valid key -- just ignore it
    return;
  }
}

void growString(std::string& newString) 
{

  std::string buildString;
  std::string changeString;

  char newChar = 'z';

  for(int i = 0; i < newString.size(); i++) {

    newChar = newString.at(i);

    switch(newChar) {
      
      // for Celtic Tree
      case 'a': 
        changeString = "a";
        break;

      case 'b': 
        changeString = "a[rb][lb]";
        break;

      // for fractal tree
      case 'f': 
        changeString = "ff";
        break;

      case 'x': 
        changeString = "fl[[xy]rxy]rf[rfxy]lx";
        break;

      case 'y': 
        changeString = "y";
        break;

      // Truffula tree
      case 't': 
        changeString = "tt";
        break;

      case 's': 
        changeString = "[s]r[s]";
        break;

      case 'k': 
        changeString = userRule;
        break;

      // rotate calls
      case 'r': 
        changeString = "r";
        break;

      case 'l': 
        changeString = "l";
        break;

      // push matrix
      case '[': 
        changeString = "[";
        break;

      // pop matrix
      case ']': 
        changeString = "]";
        break; 
      }

    buildString = buildString + changeString;
  }

  newString = buildString;
}

void drawSwitch(std::string mainString) 
{
  float setWidth = static_cast<float>(treeSize);
  float cylWidth = 0.0;
  float cylChange = 0.0;
  float cylHeight = 0.0;
  float rotateAngle = 0.0;
  char readChar = 'z';
  srand( time(0));
  int popCount = 0;
  bool popSwitch = false;

  //sets variables for Celtic Tree
  if (userChoice == 1) {
    cylWidth = (setWidth/200);
    cylChange = (cylWidth/(treeSize+1));
    cylHeight = 0.2;
    rotateAngle = 20;
  }

  // sets variables for fratal plant
  if (userChoice == 2) {
    cylWidth = (setWidth/300);
    cylHeight = 0.1;
    rotateAngle = (22.5);
  }

  // // sets variable for Truffula tree
  if (userChoice == 3) {
    cylWidth = (setWidth/100);
    cylChange = (cylWidth/19);
    cylHeight = 0.05;
    rotateAngle = (360/(setWidth + 1));
  }

    // sets variables for user plant
  if (userChoice == 4) {
    cylWidth = (setWidth/300);
    cylHeight = 0.1;
    rotateAngle = (userAngle);
  }

  for(int i = 0; i < mainString.length(); i++) {
     
    float randomNum = 0.0;
       
    readChar = mainString.at(i);

    switch(readChar) {

      case 'a': //grow Celtic trunk
        gluCylinder(cyl, (cylWidth+cylChange), cylWidth, cylHeight, 30, 30);
        glTranslatef(0.0, 0.0, cylHeight);
        glutSolidSphere(cylWidth, 50, 50);
        // if (popCount == 0) {
        //   glRotatef(20, 0.0, 0.0, 1.0); 
        // } 
        // if (popCount == 1) {
        //   glRotatef(-20, 0.0, 0.0, 1.0); 
        // }
        // if (popCount == 2) {
        //   glRotatef(-20, 0.0, 0.0, 1.0); 
        // }
        // if (popCount == 3) {
        //   glRotatef(20, 0.0, 0.0, 1.0); 
        //   popCount = 0;
        // }
        // popCount++;
        break;

      case 'b': //grow Celtic branches
        gluCylinder(cyl, (cylWidth+cylChange), cylWidth, cylHeight, 30, 30);
        glTranslatef(0.0, 0.0, cylHeight);
        //change leaf color based on season, no leaves for winter
        if (seasonChoice == 1) {
          glColor4f(1.0,0.4,0.8,1.0);
          glutSolidSphere(0.02, 50, 50);
        }
        if (seasonChoice == 2) {
          glColor4f(0.0,0.5,0.09,1.0);
          glutSolidSphere(0.02, 50, 50);
        }
        if (seasonChoice == 3) {
          glColor4f(1.0,0.4,0.0,1.0);
          glutSolidSphere(0.02, 50, 50);
        }
        glColor4f(0.28,0.14,0.08,1.0);
        break;    

      case 'x': // fractal trunk and branches
        gluCylinder(cyl, (cylWidth+cylChange), cylWidth, cylHeight, 30, 30);
        glTranslatef(0.0, 0.0, cylHeight);
        glutSolidSphere((cylWidth+cylWidth), 30, 30);
        break;

      case 'f': // fractal tips
        gluCylinder(cyl, (cylWidth+cylChange), cylWidth, cylHeight, 30, 30);
        glTranslatef(0.0, 0.0, cylHeight);
        break;

      case 'y': // fractal flowers
        glColor4f(0.8,0.8,0.0,1.0);
        glutSolidSphere((cylWidth*2), 30, 30);
        glColor4f(1.0,1.0,1.0,1.0);
          for (int k = 0; k < 12; k++) {
            gluCylinder(cyl, (cylWidth), 0.0, (cylWidth*6), 30, 30);
            glRotatef(30, 0.0, 1.0, 0.0); 
          }
        glColor4f(0.0,0.5,0.09,1.0);
        break;

      case 't': //grow truffula trunk
        if (i % 2 != 0) {
          glColor4f(1.0,1.0,0.4,1.0);
        } else { 
          glColor4f(0.2,0.2,0.0,1.0);
        }
        glRotatef((50/(treeSize*treeSize)*-1), 0.0, 1.0, 0.0); 
        gluCylinder(cyl, cylWidth, cylWidth, cylHeight, 30, 30);
        glTranslatef(0.0, 0.0, cylHeight);
        break;

      case 's': //grow truffula spiral
        glColor4f(0.2,0.8,1.0,1.0);
        cylWidth = (cylWidth*4);
        glutSolidSphere((cylWidth), 30, 30);

        for (int k = 0; k < 180; k++) {
          gluCylinder(cyl, cylWidth, (cylWidth-cylChange), (setWidth*.0015), 30, 30);
          glutSolidSphere((cylWidth-cylChange), 30, 30);
          glTranslatef(0.0, 0.0, (setWidth*.0015));
          glRotatef(2, 0.0, 1.0, 0.0); 
          cylWidth = (cylWidth-cylChange);
        }
        break;

      case 'k': // user line
        gluCylinder(cyl, cylWidth, cylWidth, cylHeight, 30, 30);
        glTranslatef(0.0, 0.0, cylHeight);
        break;

      case 'r': 
        glRotatef(rotateAngle, 0.0, 1.0, 0.0); 
        break;

      case 'l': 
        glRotatef(-(rotateAngle), 0.0, 1.0, 0.0); 
        break;

      case '[': 
        glPushMatrix();
        if (userChoice == 1) {
          cylWidth = (cylWidth-cylChange);
        }
        if (userChoice == 2) {
          randomNum = ((rand() % 40) - (rand() % 40));
          glRotatef(randomNum, 1.0, 0.5, 0.0);
        }
        break;

      case ']': 
        glPopMatrix();
        if (userChoice == 1) {
          cylWidth = (cylWidth+cylChange);
        }
        if (userChoice == 3) {
          cylWidth = (setWidth/100);
        }
        break;

    }
  }
}

void drawCeltic()
{

  int growth = 0;
  int flip = 0;

  //Set Axiom
  mainString = "b";

  //Grow string as needed
  while (growth < treeSize) {
    growString(mainString);
    growth++;
  }

  while (flip < 2) {

    //tree setup
    glColor4f(0.28,0.14,0.08,1.0);

    if (flip == 0) {
      glRotatef(-90, 1.0, 0.0, 0.0); 
    }

    if (flip == 1) {
      glRotatef(180, 1.0, 0.0, 0.0); 
    }
    
    glPushMatrix();

    drawSwitch(mainString);

  flip++;
  }
}

void drawFractal()
{

  int growth = 0;

  //Set Axiom
  mainString = "x";

  //Grow string as needed
  while (growth < treeSize) {
    growString(mainString);
    growth++;
  }

  //tree setup
  glRotatef(-90, 1.0, 0.0, 0.0); 
  glTranslatef(0.0, 0.0, -2.0);
  glColor4f(0.0,0.5,0.09,1.0);

  drawSwitch(mainString);

}

void drawTruf()
{

  int growth = 0;

  //Set Axiom
  mainString = "ts";

  //Grow string as needed
  while (growth < treeSize) {
    growString(mainString);
    growth++;
  }

  //tree setup
  glRotatef(-90, 1.0, 0.0, 0.0); 
  glRotatef(25, 0.0, 1.0, 0.0); 
  glTranslatef(1.0, 0.0, -1.0);

  drawSwitch(mainString);

}


void drawUserTree()
{

  int growth = 0;

  //Set Axiom
  mainString = "k";

  //Grow string as needed
  while (growth < treeSize) {
    growString(mainString);
    growth++;
  }

  //tree setup
  glRotatef(-90, 1.0, 0.0, 0.0); 
  glTranslatef(0.0, 0.0, -2.0);
  glColor4f(0.0,0.5,0.09,1.0);

  drawSwitch(mainString);

}

// Cylinder Window Routine
void display()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gluQuadricDrawStyle(cyl, GLU_SMOOTH);

  if (userChoice == 1) {
    drawCeltic();
  }

  if (userChoice == 2) {
    drawFractal();
  }

  if (userChoice == 3) {
    drawTruf();
  }

  if (userChoice == 4) {
    drawUserTree();
  }

  glutSwapBuffers();
}

void init()
{

   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 98.0);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glColorMaterial(GL_FRONT, GL_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(40.0, 1.0, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(8.0, 0.0, 0.0,
      0.0, 0.0, 0.0,
      0.0, 1.0, 0.0);
}

int main(int argc, char **argv)
{

  std::cout << "What type of tree would you like to see?" << std::endl;
  std::cout << "Select 1 for Celtic Tree of Life, 2 for Fractal Baby's Breath, 3 for Truffula Tree, or select 4 to draw your own" << std::endl;
  std::cin >> userChoice;
  
  if (userChoice == 1) {
    std::cout << "How many recursions? (1-9)" << std::endl;
    std::cin >> treeSize;
    std::cout << "Choose a season: 1=Spring 2=Summer 3=Fall 4=Winter " << std::endl;
    std::cin >> seasonChoice;
  }

  if (userChoice == 2) {
    std::cout << "How many recursions? (1-4)" << std::endl;
    std::cin >> treeSize;
  }

  if (userChoice == 3) {
    std::cout << "How many recursions? (1-6)" <<std::endl;
    std::cin >> treeSize;
  }

  if (userChoice == 4) {
    std::cout << "With the given axiom k, create your own your rule with the characters below. ex. kkl[lkrkrk]r[rklklk]" << std::endl;
    std::cout << "k = draw a line" << std::endl;
    std::cout << "y = draw a flower" << std::endl;
    std::cout << "l = rotate left (you can set rotate angle after writing rule)" << std::endl;
    std::cout << "r = rotate right (you can set rotate angle after writing rule)" << std::endl;
    std::cout << "[ = pushes the matrix" << std::endl;
    std::cout << "[ = pops the matrix" << std::endl;
    std::cin >> userRule;
    std::cout << "Set rotate angle (float):" << std::endl;
    std::cin >> userAngle;
    std::cout << "How many recursions?" << std::endl;
    std::cin >> treeSize;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  
  // Create Cube window
  window_cube = glutCreateWindow("Viewport");
  glutDisplayFunc(display);
  // glutMotionFunc(motion);
  // glutMouseFunc(mouse);
  glutReshapeWindow(WINDOW_SIZE, WINDOW_SIZE);
  glutKeyboardFunc(handleKeys);
  init();

  glutMainLoop();
  return 0;
}