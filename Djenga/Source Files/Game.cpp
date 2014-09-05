/*
* 
* Project: VR Wall
* Author: Jing, Aditya
* Game.cpp
*
*/

#include "../Header Files/Game.h"


float Game::PI = 3.1459;
int Game::NUM_BLOCKS = 6;

// Constructor 
// Initialize the blocks as well as the openGL parameters
Game::Game() : win(640,480,"Djenga",45,1.0,-1.0) {
   Blocks = new Block[NUM_BLOCKS];
   
   initializeGL();
   initBlocks();
   
}

Game::~Game(){
   delete [] Blocks;
}


// Connect to the input devices
void Game::connectToInputs(const string& bluetoothAddr, const string& wandAddr){
   
   VClient.connectToServer(wandAddr);
   Wii.connectTo(bluetoothAddr);
}

// Initialize the blocks
// Sets the initial position and the dimensions
void Game::initBlocks(){

   vec3 initialPos[6];	
   initialPos[0] = vec3(0.2, 0.0 , 0.0);
   initialPos[1] = vec3(0.5, 1.0 , 0.0);
   initialPos[2] = vec3(-0.4, 1.0 , 0.0);
   initialPos[3] = vec3(0, 0.25 , 0);
   initialPos[4] = vec3(0.5, 0 , 0);
   initialPos[5] = vec3(0.5, 1 , 0);
   for (int i = 0; i < NUM_BLOCKS; i++){
	      Blocks[i].InitBlock(initialPos[i], 0.5, 0.5, 0.5);
	      Blocks[i].SetBlockIndex(i);
	      Block::AddToList(&Blocks[i]);
   }
}


// Initializes the OpenGL parameters

void Game::initializeGL(){

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   
   glutInitWindowSize(win.width,win.height);
   glutInitWindowPosition(100, 100);
   glutCreateWindow((win.title).c_str());
   glutDisplayFunc(Draw);
   glutTimerFunc(100, updateState, 0);
   glMatrixMode(GL_PROJECTION);							
   glViewport(0, 0, win.width, win.height);					
   glMatrixMode(GL_PROJECTION);							
   
   glLoadIdentity();								
   GLfloat aspect = (GLfloat) win.width / win.height;
   gluPerspective(win.fieldOfViewAngle, aspect, win.z_near, win.z_far);		
   glMatrixMode(GL_MODELVIEW);							
   glShadeModel( GL_SMOOTH );
   
   glClearDepth( 1.0f );							
   glEnable( GL_DEPTH_TEST );
   glDepthFunc( GL_LEQUAL );
   glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );				
   glClearColor(0.0, 0.0, 0.0, 1.0);

}


// Draws the scene, the pointer and the blocks
// as per their updated position in space

void Game::Draw()
{

   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glTranslatef(0.0f,0.0f,-3.0f);
   glRotatef(alpha,0,1,0);
    
   theScene.Draw(win.z_near-win.z_far,2);

   for(int i=0;i<NUM_BLOCKS;i++){
      drawBlock(Blocks[i]);    
   }

   glColor3f(1.0f,0.0f,0.0f);
   glPointSize(5.0f);
   glBegin(GL_POINTS);
   glVertex3f(point[0],point[1],point[2]);
	
   glEnd();
   glutSwapBuffers();

}

// This timer function is called repeatedly
// with the time interval between two calls 
// specified by "value"
// It reads the data from the input devices
// and updates the position of the blocks. The function terminates after asking openGL to refresh the display

void Game::updateState(int value){
 
   VClient.readData();
   float x_pos = 2*VClient.getXData();
   float y_pos = 2*(VClient.getYData()*sin(0.263) - VClient.getZData()*cos(0.263));
   float z_pos = 2*(VClient.getZData()*sin(0.263) + VClient.getYData()*cos(0.263));
   int theButtonState = Wii.GetButtonId();
  
   if (theButtonState == 8){
      for (int i=0; i< NUM_BLOCKS;i++){
         if (Blocks[i].IsInside(point[0], point[1], point[2])){
            Blocks[i].held_flag = 1;
         }
         else{
            Blocks[i].held_flag = 0;
         }
      }
   }
   else{
      for (int i=0; i< NUM_BLOCKS;i++){	
         Blocks[i].held_flag = 0;	
      }
   }
   if (theButtonState == 512){
      alpha = (alpha < 90) ? alpha + 10 : alpha;
   }
   else if (theButtonState == 256){
	alpha = (alpha > 0) ? alpha - 10 : alpha;
   }
   
   point[0] = x_pos*cos(alpha*PI/180) + z_pos*sin(alpha*PI/180);
   point[1] = y_pos;
   point[2] = z_pos*cos(alpha*PI/180) - x_pos*sin(alpha*PI/180);


   for (int i = 0; i < NUM_BLOCKS; i++){		
	 Blocks[i].Update(0.01, theScene);
   }

   glutTimerFunc(100,updateState,0);
   glutPostRedisplay();
}

// Launch the OpenGL main loop
void Game::startGame(){
   glutMainLoop();
}

// Communicates the location of the corner points of the block to openGL
void Game::drawBlock(Block& b){
   
   int width, height;
   int * data;
   FILE * file;

   GLuint texture;
   Block::BlockGrid& grid = b.m_vparticles;
   
   glGenTextures( 1, &texture );
   glBindTexture( GL_TEXTURE_2D, texture );
   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		
   width = 543;
   height = 612;

   data = (int*)malloc( width * height * 3 );

   file = fopen( "24bit.bmp", "rb" );
   fread( data, width * height * 3, 1, file );
   fclose( file );
   gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );

   free( data );
   glEnable( GL_TEXTURE_2D );
   glBindTexture( GL_TEXTURE_2D, texture );

   
   glBegin(GL_QUADS);
   glTexCoord2d(0,0);glVertex3f((b.GetParticle(grid,0,0,0)).position[0],(b.GetParticle(grid,0,0,0)).position[1],(b.GetParticle(grid,0,0,0)).position[2]);
   glTexCoord2d(0,1);glVertex3f((b.GetParticle(grid,4,0,0)).position[0],(b.GetParticle(grid,4,0,0)).position[1],(b.GetParticle(grid,4,0,0)).position[2]);
   glTexCoord2d(1,1);glVertex3f((b.GetParticle(grid,4,4,0)).position[0],(b.GetParticle(grid,4,4,0)).position[1],(b.GetParticle(grid,4,4,0)).position[2]);
   glTexCoord2d(1,0);glVertex3f((b.GetParticle(grid,0,4,0)).position[0],(b.GetParticle(grid,0,4,0)).position[1],(b.GetParticle(grid,0,4,0)).position[2]);

   glTexCoord2d(0,0);glVertex3f((b.GetParticle(grid,0,0,0)).position[0], (b.GetParticle(grid,0,0,0)).position[1], (b.GetParticle(grid,0,0,0)).position[2]);
   glTexCoord2d(0,1);glVertex3f((b.GetParticle(grid,4,0,0)).position[0],(b.GetParticle(grid,4,0,0)).position[1],(b.GetParticle(grid,4,0,0)).position[2]);
   glTexCoord2d(1,1);glVertex3f((b.GetParticle(grid,4,0,4)).position[0],(b.GetParticle(grid,4,0,4)).position[1],(b.GetParticle(grid,4,0,4)).position[2]);
   glTexCoord2d(1,0);glVertex3f((b.GetParticle(grid,0,0,4)).position[0],(b.GetParticle(grid,0,0,4)).position[1],(b.GetParticle(grid,0,0,4)).position[2]);

   glTexCoord2d(0,0);glVertex3f((b.GetParticle(grid,0,0,4)).position[0], (b.GetParticle(grid,0,0,4)).position[1], (b.GetParticle(grid,0,0,4)).position[2]);
   glTexCoord2d(0,1);glVertex3f((b.GetParticle(grid,4,0,4)).position[0],(b.GetParticle(grid,4,0,4)).position[1],(b.GetParticle(grid,4,0,4)).position[2]);
   glTexCoord2d(1,1);glVertex3f((b.GetParticle(grid,4,4,4)).position[0],(b.GetParticle(grid,4,4,4)).position[1],(b.GetParticle(grid,4,4,4)).position[2]);
   glTexCoord2d(1,0);glVertex3f((b.GetParticle(grid,0,4,4)).position[0],(b.GetParticle(grid,0,4,4)).position[1],(b.GetParticle(grid,0,4,4)).position[2]);

   glTexCoord2d(0,0);glVertex3f((b.GetParticle(grid,0,0,0)).position[0], (b.GetParticle(grid,0,0,0)).position[1], (b.GetParticle(grid,0,0,0)).position[2]);
   glTexCoord2d(0,1);glVertex3f((b.GetParticle(grid,4,4,0)).position[0],(b.GetParticle(grid,4,4,0)).position[1],(b.GetParticle(grid,4,4,0)).position[2]);
   glTexCoord2d(1,1);glVertex3f((b.GetParticle(grid,4,4,4)).position[0],(b.GetParticle(grid,4,4,4)).position[1],(b.GetParticle(grid,4,4,4)).position[2]);
   glTexCoord2d(1,0);glVertex3f((b.GetParticle(grid,0,4,4)).position[0],(b.GetParticle(grid,0,4,4)).position[1],(b.GetParticle(grid,0,4,4)).position[2]);

   glTexCoord2d(0,0);glVertex3f((b.GetParticle(grid,0,0,0)).position[0], (b.GetParticle(grid,0,0,0)).position[1], (b.GetParticle(grid,0,0,0)).position[2]);
   glTexCoord2d(0,1);glVertex3f((b.GetParticle(grid,0,4,0)).position[0],(b.GetParticle(grid,0,4,0)).position[1],(b.GetParticle(grid,0,4,0)).position[2]);
   glTexCoord2d(1,1);glVertex3f((b.GetParticle(grid,0,4,4)).position[0],(b.GetParticle(grid,0,4,4)).position[1],(b.GetParticle(grid,0,4,4)).position[2]);
   glTexCoord2d(1,0);glVertex3f((b.GetParticle(grid,0,0,4)).position[0],(b.GetParticle(grid,0,0,4)).position[1],(b.GetParticle(grid,0,0,4)).position[2]);

   glTexCoord2d(0,0);glVertex3f((b.GetParticle(grid,4,0,0)).position[0],(b.GetParticle(grid,4,0,0)).position[1],(b.GetParticle(grid,4,0,0)).position[2]);
   glTexCoord2d(0,1);glVertex3f((b.GetParticle(grid,4,4,0)).position[0],(b.GetParticle(grid,4,4,0)).position[1],(b.GetParticle(grid,4,4,0)).position[2]);
   glTexCoord2d(1,1);glVertex3f((b.GetParticle(grid,4,4,4)).position[0],(b.GetParticle(grid,4,4,4)).position[1],(b.GetParticle(grid,4,4,4)).position[2]);
   glTexCoord2d(1,0);glVertex3f((b.GetParticle(grid,4,0,4)).position[0],(b.GetParticle(grid,4,0,4)).position[1],(b.GetParticle(grid,4,0,4)).position[2]);

			
   glEnd();
   glDisable( GL_TEXTURE_2D );
}
