/* --------------------------------------------------------------------
 * gls08.c
 * プリミティブ図形（点，線，三角パッチ）を描画する
 * -------------------------------------------------------------------- */

/* ヘッダファイル */
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define RAD (M_PI / 180.0)

/* グローバル変数 */
int   xBegin = 0;               /* マウスドラッグの始点X座標 */
int   yBegin = 0;               /* マウスドラッグの始点Y座標 */
int   PressButton = 0;          /* 現在押されているマウスボタン（1:左,2:中,3:右） */
float CameraAzimuth   = 90.0;   /* カメラの位置（方位角） */
float CameraElevation = 0.0;    /* カメラの位置（仰角） */
float CameraDistance  = 5.0;    /* カメラの位置（原点からの距離） */
float CameraX = 0.0;            /* カメラの位置（X座標） */
float CameraY = 0.0;            /* カメラの位置（Y座標） */
float CameraZ = 5.0;            /* カメラの位置（Z座標） */
float BoxY = 0.0;               /* 四角のY座標 */


/* 関数のプロトタイプ宣言 */
void display(void);
void timer(int timerID);
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
    /* 初期化 */
    glutInit(&argc, argv);  /* OpenGL の初期化 */
    myInit(argv[0]);        /* ウインドウ表示と描画設定の初期化 */

    /* イベント処理ループ */
    glutMainLoop(); 

    /* プログラム終了 */
    return( 0 );
}


/**********************************************************
|  関数：display()
|  説明：「１枚の」グラフィック描画イベント処理
|  引数：なし
|  戻値：なし
***********************************************************/
void display(void)
{
    float color[4] = {1.0};
    int i;

    /* 初期化 */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   /* 画面を消去 */
    glMatrixMode(GL_MODELVIEW);             /* 幾何（描画位置など設定する）モード */
    glLoadIdentity();                       /* 幾何を初期化する */

    /* 視点の設定 */
    gluLookAt(  CameraX, CameraY, CameraZ,  /* カメラの位置 */
                0.0, 0.0, 0.0,  /* 注視点の位置 */
                0.0, 1.0, 0.0); /* カメラ上方向のベクトル */
    
    /* 点の描画 */
    glBegin(GL_POINTS);                 /* 点の描画 開始 */
        /* 四角に4点を置く */
        color[0]=1.0; color[1]=1.0; color[2]=1.0;   /* 白色 */
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);  /* 描画色を設定 */
	glNormal3f(0, 0, 1.0);            /* 頂点の法線を設定 */
	glVertex3f(1.0, 1.0, 0);
	glVertex3f(1.0, 1.1, 0);
	glVertex3f(1.1, 1.1, 0);
	glVertex3f(1.1, 1.0, 0);
	
	/* 繰り返しで直線上に点を並べる */
	color[0]=0; color[1]=1.0; color[2]=0;       /* 緑色 */
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);  /* 描画色を設定 */
	glNormal3f(0, 0, 1.0);            /* 頂点の法線を設定 */
	for(i=0; i<20; i++)
	{
	    glVertex3f((float)i * 0.1 - 1.0, 0, 1.0);
	}
    glEnd();                            /* 点の描画 ここまで */

    /* 線の描画 */
    glBegin(GL_LINES);                  /* 線の描画 開始 */
        color[0]=1.0; color[1]=0; color[2]=0;       /* 赤色 */
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);  /* 描画色を設定 */
	glNormal3f(0, 0, 1.0);            /* 頂点の法線を設定 */
	
	glVertex3f(0.5, 0.7, 0);        /* 1本目の線の始点 */
	glVertex3f(0.7, 0.5, 0);        /* 1本目の線の終点 */

	glVertex3f(0.5, 0.5, 0);        /* 2本目の線の始点 */
	glVertex3f(0.7, 0.7, 0);        /* 2本目の線の終点 */
    glEnd();                            /* 線の描画 ここまで */

    /* 三角形の描画 */
    glBegin(GL_TRIANGLE_STRIP);         /* 三角形の描画 開始 */
        color[0]=0; color[1]=0; color[2]=1.0;       /* 青色 */
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);  /* 描画色を設定 */
	glNormal3f(0, 0, 1.0);            /* 頂点の法線を設定 */
	
	glVertex3f(1.0, -1.0, 1.0);     /* 頂点1 */
	glVertex3f(1.0, -1.2, 1.0);     /* 頂点2 */
	glVertex3f(1.2, -1.2, 1.0);     /* 頂点3 */
    glEnd();                            /* 三角形の描画 ここまで */

    /* 四角形の描画（三角形を２個つなげる） */
    glBegin(GL_TRIANGLE_STRIP);         /* 三角形の描画 開始 */
        color[0]=1.0; color[1]=1.0; color[2]=0;     /* 黄色 */
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);  /* 描画色を設定 */
	glNormal3f(0, 0, 1.0);            /* 頂点の法線を設定 */
	
	glVertex3f(-1.0, BoxY,       1.5);     /* 頂点1 */
	glVertex3f(-1.0, BoxY + 0.2, 1.5);     /* 頂点2 */
	glVertex3f(-1.2, BoxY,       1.5);     /* 頂点3 */
	glVertex3f(-1.2, BoxY + 0.2, 1.5);     /* 頂点4 */
    glEnd();                            /* 三角形の描画 ここまで */
	
    /* 従来の立方体も描画 */
    glPushMatrix ();                /* 描画位置を保存 */
    color[0]=1.0; color[1]=0; color[2]=1.0;     /* 紫色 */
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);  /* 描画色を設定 */
    glutSolidCube (0.6);
    glPopMatrix ();                 /* 描画位置を戻す */

    /* 上記で描画されたCGをモニターに出力 */
    glutSwapBuffers();
}


/***********************************************************
|  関数：timer(int timerID)
|  説明：タイマー（設定時間経過）イベント処理
|  引数：int timerID    イベントが発生したタイマーの識別ID
|  戻値：なし
***********************************************************/
void timer(int timerID)
{
    /* 次のタイマーを15ミリ秒後に設定 */
    glutTimerFunc(15, timer, 0);

    /* 四角の表示Y座標を0.01ずつ増加させる */
    BoxY += 0.01;
    if( BoxY > 2.0 ) BoxY = -2.0;

    /* 描画要求（直後に display() 関数が呼ばれる） */
    glutPostRedisplay();
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
    /* キーボード処理 */
    switch( key )
    {
    case 'q':
        exit( 0 );      /* プログラム終了 */
        break;
    }

    /* 描画要求（直後に display() 関数が呼ばれる） */
    glutPostRedisplay();

    /* コンパイル時の警告対策（定義された変数を使わないと警告になるので） */
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
    /* マウスが押された時 */
    if (state == GLUT_DOWN)
    {
        switch(button)
        {
        case GLUT_LEFT_BUTTON:  /* マウス左ボタンを押した時の処理 */
            PressButton = button;
            break;

        case GLUT_MIDDLE_BUTTON:/* マウス中ボタンを押した時の処理 */
            break;

        case GLUT_RIGHT_BUTTON: /* マウス右ボタンを押した時の処理 */
            PressButton = button;
            break;
        }

        /* マウスボタンを押した瞬間の始点座標を記録する */
        xBegin = x;
        yBegin = y;
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
    /* マウスボタンが押されてからの移動量を計算する */
    int xMove = x - xBegin;
    int yMove = y - yBegin;

    switch (PressButton)
    {
    /* マウス左ボタンドラッグ時の処理 */
    /* 視点を方位角，仰角に対して回転させる */
    case GLUT_LEFT_BUTTON:
        CameraAzimuth   += (float)xMove / 2.0;
        CameraElevation += (float)yMove / 2.0;
        if (CameraElevation >  90.0) CameraElevation =  90.0;
        if (CameraElevation < -90.0) CameraElevation = -90.0;
        break;

    /* マウス右ボタンドラッグ時の処理 */
    /* 視点を奥行き方向に前後に移動させる */
    case GLUT_RIGHT_BUTTON:
        CameraDistance += (float)yMove / 40.0;
        break;
    }
    CameraX = CameraDistance * cos(CameraAzimuth * RAD) * cos(CameraElevation * RAD);
    CameraY = CameraDistance * sin(CameraElevation * RAD);
    CameraZ = CameraDistance * sin(CameraAzimuth * RAD) * cos(CameraElevation * RAD);
    printf("Camera AZ:%.1f, EL:%.1f, dist:%.1f, x,y,z= %.1f, %.1f, %.1f\n", 
        CameraAzimuth, CameraElevation, CameraDistance, CameraX, CameraY, CameraZ);

    /* 現在のマウスポインタの座標を次の始点用に記録する */
    xBegin = x;
    yBegin = y;

    /* 描画要求（直後に display() 関数が呼ばれる） */
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
    /* ウインドウのサイズ */
    int winWidth  = 400;
    int winHeight = 400;
    /* ウインドウの縦横の比を計算 */
    float aspect = (float)winWidth / (float)winHeight;

    /* OpenGLウインドウ作成までの初期化 */
    glutInitWindowPosition(0, 0);                   /* ウインドウ表示位置 */
    glutInitWindowSize(winWidth, winHeight);        /* ウインドウサイズ */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);   /* 描画モード */
    glutCreateWindow(windowTitle);                  /* ウインドウの表示 */
    glClearColor (0.0, 0.0, 0.0, 1.0);              /* 画面消去色の設定 */

    /* イベント発生時に呼び出す関数の登録 */
    glutKeyboardFunc(keyboard);     /* キーボードを押した時 */
    glutMouseFunc   (mouseButton);  /* マウスボタンを押した時*/
    glutMotionFunc  (mouseDrag);    /* マウスドラッグした時 */
    glutDisplayFunc (display);      /* 画面表示 */
    glutTimerFunc(15, timer, 0);    /* タイマーを15ミリ秒後に設定 */

    /* CG描画設定 */
    glMatrixMode(GL_PROJECTION);    /* 透視投影(遠近投影法)設定モードに切り替え */
    glLoadIdentity();               /* 透視投影行列を初期化 */
    gluPerspective(45.0, aspect, 1.0, 20.0);    /* 透視投影行列の設定 */
      /* 視野角45度, 縦横比 aspect，描画前面までの奥行 1.0，描画背面までの奥行 20.0 */
    glEnable(GL_DEPTH_TEST);        /* 隠面消去を有効にする */
    glEnable(GL_LIGHT0);            /* 0番の照明を使う ##########  ##########  */
    glEnable(GL_NORMALIZE);         /* 照明計算の法線を正規化 ##########  ########## */
    glEnable(GL_LIGHTING);          /* 照明を有効にする ##########  ##########  */
}