/* --------------------------------------------------------------------
 * gls06.c
 * �l�X�Ȍ`���\������
 * -------------------------------------------------------------------- */

/* �w�b�_�t�@�C�� */
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define RAD (M_PI / 180.0)

/* �O���[�o���ϐ� */
int   xBegin = 0;               /* �}�E�X�h���b�O�̎n�_X���W */
int   yBegin = 0;               /* �}�E�X�h���b�O�̎n�_Y���W */
int   PressButton = 0;          /* ���݉�����Ă���}�E�X�{�^���i1:��,2:��,3:�E�j */
float CameraAzimuth   = 90.0;   /* �J�����̈ʒu�i���ʊp�j */
float CameraElevation = 0.0;    /* �J�����̈ʒu�i�p�j */
float CameraDistance  = 5.0;    /* �J�����̈ʒu�i���_����̋����j */
float CameraX = 0.0;            /* �J�����̈ʒu�iX���W�j */
float CameraY = 0.0;            /* �J�����̈ʒu�iY���W�j */
float CameraZ = 5.0;            /* �J�����̈ʒu�iZ���W�j */
int   ObjectType = 1;           /* ���̂̎�� */
int   ObjectWired = 1;          /* ���̂̕\�����[�h�iSolid=0, Wire=1) */
float ObjectRotate = 0.0;       /* ���̂̉�]�p */


/* �֐��̃v���g�^�C�v�錾 */
void display(void);
void timer(int timerID);
void keyboard(unsigned char key, int x, int y );
void mouseButton(int button, int state, int x, int y );
void mouseDrag(int x, int y);
void myInit (char *windowTitle);


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


/**********************************************************
|  �֐��Fdisplay()
|  �����F�u�P���́v�O���t�B�b�N�`��C�x���g����
|  �����F�Ȃ�
|  �ߒl�F�Ȃ�
***********************************************************/
void display(void)
{
    /* ������ */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   /* ��ʂ����� */
    glMatrixMode(GL_MODELVIEW);             /* �􉽁i�`��ʒu�Ȃǐݒ肷��j���[�h */
    glLoadIdentity();                       /* �􉽂����������� */

    /* ���_�̐ݒ� */
    gluLookAt(  CameraX, CameraY, CameraZ,  /* �J�����̈ʒu */
                0.0, 0.0, 0.0,  /* �����_�̈ʒu */
                0.0, 1.0, 0.0); /* �J����������̃x�N�g�� */
    
    /* �����̂̕`�� 1 */
    glPushMatrix ();                /* �`��ʒu��ۑ� */
    glColor3f(1.0, 1.0, 1.0);       /* �`��F�𔒂ɂ��� */
    glRotatef(ObjectRotate, 0.0, 1.0, 0.0);   /* Y�����S��ObjectRotate(�x)��] */
    switch (ObjectType)
    {
    case 1: /* �����́i�����F��ӂ̒����j */
        if (ObjectWired == 0) glutSolidCube(1.0);
        else                  glutWireCube (1.0);
        break;
    case 2: /* ���i�����F���a, �ܓx�����������C�o�x�����������j */
        if (ObjectWired == 0) glutSolidSphere(0.5, 10, 10);
        else                  glutWireSphere (0.5, 10, 10);
        break;
    case 3: /* �~���i�����F��ʂ̔��a�C����, �ܓx�����������C�o�x�����������j */
        if (ObjectWired == 0) glutSolidCone(0.5, 1.0, 10, 10);
        else                  glutWireCone (0.5, 1.0, 10, 10);
        break;
    case 4: /* �h�[�i�c�i�����F���a�C�O�a, �f�ʂ̕������C�ǂ̕������j */
        if (ObjectWired == 0) glutSolidTorus(0.2, 0.5, 10, 10);
        else                  glutWireTorus (0.2, 0.5, 10, 10);
        break;
    case 5: /* ���l�ʑ́i�����F�Ȃ��j */
        if (ObjectWired == 0) glutSolidTetrahedron();
        else                  glutWireTetrahedron ();
        break;
    case 6: /* �e�B�[�|�b�g */
        if (ObjectWired == 0) glutSolidTeapot(1.0);
        else                  glutWireTeapot (1.0);
        break;
    }
    glPopMatrix ();                 /* �`��ʒu��߂� */

    /* ��L�ŕ`�悳�ꂽCG�����j�^�[�ɏo�� */
    glutSwapBuffers();
}


/***********************************************************
|  �֐��Ftimer(int timerID)
|  �����F�^�C�}�[�i�ݒ莞�Ԍo�߁j�C�x���g����
|  �����Fint timerID    �C�x���g�����������^�C�}�[�̎���ID
|  �ߒl�F�Ȃ�
***********************************************************/
void timer(int timerID)
{
    /* ���̃^�C�}�[��15�~���b��ɐݒ� */
    glutTimerFunc(15, timer, 0);

    /* �I�u�W�F�N�g�̉�]�p�x��1.0�x������������ */
    ObjectRotate += 1.0;
    if( ObjectRotate > 360.0 ) ObjectRotate -= 360.0;

    /* �`��v���i����� display() �֐����Ă΂��j */
    glutPostRedisplay();
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
    /* �L�[�{�[�h���� */
    switch( key )
    {
    case 'q':
        exit( 0 );      /* �v���O�����I�� */
        break;
    case 'w': /* �\�����[�h�ؑ� */
        ObjectWired = 1 - ObjectWired;  /* 1��0, 0��1 �ƂȂ� */
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

    /* �`��v���i����� display() �֐����Ă΂��j */
    glutPostRedisplay();

    /* �R���p�C�����̌x���΍�i��`���ꂽ�ϐ����g��Ȃ��ƌx���ɂȂ�̂Łj */
    x = y = 0;
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
    /* �}�E�X�������ꂽ�� */
    if (state == GLUT_DOWN)
    {
        switch(button)
        {
        case GLUT_LEFT_BUTTON:  /* �}�E�X���{�^�������������̏��� */
            PressButton = button;
            break;

        case GLUT_MIDDLE_BUTTON:/* �}�E�X���{�^�������������̏��� */
            break;

        case GLUT_RIGHT_BUTTON: /* �}�E�X�E�{�^�������������̏��� */
            PressButton = button;
            break;
        }

        /* �}�E�X�{�^�����������u�Ԃ̎n�_���W���L�^���� */
        xBegin = x;
        yBegin = y;
    }
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
    /* �}�E�X�{�^����������Ă���̈ړ��ʂ��v�Z���� */
    int xMove = x - xBegin;
    int yMove = y - yBegin;

    switch (PressButton)
    {
    /* �}�E�X���{�^���h���b�O���̏��� */
    /* ���_����ʊp�C�p�ɑ΂��ĉ�]������ */
    case GLUT_LEFT_BUTTON:
        CameraAzimuth   += (float)xMove / 2.0;
        CameraElevation += (float)yMove / 2.0;
        if (CameraElevation >  90.0) CameraElevation =  90.0;
        if (CameraElevation < -90.0) CameraElevation = -90.0;
        break;

    /* �}�E�X�E�{�^���h���b�O���̏��� */
    /* ���_�����s�������ɑO��Ɉړ������� */
    case GLUT_RIGHT_BUTTON:
        CameraDistance += (float)yMove / 40.0;
        break;
    }
    CameraX = CameraDistance * cos(CameraAzimuth * RAD) * cos(CameraElevation * RAD);
    CameraY = CameraDistance * sin(CameraElevation * RAD);
    CameraZ = CameraDistance * sin(CameraAzimuth * RAD) * cos(CameraElevation * RAD);
    printf("Camera AZ:%.1f, EL:%.1f, dist:%.1f, x,y,z= %.1f, %.1f, %.1f\n", 
        CameraAzimuth, CameraElevation, CameraDistance, CameraX, CameraY, CameraZ);

    /* ���݂̃}�E�X�|�C���^�̍��W�����̎n�_�p�ɋL�^���� */
    xBegin = x;
    yBegin = y;

    /* �`��v���i����� display() �֐����Ă΂��j */
    glutPostRedisplay();
}


/***********************************************************
|  �֐��FmyInit()
|  �����F�E�C���h�E�\���ƕ`��ݒ�̏�����
|  �����Fchar *windowTitle      �E�C���h�E�̃^�C�g���o�[�ɕ\�����镶����
|  �ߒl�F�Ȃ�
***********************************************************/
void myInit (char *windowTitle)
{
    /* �E�C���h�E�̃T�C�Y */
    int winWidth  = 400;
    int winHeight = 400;
    /* �E�C���h�E�̏c���̔���v�Z */
    float aspect = (float)winWidth / (float)winHeight;

    /* OpenGL�E�C���h�E�쐬�܂ł̏����� */
    glutInitWindowPosition(0, 0);                   /* �E�C���h�E�\���ʒu */
    glutInitWindowSize(winWidth, winHeight);        /* �E�C���h�E�T�C�Y */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);   /* �`�惂�[�h */
    glutCreateWindow(windowTitle);                  /* �E�C���h�E�̕\�� */
    glClearColor (0.0, 0.0, 0.0, 1.0);              /* ��ʏ����F�̐ݒ� */

    /* �C�x���g�������ɌĂяo���֐��̓o�^ */
    glutKeyboardFunc(keyboard);     /* �L�[�{�[�h���������� */
    glutMouseFunc   (mouseButton);  /* �}�E�X�{�^������������*/
    glutMotionFunc  (mouseDrag);    /* �}�E�X�h���b�O������ */
    glutDisplayFunc (display);      /* ��ʕ\�� */
    glutTimerFunc(15, timer, 0);    /* �^�C�}�[��15�~���b��ɐݒ� */

    /* CG�`��ݒ� */
    glMatrixMode(GL_PROJECTION);    /* �������e(���ߓ��e�@)�ݒ胂�[�h�ɐ؂�ւ� */
    glLoadIdentity();               /* �������e�s��������� */
    gluPerspective(45.0, aspect, 1.0, 20.0);    /* �������e�s��̐ݒ� */
      /* ����p45�x, �c���� aspect�C�`��O�ʂ܂ł̉��s 1.0�C�`��w�ʂ܂ł̉��s 20.0 */
    glEnable(GL_DEPTH_TEST);        /* �B�ʏ�����L���ɂ��� */
}