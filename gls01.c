/* --------------------------------------------------------------------
 * gls01.c
 * イベントの発生を理解するプログラム
 * -------------------------------------------------------------------- */

/* ヘッダファイル */
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/**********************************************************
|  関数：display()
|  説明：1枚のグラフィック描画イベント処理
|  引数：なし
|  戻値：なし
***********************************************************/
void display(void)
{
    printf("Display Event\n");
    
    glClear (GL_COLOR_BUFFER_BIT);          /* 画面を消去 */
    glutSwapBuffers();                      /* 描画されたCGを画面に表示 */
}


/***********************************************************
|  関数：timer(int timerID)
|  説明：タイマー（設定時間経過）イベント処理
|  引数：int timerID    イベントが発生したタイマーの識別ID
|  戻値：なし
***********************************************************/
void timer(int timerID)
{
    printf("Timer Event\n");
    glutTimerFunc(1000, timer, 0);
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
    printf("Keyboard Event  key:'%c', x:%3d, y:%3d\n", key, x, y);

    /* キーボード処理 */
    switch( key )
    {
        case 'q':
            exit( 0 );              /* プログラム終了 */
            break;
        case 'd':
            glutPostRedisplay();    /* 描画要求 */
            break;
    }
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
    printf("Mouse Button Event  button:%d, state:%4s, x:%3d, y:%3d\n", 
        button, (state==GLUT_DOWN ? "down": "up"), x, y);
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
    printf("Mouse Drag Event  x:%3d, y:%3d\n", x, y);
}


/***********************************************************
|  関数：myInit()
|  説明：ウインドウ表示と描画設定の初期化
|  引数：char *windowTitle      ウインドウのタイトルバーに表示する文字列
|  戻値：なし
***********************************************************/
void myInit (char *windowTitle)
{
    /* OpenGLウインドウ作成までの初期化 */
    glutInitWindowPosition(0, 0);                   /* ウインドウ表示位置 */
    glutInitWindowSize(400, 400);                   /* ウインドウサイズ */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);   /* 描画モード */
    glutCreateWindow(windowTitle);                  /* ウインドウの表示 */
    glClearColor (0.0, 0.0, 0.0, 1.0);              /* 画面消去色の設定 */

    /* イベント発生時に呼び出す関数の登録 */
    glutKeyboardFunc(keyboard);         /* キーボードを押した時 */
    glutMouseFunc   (mouseButton);      /* マウスボタンを押した時*/
    glutMotionFunc  (mouseDrag);        /* マウスドラッグした時 */
    glutTimerFunc   (1000, timer, 0);   /* 1000(ms)経過時 */
    glutDisplayFunc (display);          /* 画面表示 */
}


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