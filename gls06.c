/* --------------------------------------------------------------------
 * gls06.c
 * 様々な形状を表示する
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
int   ObjectType = 1;           /* 物体の種類 */
int   ObjectWired = 1;          /* 物体の表示モード（Solid=0, Wire=1) */
float ObjectRotate = 0.0;       /* 物体の回転角 */


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
    /* 初期化 */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   /* 画面を消去 */
    glMatrixMode(GL_MODELVIEW);             /* 幾何（描画位置など設定する）モード */
    glLoadIdentity();                       /* 幾何を初期化する */

    /* 視点の設定 */
    gluLookAt(  CameraX, CameraY, CameraZ,  /* カメラの位置 */
                0.0, 0.0, 0.0,  /* 注視点の位置 */
                0.0, 1.0, 0.0); /* カメラ上方向のベクトル */
    
    /* 立方体の描画 1 */
    glPushMatrix ();                /* 描画位置を保存 */
    glColor3f(1.0, 1.0, 1.0);       /* 描画色を白にする */
    glRotatef(ObjectRotate, 0.0, 1.0, 0.0);   /* Y軸中心にObjectRotate(度)回転 */
    switch (ObjectType)
    {
    case 1: /* 立方体（引数：一辺の長さ） */
        if (ObjectWired == 0) glutSolidCube(1.0);
        else                  glutWireCube (1.0);
        break;
    case 2: /* 球（引数：半径, 緯度方向分割数，経度方向分割数） */
        if (ObjectWired == 0) glutSolidSphere(0.5, 10, 10);
        else                  glutWireSphere (0.5, 10, 10);
        break;
    case 3: /* 円錐（引数：底面の半径，高さ, 緯度方向分割数，経度方向分割数） */
        if (ObjectWired == 0) glutSolidCone(0.5, 1.0, 10, 10);
        else                  glutWireCone (0.5, 1.0, 10, 10);
        break;
    case 4: /* ドーナツ（引数：内径，外径, 断面の分割数，管の分割数） */
        if (ObjectWired == 0) glutSolidTorus(0.2, 0.5, 10, 10);
        else                  glutWireTorus (0.2, 0.5, 10, 10);
        break;
    case 5: /* 正四面体（引数：なし） */
        if (ObjectWired == 0) glutSolidTetrahedron();
        else                  glutWireTetrahedron ();
        break;
    case 6: /* ティーポット */
        if (ObjectWired == 0) glutSolidTeapot(1.0);
        else                  glutWireTeapot (1.0);
        break;
    }
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

    /* オブジェクトの回転角度を1.0度ずつ増加させる */
    ObjectRotate += 1.0;
    if( ObjectRotate > 360.0 ) ObjectRotate -= 360.0;

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
    case 'w': /* 表示モード切替 */
        ObjectWired = 1 - ObjectWired;  /* 1→0, 0→1 となる */
        break;
    case '1':
        ObjectType = 1;
        break;
    case '2':
        ObjectType = 2;
        break;
    case '3':
        ObjectType = 3;
        break;
    case '4':
        ObjectType = 4;
        break;
    case '5':
        ObjectType = 5;
        break;
    case '6':
        ObjectType = 6;
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
}