///////////////////////////////////////////////////////////////////////////////
///                                                                         ///
///     �w�Дԍ�:2072088�@   �����F�R�{�E��                                 ///
///                                                                         ///
///     �r�W���A���C�[�[�V���� �ŏI�ۑ�                                     ///
///                                                                         ///
///                                                                         ///
///     �v���O�������p��                                                    ///
///         �u�R���s���[�^�O���t�B�b�N�X OpenGL action3.c�@�i�Ñ������j�v   ///
///         https://www.mi.tj.chiba-u.jp/~tsumura/OpenGL/action3.c          ///
///                                                                         ///                                                                     ///
///////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

// �u���b�N��
//#define�͑�1�����������2�����Ƃ��Ĉ����Ă����
#define	I	43  //�󒆃u���b�N�z��p�ϐ�
#define O   195 //���u���b�N�p�z��ϐ�
#define D   6   //�y�Ǘp�z��ϐ�

// �G��
#define	J	7
#define RAD (M_PI / 180.0)

//mySolidSylinder�p
#define PI2 2.0*3.1415926534

// ���@�̈ʒu
//typedef struct�͍\���̂�Geometry�Ɩ������邱�Ƃō���̕ϐ��錾����struct�L�[���[�h�̋L�q���ȗ��ł���D
typedef struct {
  float ShiftX;
  float ShiftY;
  float ShiftZ;
  float RotateX;
  float RotateY;
  float RotateZ;
} Geometry;
Geometry Cube;

// �t���O�Ȃǂ̐錾�Ə�����
char  AnimationFlag = 0;
int   xBegin, yBegin;
int   PressButton;
int   i=0,m=0,n=0;
int   jump = 0;
char  left = 0;
char		right = 0;
char		direction	=	0;
char		die_flag	=	99;
int		limit_left[I] ={1};
int		limit_right[I] ={1};
int		limit_up[I] ={1};
int		limit_down[I] ={1};
int		t_limit_left	=	1;
int		t_limit_right	=	1;
int		fall=1,fall_p=0;
int		rise=1,rise_p=0;
double          Rotate=0;
double		mini=0,max=100;
double		Vy;

// ���ԕϐ��̐錾�Ə�����
double		ntime=0,ptime=0;
double		die_ntime=0,die_ptime=0;

// �u���b�N�ƓG�̐錾�Ə�����
double		block_x[I]={6,10,11,12,12,13,14,65,66,67,68,69,70,71,72,73,74,75,80,81,82,83,83,89,90,95,98,98,101,107,110,111,112,117,118,118,119,119,120,158,159,160,161};
double		block_y[I]={3,3,3,3,7,3,3,3,3,3,7,7,7,7,7,7,7,7,7,7,7,7,3,3,3,3,3,7,3,3,7,7,7,7,7,3,7,3,7,3,3,3,3};
double      fblock_x[O] = {-10, -9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77};
double      dblock_x[D] = { 18.5,28.5,36.5,47.5,153.5,169.5 };
double      dblock_height[D] = { 2,3,4,4,2,2 };
double		block_z[I]={0};
double		enemy_x[J]={0};	
double		enemy_y[J]={0};	
double		enemy_z[J]={0};	
double		enemy_x2[J]={0};
double		enemy_y2[J]={0};	
double		bL[I],bR[I],bU[I],bD[I]/*,bF[I],bB[I]*/,R[J],R2[J];
double		nView[2];
int		jcount=0;
double          Cv=0.03;
float CameraAzimuth   = 90.0;   /* �J�����̈ʒu�i���ʊp�j */
float CameraElevation = 0.0;    /* �J�����̈ʒu�i�p�j */
float CameraDistance  = 5.0;    /* �J�����̈ʒu�i���_����̋����j */
float CameraX = 0.0;            /* �J�����̈ʒu�iX���W�j */
float CameraY = 0.0;            /* �J�����̈ʒu�iY���W�j */
float CameraZ = 5.0;            /* �J�����̈ʒu�iZ���W�j */


//wire�~���֐�
void myWireCylinder(float r, float h, int n)
{
    float x, y, z, dq;
    int i;

    dq = PI2 / (float)n;
    y = 0.5 * h;
    glPushMatrix();
    glRotatef(-dq * 180.0 / PI2, 0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    for (i = 0; i < n; i++) {
        x = r * cos(dq * (float)i);
        z = r * sin(dq * (float)i);
        glVertex3f(x, y, z);
        glVertex3f(x, -y, z);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (i = 0; i < n; i++) {
        x = r * cos(dq * (float)i);
        z = r * sin(dq * (float)i);
        glVertex3f(x, y, z);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (i = 0; i < n; i++) {
        x = r * cos(dq * (float)i);
        z = r * sin(dq * (float)i);
        glVertex3f(x, -y, z);
    }
    glEnd();
    glPopMatrix();
}


//�h��Ԃ��~���֐�
void mySolidCylinder(float r, float h, int n)
{
    float x, y, z, dq;
    int i;

    glEnable(GL_NORMALIZE);
    dq = PI2 / (float)n;
    y = 0.5 * h;
    glPushMatrix();
    glRotatef(-dq * 180.0 / PI2, 0.0, 0.1, 0.0);
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= n; i += 1) {
        x = r * cos(dq * (float)i);
        z = r * sin(dq * (float)i);
        glNormal3f(x, 0, z);
        glVertex3f(x, y, z);
        glVertex3f(x, -y, z);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    for (i = 0; i < n; i += 1) {
        x = r * cos(dq * (float)i);
        z = r * sin(dq * (float)i);
        glVertex3f(x, -y, z);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    for (i = 0; i < n; i += 1) {
        x = r * cos(dq * (float)i);
        z = r * sin(dq * (float)i);
        glVertex3f(x, y, z);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_NORMALIZE);
}


// �`��֐�(���@�̎���)
void drawString3D(const char *str, float charSize, float lineWidth)
{
  glPushMatrix();
  glPushAttrib(GL_LINE_BIT);    //�J�����g�̃��C�e�B���O�v���p�e�B���Z�[�u
  glScaled(0.001 * charSize, 0.001 * charSize, 0.01);
  glLineWidth(lineWidth);
  while(*str){
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *str);
    ++str;
  }
  glPopAttrib();    //�Z�[�u���ꂽ�v���p�e�B�����X�g�A
  glPopMatrix();
}


void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //gl_depth_buffer_bit�ŉB�ʏ���
  glPushMatrix ();
  
  /* ���_�̐ݒ� */
  gluLookAt(  Cube.ShiftX+CameraX, Cube.ShiftY+CameraY+3, Cube.ShiftZ+CameraZ+5,  /* �J�����̈ʒu */
	      Cube.ShiftX, Cube.ShiftY+3, Cube.ShiftZ,  /* �����_�̈ʒu */
	      0.0, 1.0, 0.0); /* �J����������̃x�N�g�� */ 
  
  glEnable(GL_DEPTH_TEST); 

  //�w�i�̐��F�̕`��
  glPushMatrix();
  glColor3f(0.39, 0.58, 0.93);
  glTranslatef(Cube.ShiftX, Cube.ShiftY, Cube.ShiftZ+5);
  glutSolidSphere(15, 10, 10);
  glPopMatrix();
 
  // �������(�����̕`��)
  if(die_flag==99){
    glPushMatrix ();
    glColor3f( 1.0, 0.0, 0.0 );  
    glTranslatef(-7, 4.0, 0); 
    drawString3D("Press ' s ' to start", 10.0, 2.0); 
    glPopMatrix ();   
  }
  
  // ���@�̕`��
  glPushMatrix (); 
  glTranslatef(Cube.ShiftX,Cube.ShiftY,Cube.ShiftZ);
  glRotatef(Rotate,0,0,1.0);
  if(die_flag==2){
    glColor3f( 1.0-die_ptime, 1.0-die_ptime, 1.0 ); 
  }
  else if(die_flag==0){
    glColor3f( 1.0, 1.0-die_ptime, 1.0-die_ptime ); 	  
  }
  else{
    glColor3f( 1.0, 1.0, 1.0 );   
  }

  glutWireSphere(0.5, 10, 10);
  glPopMatrix ();   

  
  // �G�̕`��
  for(i=0;i<J;i++){
    glPushMatrix ();   //�����痈��G�̕`��
    glColor3f( 0.0,0.0,1.0 ); 
    glRotatef(-90,0.0,1.0,0.0);
    glTranslatef(0.0,enemy_y[i],enemy_x[i]);
    glRotatef(ptime*100,0.0,0.0,1.0);
    glutWireCone(0.25,0.5,10,2);
    glPopMatrix ();
    
    glPushMatrix ();    //�����炭��G�̕`��  
    glColor3f( 0.0,1.0,0.0 ); 
    glTranslatef(enemy_x2[i],enemy_y2[i],enemy_z[i]);
	glRotatef(ptime*100,0.0,0.0,1.0);
	glutWireCone(0.25,0.5,10,2);
	glPopMatrix ();
  }
  
  // ���u���b�N�̕`��
      for (i = 0; i < O; i++) {
          glPushMatrix();
          glTranslatef(fblock_x[i], -1, 0);
          glColor3f(0.96, 0.64, 0.38);
          glutSolidCube(1.0);
          glColor3f(0, 0, 0);
          glutWireCube(1.0);
          glLineWidth(5.0);   //�u���b�N�̐��̕`��
          glScaled(0.02, 1.0, 1.0);
          glutWireCube(1.0);  //�c���̕`��
          glScaled(50, 0, 1.0);
          glutWireCube(1.0);
          glLineWidth(1.0);   //���̑��������Ƃɖ߂�
          glPopMatrix();
      }

      // �y�ǂ̕`��
      for (i = 0; i < D; i++) {
          glPushMatrix();
          glTranslatef(dblock_x[i], dblock_height[i]/2-0.5, 0);
          glColor3f(0.13, 0.55, 0.13);
          mySolidCylinder(1, dblock_height[i],24);
          glColor3f(0, 0, 0);
          myWireCylinder(1, dblock_height[i], 24);
          glPopMatrix();
      }

      //�y�ǂ̉��̕`��
      for (i = 0; i < D; i++) {
          glPushMatrix();
          glTranslatef(dblock_x[i], dblock_height[i] / 2 + 1 , 0);
          glColor3f(0.13, 0.55, 0.13);
          mySolidCylinder(1.2, dblock_height[i]/3, 24);
          glColor3f(0, 0, 0);
          myWireCylinder(1.2, dblock_height[i] / 3, 24);
          glPopMatrix();
      }
  

  // �󒆃u���b�N�̕`��
  for(i=0;i<I;i++){
    glPushMatrix (); 
    glTranslatef(block_x[i],block_y[i],block_z[i]);
    if(i!=I-1){
      glColor3f( 0.50, 0.25, 0.25 ); 
    }
    else{
      glColor3f( 0.5, 1.0, 0.5 ); 
    }glutSolidCube(1.0);
    glColor3f( 0, 0, 0 ); 
    glutWireCube(1.0);
    glLineWidth(5.0);   //�u���b�N�̐��̕`��
    glScaled(1.0, 0.33, 1.0);
    glutWireCube(1.0);  //�����̕`��
    glScaled(0.5, 1.0, 1.0);
    glutWireCube(1.0);  //�����̎l�p�̕`��
    glLineWidth(1.0);   //���̑��������Ƃɖ߂�
    glPopMatrix (); 
  }

  glDisable(GL_DEPTH_TEST);
  glPopMatrix ();                   
  glutSwapBuffers();
}


void timer(int value)
 {
   
   switch	(die_flag)	{
     
     // �ʏ펞
   case	1:
     
     // �u���b�N�Ƃ̓����蔻��
     for(i=0;i<I;i++){
       
       // ���E�㉺�̔���p
       bL[i]	=	block_x[i]-Cube.ShiftX;
       bR[i]	=	Cube.ShiftX-block_x[i];
       bU[i]	=	Cube.ShiftY-block_y[i];
       bD[i]	=	block_y[i]-Cube.ShiftY;
       
       // ����
       if(bL[i]<1 && -0.5<bL[i] && bU[i]<1 && bD[i]<1){
           limit_right[i]	=	0;
       }
       else{
           limit_right[i]	=	1;
           t_limit_right		=	1;
       }		    
       
       // �E��
       if(-0.5<bR[i] && bR[i]<1 && bU[i]<1 && bD[i]<1){
	 limit_left[i]	=	0;
       }
       else{
	 limit_left[i]	=	1;
	 t_limit_left		=	1;
       }
       
       // ���
       if(-0.75<bL[i] && bL[i]<0.75 && -0.75<bR[i] && bR[i]<0.75 && bU[i]<1 && 0<bU[i]){
	 mini	=	block_y[i]+1;
	 fall	=	0;
	 fall_p	=	block_x[i];
	 if(i==I-1){
	   die_flag=2;
	 }
       }

       // ��������
       if(Cube.ShiftX<fall_p-0.9 || fall_p+0.9<Cube.ShiftX || bU[i]>1 && -1>bU[i]){
	 fall	=	1;
       }

       // ����
       if(-0.75<bL[i] && bL[i]<0.75 && -0.75<bR[i] && bR[i]<0.75 && 0.75<bD[i] && 0<bD[i]){
	 if(block_y[i]<max){		
	   max	=	block_y[i]-1;
	 }
	 rise	=	0;block_x[i];
       }
       // ��ړ�����
       if(Cube.ShiftX<rise_p-0.9 || rise_p+0.9<Cube.ShiftX){
	 rise	=	1;
       }
     }
     
     // �ړ��t���O
     for(i=0;i<I;i++){	
       t_limit_right	*=	limit_right[i];				
     }
     for(i=0;i<I;i++){	
       t_limit_left	*=	limit_left[i];				
     }

     // �ړ��͈͂̐���(�㉺)
     if(fall==1){
       mini=0;
     }
     if(rise==1){
       max=100;
     }

     // ���@�̉�]
     if (direction == 0) {  //�E�Ɉړ����Ă���Ƃ��͉E��]
         Rotate -= 1;
     }
     else {
         Rotate += 1;
     }
     if (Cube.RotateZ > 360.0) {
         Cube.RotateZ -= 360.0;
     }
     
     // ���@�̈ړ�(�E)
     if(right==1 && t_limit_right == 1){
       Cube.ShiftX+=Cv;
       direction=0;
     }
     
     // ���@�̈ړ�(��)
     if(left==1 && t_limit_left == 1){
       Cube.ShiftX-=Cv;
       direction=1;
     }
          
     // �W�����v�Ɨ����̐���
     Cube.ShiftY	+=	Vy;
     Vy	-=	0.00025;

     if(Cube.ShiftY<=mini){
       Cube.ShiftY=mini;
       Vy		=	0;
       jump	=	0;
       jcount	=	0;
     }
     else if(max<=Cube.ShiftY){
       Cube.ShiftY=max;
     }
     
     // ���̎��S����
     if(Cube.ShiftX>-10 && Cube.ShiftY==-6){
       die_flag=0;  
     }
		  
     // �G�Ƃ̓����蔻��
     for(i=0;i<J;i++){
       R[i]	=	sqrt(pow(Cube.ShiftX+enemy_x[i],2.0)+pow(Cube.ShiftY-enemy_y[i],2.0));  //������̓G�Ƃ̓����蔻��
       if(R[i]<0.5){
	 die_flag=0;
       }
       R2[i]	=	sqrt(pow(Cube.ShiftX-enemy_x2[i],2.0)   //������̓G�Ƃ̓����蔻��
			     +pow(Cube.ShiftY-enemy_y2[i],2.0)
			     +pow(Cube.ShiftZ-enemy_z[i],2.0));
       if(R2[i]<0.5){
	 die_flag=0;
		    }
     }
     
     // �G�̈ړ�
     for(i=0;i<J;i++){
       enemy_x[i]	+=	0.0025;
       enemy_z[i]	+=	0.0025;
       if(enemy_x[i]>0){
	 enemy_y[i]	=	1+rand()%8;	
	 enemy_x[i]	=	enemy_x[i]-30;	
       }
       if(enemy_z[i]>5){
	 enemy_y2[i]	=	1+rand()%8;	
	 enemy_x2[i]	=	10+rand()%10;	
	 enemy_z[i]	=       -5;
		    }
     }

     // ���ԕϐ��̍X�V
     ntime	=	ntime-(ntime-0.1);
     ptime	+=	ntime;

     break;
     
     // ���S���ƃN���A��
   case	0:
   case	2:
     ntime	=	ntime-(ntime-0.1);
     ptime	+=	ntime;
     die_ntime	=	die_ntime-(die_ntime-0.005);
     die_ptime	+=	die_ntime;
     if(die_ptime>1){
       exit(0);
     }		
     break;
   }
   
   
   glutPostRedisplay();
   glutTimerFunc(3 , timer , 0);
   
   
 }




void keyboard(unsigned char key, int x, int y )
{
  switch( key ) {

    // �X�y�[�X�ŃW�����v
  case ' ':
	  jcount++;
	  if(jcount<2){
		Vy	=	0.046;
	  }	 
	  jump=1; 
    break;

    // "s"�ŊJ�n
  case 's':
    die_flag=1;
    break;
  }
  glutPostRedisplay();
  
  x = y = 0;
} 


void mouseButton(int button, int state, int x, int y )
{
  if (state == GLUT_DOWN)
  {
    switch(button)
    {

      // ���N���b�N�ō��ړ�
    case GLUT_LEFT_BUTTON:
	    PressButton = 0;
		left=1;
      break;

      // �^���N���b�N�Ŏ��_�ύX
    case GLUT_MIDDLE_BUTTON:
      PressButton = button;
      break;
    
      // �E�N���b�N�ŉE�ړ�
    case GLUT_RIGHT_BUTTON:
	    PressButton = 0;
		right=1;
	  break;
    }
 
    xBegin = x;
    yBegin = y;
  }
  else{
	right=0;
	left=0;
  }
}



void mouseDrag(int x, int y)
{
  int xMove = x - xBegin;
  int yMove = y - yBegin;
 
  switch (PressButton) {

    // �J�����̈ړ�
  case GLUT_MIDDLE_BUTTON:
      CameraAzimuth   += (float)xMove / 2.0;
      CameraElevation += (float)yMove / 2.0;
      if (CameraElevation >  90.0){
	CameraElevation =  90.0;
	    }
      if (CameraElevation < -90.0){
	CameraElevation = -90.0;	
      }
    break;
    
  }
  
  CameraX = CameraDistance * cos(CameraAzimuth * RAD) * cos(CameraElevation * RAD);
  CameraY = CameraDistance * sin(CameraElevation * RAD);
  CameraZ = CameraDistance * sin(CameraAzimuth * RAD) * cos(CameraElevation * RAD); 
  
  xBegin = x;
  yBegin = y;
  
  glutPostRedisplay();
}



void myInit (char *windowTitle)
{
  int winWidth  = 400;
  int winHeight = 400;

  float aspect = (float)winWidth / (float)winHeight;

  glutInitWindowPosition(0, 0);                 
  glutInitWindowSize(winWidth, winHeight);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
  glutCreateWindow(windowTitle); 
  glClearColor (0.0, 0.0, 0.0, 1.0);

  glutKeyboardFunc(keyboard);   
  glutMouseFunc   (mouseButton); 
  glutMotionFunc  (mouseDrag); 
  glutDisplayFunc (display);
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity(); 
  gluPerspective(90.0, aspect, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glutTimerFunc(15 , timer , 0);    //�w��̎��Ԍo�߂ŃR�[���o�b�N�֐����Ăяo��

  
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    myInit(argv[0]);

    // ���@�ʒu�̏�����
    Cube.ShiftX = 0;
    Cube.ShiftY = 0;
    Cube.ShiftZ = 0;
    Cube.RotateX = 0;
    Cube.RotateY = 0;
    Cube.RotateZ = 0;
    
    //�u���b�N���m�F�̂��߁i������̂߂�ǂ��D�D�D�j
    int length = sizeof(block_x) / sizeof(block_x[0]);
    printf("length of block_x is: %d",length);

    // �G�ʒu(��)�̏�����
    for (i = 0; i < J; i++) {
        enemy_x[i] = 30 + rand() % 30;
        enemy_y[i] = rand() % 10;
    }

    // �G�ʒu(��)�̏�����
    for (i = 0; i < J; i++) {
        enemy_z[i] = -5 + rand() % 10;
        enemy_x2[i] = 10 + rand() % 10;
        enemy_y2[i] = rand() % 10;
    }

    glutMainLoop();

    return(0);
}