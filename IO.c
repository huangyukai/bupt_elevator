/***********************************************************
	�ļ����ƣ� ���ݵ�ͼ�ν��������DOS��������
	�� �ߣ� ������
	�� ���� 1.0
	˵ ���� �����������ͼ�ν���������ͼ�ν���ļ������룬�Լ�����print_message���DOS����
	�޸ļ�¼�� 1���޸��Ҽ��������           �޸��ˣ�������
***********************************************************/
#include "egg.h"
#include "graphical_interface.h"
#include "list.h"
//��������
#define INSIDE_BUTTON_LENGTH 67
#define INSIDE_BUTTON_HEIGHT 67
#define OUTSIDE_BUTTON_LENGTH 30
#define OUTSIDE_BUTTON_HEIGHT 30
#define ELEVATOR_GO 73
#define ELEVATOR_OPEN 73
#define ELEVATOR_HEIGHT 73
#define A 1
#define B 2
#define C 3
#define D 4
#define E 5
#define F 6

struct coordinates//����ṹ
{
    int x;
    int y;
};

extern struct coordinates elvator[10];
extern struct coordinates elevator_outside_button_up[10];
extern struct coordinates elevator_outside_button_down[10];
extern struct coordinates elevator_inside_button[10];
extern struct coordinates elevator_go;
extern struct coordinates elevator_open;
extern int profileChange;
extern int startexit;
extern int buttonUp[10]; //�������ϰ�ť
extern int buttonDown[10]; //�������°�ť
extern int buttonNumber[10]; //�����ڲ���ť
extern int Go;
extern int openbutton;
extern HANDLE hMutex;
extern int Profile;
extern HEGG background, elevator, button, head, string;
extern int blockedFloor;
/***********************************************************
	�������ƣ� IO()
	�������ܣ� ������ݵ�ͼ����������DOS�������
	��ڲ����� ��
	���ڲ����� ��
	�� ע��
***********************************************************/
void IO(void)
{
    EVENT_TYPE ev;
    StartTimer  (700);//�趨�����DOS�����Ƶ��

    while ((ev = WaitForEvent()) != EXIT)
    {

        switch (ev)
        {
            case
                    MOUSEMOVE://����ƶ��������̵��ж�
                {
                    int x, y;

                    x = GetMouseX();//���X����
                    y = GetMouseY();//���Y����

                    if ( ( x >= 672 && x <= 710 ) && ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//��������
                        SetActiveEgg(button);//��button��egg�ϲ���
                        MovePen(687, 226);
                        DrawBitmap("img\\showa.bmp");
                        ReleaseMutex(hMutex);//�ͷŻ������
                    }

                    if ( ( x >= 717 && x <= 755 ) &&  ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//��������
                        SetActiveEgg(button);//��button��egg�ϲ���
                        MovePen(687, 226);
                        DrawBitmap("img\\showb.bmp");
                        ReleaseMutex(hMutex);//�ͷŻ������
                    }

                    if ( ( x >= 762 && x <= 800 ) && ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//��������
                        SetActiveEgg(button);//��button��egg�ϲ���
                        MovePen(687, 226);
                        DrawBitmap("img\\showc.bmp");
                        ReleaseMutex(hMutex);//�ͷŻ������
                    }

                    if ( ( x >= 807 && x <= 845 ) && ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//��������
                        SetActiveEgg(button);//��button��egg�ϲ���
                        MovePen(687, 226);
                        DrawBitmap("img\\showd.bmp");
                        ReleaseMutex(hMutex);//�ͷŻ������
                    }

                    if ( ( x >= 852 && x <= 890 ) && ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//��������
                        SetActiveEgg(button);//��button��egg�ϲ���
                        MovePen(687, 226);
                        DrawBitmap("img\\showe.bmp");
                        ReleaseMutex(hMutex);//�ͷŻ������
                    }

                    if ( ( x >= 897 && x <= 935 ) && ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//��������
                        SetActiveEgg(button);//��button��egg�ϲ���
                        MovePen(687, 226);
                        DrawBitmap("img\\showf.bmp");
                        ReleaseMutex(hMutex);//�ͷŻ������
                    }

                }

                break;

            case
                    TIMER://��ʱ����ʱ�����DOS����
                print_message();
                break;

            case
                    KEYDOWN://��갴��
                switch(GetStruckKey())
                {
                    case
                            VK_LBUTTON://�������
                        {
                            int x, y;
                            x = GetMouseX();//���X����
                            y = GetMouseY();//���Y����

                            //�жϰ�ť
                            if ( ( x >= 672 && x <= 710 ) && ( y >= 512 && y <= 572 ) )
                            {
                                Profile = A;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//��������
                                SetActiveEgg(button);//��button��egg�ϲ���
                                MovePen(672, 512);
                                DrawBitmap("img\\A.bmp");
                                ReleaseMutex(hMutex);//�ͷŻ������
                            }

                            if ( ( x >= 717 && x <= 755 ) &&  ( y >= 512 && y <= 572 ) )
                            {
                                Profile = B;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//��������
                                SetActiveEgg(button);//��button��egg�ϲ���
                                MovePen(672, 512);
                                DrawBitmap("img\\B.bmp");
                                ReleaseMutex(hMutex);//�ͷŻ������
                            }

                            if ( ( x >= 762 && x <= 800 ) && ( y >= 512 && y <= 572 ) )
                            {
                                Profile = C;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//��������
                                SetActiveEgg(button);//��button��egg�ϲ���
                                MovePen(672, 512);
                                DrawBitmap("img\\C.bmp");
                                ReleaseMutex(hMutex);//�ͷŻ������

                            }

                            if ( ( x >= 807 && x <= 845 ) && ( y >= 512 && y <= 572 ) )
                            {

                                Profile = D;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//��������
                                SetActiveEgg(button);//��button��egg�ϲ���
                                MovePen(672, 512);
                                DrawBitmap("img\\D.bmp");
                                ReleaseMutex(hMutex);//�ͷŻ������

                            }

                            if ( ( x >= 852 && x <= 890 ) && ( y >= 512 && y <= 572 ) )
                            {

                                Profile = E;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//��������
                                SetActiveEgg(button);//��button��egg�ϲ���
                                MovePen(672, 512);
                                DrawBitmap("img\\E.bmp");

                                ReleaseMutex(hMutex);//�ͷŻ������

                            }

                            if ( ( x >= 897 && x <= 935 ) && ( y >= 512 && y <= 572 ) )
                            {
                                Profile = F;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//��������
                                SetActiveEgg(button);//��button��egg�ϲ���
                                MovePen(672, 512);
                                DrawBitmap("img\\F.bmp");
                                ReleaseMutex(hMutex);//�ͷŻ������

                            }


                            if ( ( x >= elevator_go.x && x <= (elevator_go.x + ELEVATOR_GO) ) && ( y >= elevator_go.y && y <= elevator_go.y + ELEVATOR_GO ) )
                            {
                                Go = 1;
                                lightOn('G');//����ͼ��
                                Sleep(100);

                            }


                            if ( ( x >= elevator_open.x && x <= (elevator_open.x + ELEVATOR_OPEN) ) && ( y >= elevator_open.y && y <= elevator_open.y + ELEVATOR_OPEN ) )
                            {
                                openbutton = 1;
                                lightOn('O');//����ͼ��
                            }


                            if ( ( x >= elevator_inside_button[1].x && x <= (elevator_inside_button[1].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[1].y && y <= elevator_inside_button[1].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                lightOn('1');//����ͼ��
                                createList('1');
                                buttonNumber[1] = 1;

                            }

                            if ( ( x >= elevator_inside_button[2].x && x <= (elevator_inside_button[2].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[2].y && y <= elevator_inside_button[2].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('2') <= blockedFloor && Profile == D && Profile == D)
                                {
                                    break;
                                }

                                lightOn('2');//����ͼ��
                                createList('2');
                                buttonNumber[2] = 1;
                            }

                            if ( ( x >= elevator_inside_button[3].x && x <= (elevator_inside_button[3].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[3].y && y <= elevator_inside_button[3].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('3') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('3');//����ͼ��
                                createList('3');
                                buttonNumber[3] = 1;
                            }

                            if ( ( x >= elevator_inside_button[4].x && x <= (elevator_inside_button[4].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[4].y && y <= elevator_inside_button[4].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('4') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('4');//����ͼ��
                                createList('4');
                                buttonNumber[4] = 1;
                            }

                            if ( ( x >= elevator_inside_button[5].x && x <= (elevator_inside_button[5].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[5].y && y <= elevator_inside_button[5].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('5') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('5');//����ͼ��
                                createList('5');
                                buttonNumber[5] = 1;
                            }

                            if ( ( x >= elevator_inside_button[6].x && x <= (elevator_inside_button[6].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[6].y && y <= elevator_inside_button[6].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('6') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('6');//����ͼ��
                                createList('6');
                                buttonNumber[6] = 1;
                            }

                            if ( ( x >= elevator_inside_button[7].x && x <= (elevator_inside_button[7].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[7].y && y <= elevator_inside_button[7].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('7') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('7');//����ͼ��
                                createList('7');
                                buttonNumber[7] = 1;
                            }

                            if ( ( x >= elevator_inside_button[8].x && x <= (elevator_inside_button[8].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[8].y && y <= elevator_inside_button[8].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('8') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('8');//����ͼ��
                                createList('8');
                                buttonNumber[8] = 1;
                            }

                            if ( ( x >= elevator_inside_button[9].x && x <= (elevator_inside_button[9].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[9].y && y <= elevator_inside_button[9].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('9') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('9');//����ͼ��
                                createList('9');
                                buttonNumber[9] = 1;
                            }


                            if ( ( x >= elevator_outside_button_up[1].x && x <= (elevator_outside_button_up[1].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[1].y && y <= elevator_outside_button_up[1].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                lightOn('q');//����ͼ��
                                createList('q');
                                buttonUp[1] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[2].x && x <= (elevator_outside_button_up[2].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[2].y && y <= elevator_outside_button_up[2].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('w') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('w');//����ͼ��
                                createList('w');
                                buttonUp[2] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[3].x && x <= (elevator_outside_button_up[3].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[3].y && y <= elevator_outside_button_up[3].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('e') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('e');//����ͼ��
                                createList('w');
                                buttonUp[3] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[4].x && x <= (elevator_outside_button_up[4].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[4].y && y <= elevator_outside_button_up[4].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('r') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('r');//����ͼ��
                                createList('r');
                                buttonUp[4] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[5].x && x <= (elevator_outside_button_up[5].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[5].y && y <= elevator_outside_button_up[5].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('t') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('t');//����ͼ��
                                createList('t');
                                buttonUp[5] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[6].x && x <= (elevator_outside_button_up[6].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[6].y && y <= elevator_outside_button_up[6].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('y') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('y');//����ͼ��
                                createList('y');
                                buttonUp[6] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[7].x && x <= (elevator_outside_button_up[7].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[7].y && y <= elevator_outside_button_up[7].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('u') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('u');//����ͼ��
                                createList('u');
                                buttonUp[7] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[8].x && x <= (elevator_outside_button_up[8].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[8].y && y <= elevator_outside_button_up[8].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('i') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('i');//����ͼ��
                                createList('i');
                                buttonUp[8] = 1;
                            }


                            if ( ( x >= elevator_outside_button_down[2].x && x <= (elevator_outside_button_down[2].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[2].y && y <= elevator_outside_button_down[2].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('a') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('a');//����ͼ��
                                createList('a');
                                buttonDown[2] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[3].x && x <= (elevator_outside_button_down[3].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[3].y && y <= elevator_outside_button_down[3].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('s') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('s');//����ͼ��
                                createList('s');
                                buttonDown[3] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[4].x && x <= (elevator_outside_button_down[4].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[4].y && y <= elevator_outside_button_down[4].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('d') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('d');//����ͼ��
                                createList('d');
                                buttonDown[4] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[5].x && x <= (elevator_outside_button_down[5].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[5].y && y <= elevator_outside_button_down[5].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('f') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('f');//����ͼ��
                                createList('f');
                                buttonDown[5] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[6].x && x <= (elevator_outside_button_down[6].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[6].y && y <= elevator_outside_button_down[6].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('g') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('g');//����ͼ��
                                createList('g');
                                buttonDown[6] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[7].x && x <= (elevator_outside_button_down[7].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[7].y && y <= elevator_outside_button_down[7].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('h') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('h');//����ͼ��
                                createList('h');
                                buttonDown[7] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[8].x && x <= (elevator_outside_button_down[8].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[8].y && y <= elevator_outside_button_down[8].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('j') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('j');//����ͼ��
                                createList('j');
                                buttonDown[8] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[9].x && x <= (elevator_outside_button_down[9].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[9].y && y <= elevator_outside_button_down[9].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('k') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('k');//����ͼ��
                                createList('k');
                                buttonDown[9] = 1;
                            }
                        }
                        break;

                        //��egg���水�¼��̰������ж�
                    case
                            81:
                        lightOn('q');//����ͼ��
                        createList('q');
                        buttonUp[1] = 1;
                        break;

                    case
                            87:
                        if (checkFloor('w') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('w');//����ͼ��
                        createList('w');
                        buttonUp[2] = 1;
                        break;

                    case
                            69:
                        if (checkFloor('e') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('e');//����ͼ��
                        createList('e');
                        buttonUp[3] = 1;
                        break;

                    case
                            82:
                        if (checkFloor('r') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('r');//����ͼ��
                        createList('r');
                        buttonUp[4] = 1;
                        break;

                    case
                            84:
                        if (checkFloor('t') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('t');//����ͼ��
                        createList('t');
                        buttonUp[5] = 1;
                        break;

                    case
                            89:
                        if (checkFloor('y') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('y');//����ͼ��
                        createList('y');
                        buttonUp[6] = 1;
                        break;

                    case
                            85:
                        if (checkFloor('u') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('u');//����ͼ��
                        createList('u');
                        buttonUp[7] = 1;
                        break;

                    case
                            73:
                        if (checkFloor('i') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('i');//����ͼ��
                        createList('i');
                        buttonUp[8] = 1;
                        break;

                    case
                            65:
                        if (checkFloor('a') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('a');//����ͼ��
                        createList('a');
                        buttonDown[2] = 1;
                        break;

                    case
                            83:
                        if (checkFloor('s') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('s');//����ͼ��
                        createList('s');
                        buttonDown[3] = 1;
                        break;

                    case
                            68:
                        if (checkFloor('d') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('d');//����ͼ��
                        createList('d');
                        buttonDown[4] = 1;
                        break;

                    case
                            70:
                        if (checkFloor('f') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('f');//����ͼ��
                        createList('f');
                        buttonDown[5] = 1;
                        break;

                    case
                            71:
                        if (checkFloor('g') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('g');//����ͼ��
                        createList('g');
                        buttonDown[6] = 1;
                        break;

                    case
                            72:
                        if (checkFloor('h') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('h');//����ͼ��
                        createList('h');
                        buttonDown[7] = 1;
                        break;

                    case
                            74:
                        if (checkFloor('j') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('j');//����ͼ��
                        createList('j');
                        buttonDown[8] = 1;
                        break;

                    case
                            75:
                        if (checkFloor('k') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('k');//����ͼ��
                        createList('k');
                        buttonDown[9] = 1;
                        break;

                    case
                            49:
                        lightOn('1');//����ͼ��
                        createList('1');
                        buttonNumber[1] = 1;
                        break;

                    case
                            50:
                        if (checkFloor('2') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('2');//����ͼ��
                        createList('2');
                        buttonNumber[2] = 1;
                        break;

                    case
                            51:
                        if (checkFloor('3') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('3');//����ͼ��
                        createList('3');
                        buttonNumber[3] = 1;
                        break;

                    case
                            52:
                        if (checkFloor('4') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        createList('4');//����ͼ��
                        lightOn('4');
                        buttonNumber[4] = 1;
                        break;

                    case
                            53:
                        if (checkFloor('5') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('5');//����ͼ��
                        createList('5');
                        buttonNumber[5] = 1;
                        break;

                    case
                            54:
                        if (checkFloor('6') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('6');//����ͼ��
                        createList('6');
                        buttonNumber[6] = 1;
                        break;

                    case
                            55:
                        if (checkFloor('7') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('7');//����ͼ��
                        createList('7');
                        buttonNumber[7] = 1;
                        break;

                    case
                            56:
                        if (checkFloor('8') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('8');//����ͼ��
                        createList('8');
                        buttonNumber[8] = 1;
                        break;

                    case
                            57:
                        if (checkFloor('9') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('9');//����ͼ��
                        createList('9');
                        buttonNumber[9] = 1;
                        break;

                }

                break;

            case
                    KEYUP://����̧��
                if (GetStruckKey() == VK_LBUTTON)//���Ϊ�����Ű����Ĵ���
                {
                    Go = 0;
                    lightOff('G');
                    openbutton = 0;
                    lightOff('O');
                }

                if (GetStruckKey() == VK_RBUTTON)   	//�簴��������Ҽ�,��������ϵ����Ի���,ѯ���Ƿ���ʾ����̨
                    if (IDYES == MessageBox(GetEggHwnd(), TEXT("�Ƿ���ʾDOS����̨?"),
                                            TEXT("Show console window"), MB_YESNO | MB_ICONQUESTION))
                    {
                        ShowConsoleWindow(1);
                    }
                    else
                    {
                        ShowConsoleWindow(0);
                    }

                break;
        }

    }

    StopTimer();
    //�رճ����Ȩ����
    MessageBox(NULL, TEXT("��Ȩ����(C)2011\n          ��л��ʹ��FGF����ϵͳ!\n          �鳤��������\n          ��Ա������ͥ����꿭\
		   \n"), TEXT("copyright"), MB_ICONINFORMATION);

    startexit = 1;//ͼ�ν���رձ�־
}
