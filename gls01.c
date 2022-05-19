/* --------------------------------------------------------------------
 * gls01.c
 * �C�x���g�̔����𗝉�����v���O����
 * -------------------------------------------------------------------- */

/* �w�b�_�t�@�C�� */
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/**********************************************************
|  �֐��Fdisplay()
|  �����F1���̃O���t�B�b�N�`��C�x���g����
|  �����F�Ȃ�
|  �ߒl�F�Ȃ�
***********************************************************/
void display(void)
{
    printf("Display Event\n");
    
    glClear (GL_COLOR_BUFFER_BIT);          /* ��ʂ����� */
    glutSwapBuffers();                      /* �`�悳�ꂽCG����ʂɕ\�� */
}


/***********************************************************
|  �֐��Ftimer(int timerID)
|  �����F�^�C�}�[�i�ݒ莞�Ԍo�߁j�C�x���g����
|  �����Fint timerID    �C�x���g�����������^�C�}�[�̎���ID
|  �ߒl�F�Ȃ�
***********************************************************/
void timer(int timerID)
{
    printf("Timer Event\n");
    glutTimerFunc(1000, timer, 0);
}


/***********************************************************
|  �֐��Fkeyboard()
|  �����F�L�[�{�[�h�������ꂽ���̃C�x���g����
|  �����Funsigned char key  �����ꂽ�L�[�̕����R�[�h
|  �����Fint x              �L�[�������ꂽ�Ƃ��̃}�E�X�|�C���^��X���W
|  �����Fint y              �L�[�������ꂽ�Ƃ��̃}�E�X�|�C���^��Y���W
|  �ߒl�F�Ȃ�
***********************************************************/
void keyboard(unsigned char key, int x, int y )
{
    printf("Keyboard Event  key:'%c', x:%3d, y:%3d\n", key, x, y);

    /* �L�[�{�[�h���� */
    switch( key )
    {
        case 'q':
            exit( 0 );              /* �v���O�����I�� */
            break;
        case 'd':
            glutPostRedisplay();    /* �`��v�� */
            break;
    }
} 


/***********************************************************
|  �֐��FmouseButton()
|  �����F�}�E�X�̃{�^�����쎞�̃C�x���g����
|  �����Fint button     ���삵���}�E�X�{�^���̔ԍ�
|  �����Fint state      ����̎�� GLUT_DOWN�i�����j��GLUT_UP�i�����j
|  �����Fint x          �L�[�������ꂽ�Ƃ��̃}�E�X�|�C���^��X���W
|  �����Fint y          �L�[�������ꂽ�Ƃ��̃}�E�X�|�C���^��Y���W
|  �ߒl�F�Ȃ�
***********************************************************/
void mouseButton(int button, int state, int x, int y )
{
    printf("Mouse Button Event  button:%d, state:%4s, x:%3d, y:%3d\n", 
        button, (state==GLUT_DOWN ? "down": "up"), x, y);
}


/***********************************************************
|  �֐��FmouseDrag()
|  �����F��ʏ�Ń}�E�X���h���b�O���ꂽ���̃C�x���g����
|  �����Fint x          ���݂̃}�E�X�|�C���^��X���W
|  �����Fint y          ���݂̃}�E�X�|�C���^��Y���W
|  �ߒl�F�Ȃ�
***********************************************************/
void mouseDrag(int x, int y)
{
    printf("Mouse Drag Event  x:%3d, y:%3d\n", x, y);
}


/***********************************************************
|  �֐��FmyInit()
|  �����F�E�C���h�E�\���ƕ`��ݒ�̏�����
|  �����Fchar *windowTitle      �E�C���h�E�̃^�C�g���o�[�ɕ\�����镶����
|  �ߒl�F�Ȃ�
***********************************************************/
void myInit (char *windowTitle)
{
    /* OpenGL�E�C���h�E�쐬�܂ł̏����� */
    glutInitWindowPosition(0, 0);                   /* �E�C���h�E�\���ʒu */
    glutInitWindowSize(400, 400);                   /* �E�C���h�E�T�C�Y */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);   /* �`�惂�[�h */
    glutCreateWindow(windowTitle);                  /* �E�C���h�E�̕\�� */
    glClearColor (0.0, 0.0, 0.0, 1.0);              /* ��ʏ����F�̐ݒ� */

    /* �C�x���g�������ɌĂяo���֐��̓o�^ */
    glutKeyboardFunc(keyboard);         /* �L�[�{�[�h���������� */
    glutMouseFunc   (mouseButton);      /* �}�E�X�{�^������������*/
    glutMotionFunc  (mouseDrag);        /* �}�E�X�h���b�O������ */
    glutTimerFunc   (1000, timer, 0);   /* 1000(ms)�o�ߎ� */
    glutDisplayFunc (display);          /* ��ʕ\�� */
}


/***********************************************************
|  �֐��Fmain()
|  �����F���C���֐�
|  �����Fint argc       ���s�������̐�
|  �����Fchar** argv    ���s�������̓��e�i������z��j
|  �ߒl�Fint            0:����I��
***********************************************************/
int main(int argc, char** argv)
{
    /* ������ */
    glutInit(&argc, argv);  /* OpenGL �̏����� */
    myInit(argv[0]);        /* �E�C���h�E�\���ƕ`��ݒ�̏����� */

    /* �C�x���g�������[�v */
    glutMainLoop(); 

    /* �v���O�����I�� */
    return( 0 );
}