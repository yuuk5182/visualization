
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

// ブロック数
#define	I	11

// 敵数
#define	J	7
#define RAD (M_PI / 180.0)

// 自機の位置
typedef struct {
  float ShiftX;     
  float ShiftY;
  float ShiftZ;
  float RotateX;
  float RotateY;
  float RotateZ;
} Geometry;
Geometry Cube;

// フラグなどの宣言と初期化
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

// 時間変数の宣言と初期化
double		ntime=0,ptime=0;
double		die_ntime=0,die_ptime=0;

// ブロックと敵の宣言と初期化
double		block_x[I]={5,7,19,10,12,22,14,11,25,14,22};
double		block_y[I]={0,0,1,1,2,2,5,6,5,9,8};
double		block_z[I]={0};
double		enemy_x[J]={0};	
double		enemy_y[J]={0};	
double		enemy_z[J]={0};	
double		enemy_x2[J]={0};
double		enemy_y2[J]={0};	
double		bL[I],bR[I],bU[I],bD[I]/*,bF[I],bB[I]*/,R[J],R2[J];
double		nView[2];
int		jcount=0;
double          Cv=0.01;
float CameraAzimuth   = 90.0;   /* カメラの位置（方位角） */
float CameraElevation = 0.0;    /* カメラの位置（仰角） */
float CameraDistance  = 5.0;    /* カメラの位置（原点からの距離） */
float CameraX = 0.0;            /* カメラの位置（X座標） */
float CameraY = 0.0;            /* カメラの位置（Y座標） */
float CameraZ = 5.0;            /* カメラの位置（Z座標） */

// 関数宣言
void display(void);
void geometrySet(Geometry geom);
void keyboard(unsigned char key, int x, int y );
void mouseButton(int button, int state, int x, int y );
void mouseDrag(int x, int y);
void myInit (char *windowTitle);


/***********************************************************
|  関数：main()
|  説明：メイン関数
|  引数：int argc       実行時引数の数
|  引数：char** argv    実行時引数の内容（文字列配列）
|  戻値：int            0:正常終了
***********************************************************/
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  myInit(argv[0]);

  // 自機位置の初期化
  Cube.ShiftX = 0;
  Cube.ShiftY = 0;
  Cube.ShiftZ = 0;
  Cube.RotateX = 0;
  Cube.RotateY = 0;
  Cube.RotateZ = 0;  

  // 敵位置(青)の初期化
  for(i=0;i<J;i++){
	enemy_x[i]	=	30+rand()%30;
	enemy_y[i]	=	rand()%10;
  }

  // 敵位置(緑)の初期化
  for(i=0;i<J;i++){
	enemy_z[i]	=	-5+rand()%10;
	enemy_x2[i]	=	10+rand()%10;
	enemy_y2[i]	=	rand()%10;
  }

  glutMainLoop(); 
  
  return( 0 );
}

// 描画関数(決まってる)
void drawString3D(const char *str, float charSize, float lineWidth)
{
  glPushMatrix();
  glPushAttrib(GL_LINE_BIT);
  glScaled(0.001 * charSize, 0.001 * charSize, 0.01);
  glLineWidth(lineWidth);
  while(*str){
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *str);
    ++str;
  }
  glPopAttrib();
  glPopMatrix();
}

/**********************************************************
|  関数：display()
|  説明：「１枚の」グラフィック描画イベント処理
|  引数：なし
|  戻値：なし
***********************************************************/
void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix ();
  
  /* 視点の設定 */
  gluLookAt(  Cube.ShiftX+CameraX, Cube.ShiftY+CameraY+3, Cube.ShiftZ+CameraZ,  /* カメラの位置 */
	      Cube.ShiftX, Cube.ShiftY+3, Cube.ShiftZ,  /* 注視点の位置 */
	      0.0, 1.0, 0.0); /* カメラ上方向のベクトル */ 
  
  glEnable(GL_DEPTH_TEST);    
 
  // 初期状態(文字の描画)
  if(die_flag==99){
    glPushMatrix ();
    glColor3f( 1.0, 1.0, 1.0 );  
    glTranslatef(-3.5, 4.0, 0); 
    drawString3D("Press ' s ' to start", 5.0, 2.0); 
    glPopMatrix ();   
  }
  
  // 自機の描画
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
  glutWireSphere (0.4,5.0,2.0);
  glPopMatrix ();   
  
  // 初期位置の床
  glPushMatrix (); 
  glColor3f( 0.0,1.0,0.0 ); 
  glTranslatef(0.0,-0.5,0.0);
  glScalef(1.0,0.1,1.0);
  if(Cube.ShiftX<0.1 && -0.1<Cube.ShiftX){
    glutSolidCube(1.0);
  }
  else{
    glutWireCube(1.0);
  }
  glPopMatrix ();
  
  // 赤床の描画
  for(i=0;i<I;i++){
    glPushMatrix ();   
	glColor3f( 1.0,0.0,0.0 ); 
	glTranslatef(55.5,-0.5,0.0);
	glScalef(100.0,0.1,5.0);
	glutSolidCube(1.0);
	glPopMatrix ();
  }
  
  // 敵の描画
  for(i=0;i<J;i++){
    glPushMatrix ();   
    glColor3f( 0.0,0.0,1.0 ); 
    glRotatef(-90,0.0,1.0,0.0);
    glTranslatef(0.0,enemy_y[i],enemy_x[i]);
    glRotatef(ptime*100,0.0,0.0,1.0);
    glutWireCone(0.25,0.5,10,2);
    glPopMatrix ();
    
    glPushMatrix ();   
    glColor3f( 0.0,1.0,0.0 ); 
    glTranslatef(enemy_x2[i],enemy_y2[i],enemy_z[i]);
	glRotatef(ptime*100,0.0,0.0,1.0);
	glutWireCone(0.25,0.5,10,2);
	glPopMatrix ();
  }
  
  // ブロックの描画
  for(i=0;i<I;i++){
    glPushMatrix (); 
    glTranslatef(block_x[i],block_y[i],block_z[i]);
    if(i!=I-1){	 
      glColor3f( 0.50, 0.25, 0.25 ); 
    }
    else{
      glColor3f( 0.5, 1.0, 0.5 ); 
    }glutSolidCube(1.0);
    glColor3f( 1.0, 1.0, 0.0 ); 
    glutWireCube(1.0);
    glPopMatrix (); 
  }

  glDisable(GL_DEPTH_TEST);
  glPopMatrix ();                   
  glutSwapBuffers();
}

/***********************************************************
|  関数：timer(int timerID)
|  説明：タイマー（設定時間経過）イベント処理
|  引数：int timerID    イベントが発生したタイマーの識別ID
|  戻値：なし
***********************************************************/
void timer(int value)
 {
   
   switch	(die_flag)	{
     
     // 通常時
   case	1:
     
     // ブロックとの当たり判定
     for(i=0;i<I;i++){
       
       // 左右上下の判定用
       bL[i]	=	block_x[i]-Cube.ShiftX;
       bR[i]	=	Cube.ShiftX-block_x[i];
       bU[i]	=	Cube.ShiftY-block_y[i];
       bD[i]	=	block_y[i]-Cube.ShiftY;
       
       // 左壁
       if(bL[i]<1 && -0.5<bL[i] && bU[i]<1 && bD[i]<1){
	 limit_right[i]	=	0;
       }
       else{
	 limit_right[i]	=	1;
	 t_limit_right		=	1;
       }		    
       
       // 右壁
       if(-0.5<bR[i] && bR[i]<1 && bU[i]<1 && bD[i]<1){
	 limit_left[i]	=	0;
       }
       else{
	 limit_left[i]	=	1;
	 t_limit_left		=	1;
       }
       
       // 上面
       if(-0.75<bL[i] && bL[i]<0.75 && -0.75<bR[i] && bR[i]<0.75 && bU[i]<1 && 0<bU[i]){
	 mini	=	block_y[i]+1;
	 fall	=	0;
	 fall_p	=	block_x[i];
	 if(i==I-1){
	   die_flag=2;
	 }
       }

       // 落下判定
       if(Cube.ShiftX<fall_p-0.9 || fall_p+0.9<Cube.ShiftX || bU[i]>1 && -1>bU[i]){
	 fall	=	1;
       }

       // 下面
       if(-0.75<bL[i] && bL[i]<0.75 && -0.75<bR[i] && bR[i]<0.75 && 0.75<bD[i] && 0<bD[i]){
	 if(block_y[i]<max){		
	   max	=	block_y[i]-1;
	 }
	 rise	=	0;
	 rise_p	=	block_x[i];
       }
       // 上移動判定
       if(Cube.ShiftX<rise_p-0.9 || rise_p+0.9<Cube.ShiftX){
	 rise	=	1;
       }
     }
     
     // 移動フラグ
     for(i=0;i<I;i++){	
       t_limit_right	*=	limit_right[i];				
     }
     for(i=0;i<I;i++){	
       t_limit_left	*=	limit_left[i];				
     }

     // 移動範囲の制御(上下)
     if(fall==1){
       mini=0;
     }
     if(rise==1){
       max=100;
     }

     // 自機の回転
     if(direction==0){
       Rotate-= 1;
     }
     else{
       Rotate+= 1;	
     }
     if( Cube.RotateZ > 360.0 ){	  
       Cube.RotateZ -= 360.0;
     }
     
     // 自機の異動(右)
     if(right==1 && t_limit_right == 1){
       Cube.ShiftX+=Cv;
       direction=0;
     }
     
     // 自機の異動(左)
     if(left==1 && t_limit_left == 1){
       Cube.ShiftX-=Cv;
       direction=1;
     }
          
     // ジャンプと落下の制御
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
     
     // 床の死亡判定
     if(Cube.ShiftX>5 && Cube.ShiftY==0){
       die_flag=0;  
     }
		  
     // 敵との当たり判定
     for(i=0;i<J;i++){
       R[i]	=	sqrt(pow(Cube.ShiftX+enemy_x[i],2.0)+pow(Cube.ShiftY-enemy_y[i],2.0));
       if(R[i]<0.5){
	 die_flag=0;
       }
       R2[i]	=	sqrt(pow(Cube.ShiftX-enemy_x2[i],2.0)
			     +pow(Cube.ShiftY-enemy_y2[i],2.0)
			     +pow(Cube.ShiftZ-enemy_z[i],2.0));
       if(R2[i]<0.5){
	 die_flag=0;
		    }
     }
     
     // 敵の移動
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

     // 時間変数の更新
     ntime	=	ntime-(ntime-0.1);
     ptime	+=	ntime;

     break;
     
     // 死亡時とクリア時
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



 /***********************************************************
|  関数：keyboard()
|  説明：キーボードが押された時のイベント処理
|  引数：unsigned char key  押されたキーの文字コード
|  引数：int x              キーが押されたときのマウスポインタのX座標
|  引数：int y              キーが押されたときのマウスポインタのY座標
|  戻値：なし
***********************************************************/
void keyboard(unsigned char key, int x, int y )
{
  switch( key ) {

    // スペースでジャンプ
  case ' ':
	  jcount++;
	  if(jcount<3){
		Vy	=	0.03;
	  }	 
	  jump=1; 
    break;

    // "s"で開始
  case 's':
    die_flag=1;
    break;
  }
  glutPostRedisplay();
  
  x = y = 0;
} 

/***********************************************************
|  関数：mouseButton()
|  説明：マウスのボタン操作時のイベント処理
|  引数：int button     操作したマウスボタンの番号
|  引数：int state      操作の種類 GLUT_DOWN（押す）かGLUT_UP（離す）
|  引数：int x          キーが押されたときのマウスポインタのX座標
|  引数：int y          キーが押されたときのマウスポインタのY座標
|  戻値：なし
***********************************************************/
void mouseButton(int button, int state, int x, int y )
{
  if (state == GLUT_DOWN)
  {
    switch(button)
    {

      // 左クリックで左移動
    case GLUT_LEFT_BUTTON:
	    PressButton = 0;
		left=1;
      break;

      // 真中クリックで始点変更
    case GLUT_MIDDLE_BUTTON:
      PressButton = button;
      break;
    
      // 右クリックで右移動
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


/***********************************************************
|  関数：mouseDrag()
|  説明：画面上でマウスがドラッグされた時のイベント処理
|  引数：int x          現在のマウスポインタのX座標
|  引数：int y          現在のマウスポインタのY座標
|  戻値：なし
***********************************************************/
void mouseDrag(int x, int y)
{
  int xMove = x - xBegin;
  int yMove = y - yBegin;
 
  switch (PressButton) {

    // カメラの移動
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


/***********************************************************
|  関数：myInit()
|  説明：ウインドウ表示と描画設定の初期化
|  引数：char *windowTitle      ウインドウのタイトルバーに表示する文字列
|  戻値：なし
***********************************************************/
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
  glutTimerFunc(15 , timer , 0);
  
}