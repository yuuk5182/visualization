///////////////////////////////////////////////////////////////////////////////
///                                                                         ///
///     学籍番号:2072088　   氏名：山本勇樹                                 ///
///                                                                         ///
///     ビジュアライゼーション 最終課題                                     ///
///                                                                         ///
///                                                                         ///
///     参考プログラム                                               ///
///         「コンピュータグラフィックス OpenGL action3.c　（津村徳道）」   ///
///         https://www.mi.tj.chiba-u.jp/~tsumura/OpenGL/action3.c          ///
///                                                                         ///                                                                     ///
///////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

// ブロック数
//#defineは第1引数を今後第2引数として扱ってくれる
//#define	I	43  //空中ブロック配列用変数
//#define O   192 //床ブロック用配列変数
#define D   6   //土管用配列変数
//#define K   88  //階段ブロック用配列変数

#define I 323

// 敵数
#define	J	7
#define RAD (M_PI / 180.0)

//mySolidSylinder用
#define PI2 2.0*3.1415926534

// 自機の位置
//typedef structは構造体にGeometryと命名することで今後の変数宣言時にstructキーワードの記述を省略できる．
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
double		mini=-6,max=100;
double		Vy;

// 時間変数の宣言と初期化
double		ntime=0,ptime=0;
double		die_ntime=0,die_ptime=0;

// ブロックと敵の宣言と初期化
double		block_x[I]={
    /*ここから空中ブロック*/6,10,11,12,12,13,14,65,66,67,68,69,70,71,72,73,74,75,80,81,82,83,83,89,90,95,98,98,101,107,110,111,112,117,118,118,119,119,120,158,159,160,161,
    /*ここから床ブロック*/-10, -9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,61,62,63,64,65,66,67,68,69,70,71,72,73,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,
    /*ここから階段ブロック*/123,124,125,126,124,125,126,125,126,126,129,130,131,132,129,130,131,129,130,129,137,138,139,140,141,138,139,140,141,139,140,141,140,141,144,145,146,147,144,145,146,144,145,144,171,172,173,174,175,176,177,178,179,172,173,174,175,176,177,178,179,173,174,175,176,177,178,179,174,175,176,177,178,179,175,176,177,178,179,176,177,178,179,177,178,179,178,179
};
double		block_y[I]={
    /*ここから空中ブロック*/3,3,3,3,7,3,3,3,3,3,7,7,7,7,7,7,7,7,7,7,7,7,3,3,3,3,3,7,3,3,7,7,7,7,7,3,7,3,7,3,3,3,3,
    /*ここから床ブロック*/-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    /*ここから階段ブロック*/0,0,0,0,1,1,1,2,2,3,0,0,0,0,1,1,1,2,2,3,0,0,0,0,0,1,1,1,1,2,2,2,3,3,0,0,0,0,1,1,1,2,2,3,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,6,6,6,7,7
};
double      dblock_x[D] = { 18.5,28.5,36.5,47.5,153.5,169.5 };
double      dblock_height[D] = { 2,3,4,4,2,2 };//土管は高さを格納．描画の際はこの数値を/2-0.5してy座標とする
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
float CameraAzimuth   = 90.0;   /* カメラの位置（方位角） */
float CameraElevation = 0.0;    /* カメラの位置（仰角） */
float CameraDistance  = 5.0;    /* カメラの位置（原点からの距離） */
float CameraX = 0.0;            /* カメラの位置（X座標） */
float CameraY = 0.0;            /* カメラの位置（Y座標） */
float CameraZ = 5.0;            /* カメラの位置（Z座標） */


//wire円柱関数
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


//塗りつぶし円柱関数
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


// 描画関数(魔法の呪文)
void drawString3D(const char *str, float charSize, float lineWidth)
{
  glPushMatrix();
  glPushAttrib(GL_LINE_BIT);    //カレントのライティングプロパティをセーブ
  glScaled(0.001 * charSize, 0.001 * charSize, 0.01);
  glLineWidth(lineWidth);
  while(*str){
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *str);
    ++str;
  }
  glPopAttrib();    //セーブされたプロパティをリストア
  glPopMatrix();
}


void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //gl_depth_buffer_bitで隠面消去
  glPushMatrix ();
  
  /* 視点の設定 */
  gluLookAt(  Cube.ShiftX+CameraX, Cube.ShiftY+CameraY+3, Cube.ShiftZ+CameraZ+5,  /* カメラの位置 */
	      Cube.ShiftX, Cube.ShiftY+3, Cube.ShiftZ,  /* 注視点の位置 */
	      0.0, 1.0, 0.0); /* カメラ上方向のベクトル */ 
  
  glEnable(GL_DEPTH_TEST); 

  //背景の水色の描画
  glPushMatrix();
  glColor3f(0.39, 0.58, 0.93);
  glTranslatef(Cube.ShiftX, Cube.ShiftY, Cube.ShiftZ+5);
  glutSolidSphere(15, 10, 10);  //solidCubeだと角の部分が黒く見える．sphereも若干見えるけど少しまし？
  glPopMatrix();
 
  // 初期状態(文字の描画)
  if(die_flag==99){
    glPushMatrix ();
    glColor3f( 1.0, 0.0, 0.0 );  
    glTranslatef(-7, 4.0, 0); 
    drawString3D("Press ' s ' to start", 10.0, 3.0);
    glColor3f(0, 0, 0);
    glScaled(0.5, 0.5, 0);
    glTranslatef(0, 7, 0);
    drawString3D("Click the center mouse button and drag", 10.0, 1.0);
    glTranslatef(3, -2, 0);
    drawString3D("to change the viewpoint", 10.0, 1.0);
    glTranslatef(0,-10,0);
    drawString3D("Press 'Space' to jump", 10.0, 1.0);
    glTranslatef(0, -10, 0);
    drawString3D("Mouse click to move", 10.0, 1.0);
    glScaled(2, 2, 0);
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

  glutWireSphere(0.5, 10, 10);
  glPopMatrix ();   

  
  // 敵の描画
  for(i=0;i<J;i++){
    glPushMatrix ();   //横から来る敵の描画
    glColor3f( 0.0,0.0,1.0 ); 
    glRotatef(-90,0.0,1.0,0.0);
    glTranslatef(0.0,enemy_y[i],enemy_x[i]);
    glRotatef(ptime*100,0.0,0.0,1.0);
    glutWireCone(0.25,0.5,10,2);
    glPopMatrix ();
    
    glPushMatrix ();    //奥からくる敵の描画  
    glColor3f( 0.0,1.0,0.0 ); 
    glTranslatef(enemy_x2[i],enemy_y2[i],enemy_z[i]);
	glRotatef(ptime*100,0.0,0.0,1.0);
	glutWireCone(0.25,0.5,10,2);
	glPopMatrix ();
  }
  


      // 土管の描画
      for (i = 0; i < D; i++) {
          glPushMatrix();
          glTranslatef(dblock_x[i], dblock_height[i]/2-0.5, 0);
          glColor3f(0.13, 0.55, 0.13);
          mySolidCylinder(1, dblock_height[i],24);
          glColor3f(0, 0, 0);
          myWireCylinder(1, dblock_height[i], 24);
          glPopMatrix();
      }

      //土管の縁の描画
      for (i = 0; i < D; i++) {
          glPushMatrix();
          glTranslatef(dblock_x[i], dblock_height[i] / 2 + 1 , 0);
          glColor3f(0.13, 0.55, 0.13);
          mySolidCylinder(1.2, dblock_height[i]/3, 24);
          glColor3f(0, 0, 0);
          myWireCylinder(1.2, dblock_height[i] / 3, 24);
          glPopMatrix();
      }



  

  // ブロックの描画
  for(i=0;i<I;i++){
      if (i <= 42){//空中ブロック部分
          glPushMatrix();
          glTranslatef(block_x[i], block_y[i], block_z[i]);
          glColor3f(0.50, 0.25, 0.25);
          glutSolidCube(1.0);
          glColor3f(0, 0, 0);
          glutWireCube(1.0);
          glLineWidth(5.0);   //ブロックの線の描画
          glScaled(1.0, 0.33, 1.0);
          glutWireCube(1.0);  //横線の描画
          glScaled(0.5, 1.0, 1.0);
          glutWireCube(1.0);  //中央の四角の描画
          glLineWidth(1.0);   //線の太さをもとに戻す
          glPopMatrix();
      }
      else if (i <= 234) {//床ブロック部分
          glPushMatrix();
          glTranslatef(block_x[i], -1, 0);
          glColor3f(0.96, 0.64, 0.38);
          glutSolidCube(1.0);
          glLineWidth(5.0);   //ブロックの線の描画
          glColor3f(0, 0, 0);
          glutWireCube(1.0);
          glScaled(0.02, 1.0, 1.0);
          glutWireCube(1.0);  //縦線の描画
          glScaled(50, 0, 1.0);
          glutWireCube(1.0);
          glLineWidth(1.0);   //線の太さをもとに戻す
          glPopMatrix();
      }
      else if (i <= 323) {//階段ブロック部分
          glPushMatrix();
          glTranslatef(block_x[i], block_y[i], 0);
          glColor3f(1, 0.50, 0.31);
          glutSolidCube(1.0);
          glLineWidth(5.0);   //ブロックの線の描画
          glColor3f(0, 0, 0);
          glutWireCube(1.0);
          glLineWidth(1.0);   //線の太さをもとに戻す
          glPopMatrix();
      }
    
  }

  //ゴール旗の描画
  glPushMatrix();
  glTranslatef(188, 4, 0);
  glColor3f(255, 255, 0);//ポール部分
  mySolidCylinder(0.1, 10, 24);
  glColor3f(255, 255, 255);//旗の三角部分
  glTranslatef(0.5, 4, 0);
  glRotatef(90, 1, 0, 0);
  mySolidCylinder(1, 0.1, 3);
  glRotatef(-90, 1, 0, 0);
  glPopMatrix();

  glDisable(GL_DEPTH_TEST);
  glPopMatrix ();                   
  glutSwapBuffers();
}


void timer(int value)
 {
   
   switch	(die_flag)	{
     
     // 通常時
   case	1:
     
     // 空中ブロックとの当たり判定
     for(i=0;i<I;i++){
   
        // 左右上下の判定用
        bL[i] = block_x[i] - Cube.ShiftX;
        bR[i] = Cube.ShiftX - block_x[i];
        bU[i] = Cube.ShiftY - block_y[i];
        bD[i] = block_y[i] - Cube.ShiftY;
         
       
       
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
     rise = 0;
     rise_p = block_x[i];
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
       mini=-6;
     }
     if(rise==1){
       max=100;
     }

     // 自機の回転
     if (direction == 0) {  //右に移動しているときは右回転
         Rotate -= 1;
     }
     else {
         Rotate += 1;
     }
     if (Cube.RotateZ > 360.0) {
         Cube.RotateZ -= 360.0;
     }
     
     // 自機の移動(右)
     if(right==1 && t_limit_right == 1){
       Cube.ShiftX+=Cv;
       direction=0;
     }
     
     // 自機の移動(左)
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
     if(Cube.ShiftX>-10 && Cube.ShiftY==-6){
       die_flag=0;  
     }

     // ゴール判定
     if (Cube.ShiftX > 187.5 && Cube.ShiftX < 188.5 && Cube.ShiftY > -1 && Cube.ShiftY < 9) {
         die_flag = 2;
     }
		  
     // 敵との当たり判定
     for(i=0;i<J;i++){
       R[i]	=	sqrt(pow(Cube.ShiftX+enemy_x[i],2.0)+pow(Cube.ShiftY-enemy_y[i],2.0));  //横からの敵との当たり判定
       if(R[i]<0.5){
	 die_flag=0;
       }
       R2[i]	=	sqrt(pow(Cube.ShiftX-enemy_x2[i],2.0)   //奥からの敵との当たり判定
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




void keyboard(unsigned char key, int x, int y )
{
  switch( key ) {

    // スペースでジャンプ
  case ' ':
	  jcount++;
	  if(jcount<2){
		Vy	=	0.046;
	  }	 
	  jump=1; 
    break;

    // "s"で開始
  case 's':
    die_flag=1;
    break;

    //開発時用ショートカット
  //case 't':
  //    Cube.ShiftX = 160;
  //    Cube.ShiftY = 0;
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

      // 左クリックで左移動
    case GLUT_LEFT_BUTTON:
	    PressButton = 0;
		left=1;
      break;

      // 真中クリックで視点変更
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
  glutTimerFunc(15 , timer , 0);    //指定の時間経過でコールバック関数を呼び出し

  
}



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
    
    //空中ブロック数確認のため
    //int length = sizeof(block_x) / sizeof(block_x[0]);
    //printf("空中ブロックの数: %d\n",length);

    //int flength = sizeof(fblock_x) / sizeof(fblock_x[0]);
    //printf("床ブロックの数: %d\n", flength);

    // 敵位置(青)の初期化
    for (i = 0; i < J; i++) {
        enemy_x[i] = 30 + rand() % 30;
        enemy_y[i] = rand() % 10;
    }

    // 敵位置(緑)の初期化
    for (i = 0; i < J; i++) {
        enemy_z[i] = -5 + rand() % 10;
        enemy_x2[i] = 10 + rand() % 10;
        enemy_y2[i] = rand() % 10;
    }

    glutMainLoop();

    return(0);
}