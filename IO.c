/***********************************************************
	文件名称： 电梯的图形界面输入和DOS界面的输出
	作 者： 黄昱恺
	版 本： 1.0
	说 明： 负责接受来自图形界面的输入和图形界面的键盘输入，以及调用print_message输出DOS界面
	修改记录： 1、修改右键点击部分           修改人：黄昱恺
***********************************************************/
#include "egg.h"
#include "graphical_interface.h"
#include "list.h"
//常量定义
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

struct coordinates//坐标结构
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
extern int buttonUp[10]; //电梯向上按钮
extern int buttonDown[10]; //电梯向下按钮
extern int buttonNumber[10]; //电梯内部按钮
extern int Go;
extern int openbutton;
extern HANDLE hMutex;
extern int Profile;
extern HEGG background, elevator, button, head, string;
extern int blockedFloor;
/***********************************************************
	函数名称： IO()
	函数功能： 负责电梯的图像界面输入和DOS界面输出
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void IO(void)
{
    EVENT_TYPE ev;
    StartTimer  (700);//设定输出到DOS界面的频率

    while ((ev = WaitForEvent()) != EXIT)
    {

        switch (ev)
        {
            case
                    MOUSEMOVE://鼠标移动到策略盘得判断
                {
                    int x, y;

                    x = GetMouseX();//获得X坐标
                    y = GetMouseY();//获得Y坐标

                    if ( ( x >= 672 && x <= 710 ) && ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//声明互斥
                        SetActiveEgg(button);//在button的egg上操作
                        MovePen(687, 226);
                        DrawBitmap("img\\showa.bmp");
                        ReleaseMutex(hMutex);//释放互斥对象
                    }

                    if ( ( x >= 717 && x <= 755 ) &&  ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//声明互斥
                        SetActiveEgg(button);//在button的egg上操作
                        MovePen(687, 226);
                        DrawBitmap("img\\showb.bmp");
                        ReleaseMutex(hMutex);//释放互斥对象
                    }

                    if ( ( x >= 762 && x <= 800 ) && ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//声明互斥
                        SetActiveEgg(button);//在button的egg上操作
                        MovePen(687, 226);
                        DrawBitmap("img\\showc.bmp");
                        ReleaseMutex(hMutex);//释放互斥对象
                    }

                    if ( ( x >= 807 && x <= 845 ) && ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//声明互斥
                        SetActiveEgg(button);//在button的egg上操作
                        MovePen(687, 226);
                        DrawBitmap("img\\showd.bmp");
                        ReleaseMutex(hMutex);//释放互斥对象
                    }

                    if ( ( x >= 852 && x <= 890 ) && ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//声明互斥
                        SetActiveEgg(button);//在button的egg上操作
                        MovePen(687, 226);
                        DrawBitmap("img\\showe.bmp");
                        ReleaseMutex(hMutex);//释放互斥对象
                    }

                    if ( ( x >= 897 && x <= 935 ) && ( y >= 512 && y <= 572 ) )
                    {
                        WaitForSingleObject(hMutex, INFINITE);//声明互斥
                        SetActiveEgg(button);//在button的egg上操作
                        MovePen(687, 226);
                        DrawBitmap("img\\showf.bmp");
                        ReleaseMutex(hMutex);//释放互斥对象
                    }

                }

                break;

            case
                    TIMER://定时器到时间输出DOS窗口
                print_message();
                break;

            case
                    KEYDOWN://鼠标按下
                switch(GetStruckKey())
                {
                    case
                            VK_LBUTTON://左键按下
                        {
                            int x, y;
                            x = GetMouseX();//获得X坐标
                            y = GetMouseY();//获得Y坐标

                            //判断按钮
                            if ( ( x >= 672 && x <= 710 ) && ( y >= 512 && y <= 572 ) )
                            {
                                Profile = A;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//声明互斥
                                SetActiveEgg(button);//在button的egg上操作
                                MovePen(672, 512);
                                DrawBitmap("img\\A.bmp");
                                ReleaseMutex(hMutex);//释放互斥对象
                            }

                            if ( ( x >= 717 && x <= 755 ) &&  ( y >= 512 && y <= 572 ) )
                            {
                                Profile = B;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//声明互斥
                                SetActiveEgg(button);//在button的egg上操作
                                MovePen(672, 512);
                                DrawBitmap("img\\B.bmp");
                                ReleaseMutex(hMutex);//释放互斥对象
                            }

                            if ( ( x >= 762 && x <= 800 ) && ( y >= 512 && y <= 572 ) )
                            {
                                Profile = C;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//声明互斥
                                SetActiveEgg(button);//在button的egg上操作
                                MovePen(672, 512);
                                DrawBitmap("img\\C.bmp");
                                ReleaseMutex(hMutex);//释放互斥对象

                            }

                            if ( ( x >= 807 && x <= 845 ) && ( y >= 512 && y <= 572 ) )
                            {

                                Profile = D;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//声明互斥
                                SetActiveEgg(button);//在button的egg上操作
                                MovePen(672, 512);
                                DrawBitmap("img\\D.bmp");
                                ReleaseMutex(hMutex);//释放互斥对象

                            }

                            if ( ( x >= 852 && x <= 890 ) && ( y >= 512 && y <= 572 ) )
                            {

                                Profile = E;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//声明互斥
                                SetActiveEgg(button);//在button的egg上操作
                                MovePen(672, 512);
                                DrawBitmap("img\\E.bmp");

                                ReleaseMutex(hMutex);//释放互斥对象

                            }

                            if ( ( x >= 897 && x <= 935 ) && ( y >= 512 && y <= 572 ) )
                            {
                                Profile = F;
                                profileChange = 1;
                                WaitForSingleObject(hMutex, INFINITE);//声明互斥
                                SetActiveEgg(button);//在button的egg上操作
                                MovePen(672, 512);
                                DrawBitmap("img\\F.bmp");
                                ReleaseMutex(hMutex);//释放互斥对象

                            }


                            if ( ( x >= elevator_go.x && x <= (elevator_go.x + ELEVATOR_GO) ) && ( y >= elevator_go.y && y <= elevator_go.y + ELEVATOR_GO ) )
                            {
                                Go = 1;
                                lightOn('G');//点亮图标
                                Sleep(100);

                            }


                            if ( ( x >= elevator_open.x && x <= (elevator_open.x + ELEVATOR_OPEN) ) && ( y >= elevator_open.y && y <= elevator_open.y + ELEVATOR_OPEN ) )
                            {
                                openbutton = 1;
                                lightOn('O');//点亮图标
                            }


                            if ( ( x >= elevator_inside_button[1].x && x <= (elevator_inside_button[1].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[1].y && y <= elevator_inside_button[1].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                lightOn('1');//点亮图标
                                createList('1');
                                buttonNumber[1] = 1;

                            }

                            if ( ( x >= elevator_inside_button[2].x && x <= (elevator_inside_button[2].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[2].y && y <= elevator_inside_button[2].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('2') <= blockedFloor && Profile == D && Profile == D)
                                {
                                    break;
                                }

                                lightOn('2');//点亮图标
                                createList('2');
                                buttonNumber[2] = 1;
                            }

                            if ( ( x >= elevator_inside_button[3].x && x <= (elevator_inside_button[3].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[3].y && y <= elevator_inside_button[3].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('3') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('3');//点亮图标
                                createList('3');
                                buttonNumber[3] = 1;
                            }

                            if ( ( x >= elevator_inside_button[4].x && x <= (elevator_inside_button[4].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[4].y && y <= elevator_inside_button[4].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('4') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('4');//点亮图标
                                createList('4');
                                buttonNumber[4] = 1;
                            }

                            if ( ( x >= elevator_inside_button[5].x && x <= (elevator_inside_button[5].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[5].y && y <= elevator_inside_button[5].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('5') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('5');//点亮图标
                                createList('5');
                                buttonNumber[5] = 1;
                            }

                            if ( ( x >= elevator_inside_button[6].x && x <= (elevator_inside_button[6].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[6].y && y <= elevator_inside_button[6].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('6') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('6');//点亮图标
                                createList('6');
                                buttonNumber[6] = 1;
                            }

                            if ( ( x >= elevator_inside_button[7].x && x <= (elevator_inside_button[7].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[7].y && y <= elevator_inside_button[7].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('7') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('7');//点亮图标
                                createList('7');
                                buttonNumber[7] = 1;
                            }

                            if ( ( x >= elevator_inside_button[8].x && x <= (elevator_inside_button[8].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[8].y && y <= elevator_inside_button[8].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('8') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('8');//点亮图标
                                createList('8');
                                buttonNumber[8] = 1;
                            }

                            if ( ( x >= elevator_inside_button[9].x && x <= (elevator_inside_button[9].x + INSIDE_BUTTON_LENGTH) ) && ( y >= elevator_inside_button[9].y && y <= elevator_inside_button[9].y + INSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('9') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('9');//点亮图标
                                createList('9');
                                buttonNumber[9] = 1;
                            }


                            if ( ( x >= elevator_outside_button_up[1].x && x <= (elevator_outside_button_up[1].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[1].y && y <= elevator_outside_button_up[1].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                lightOn('q');//点亮图标
                                createList('q');
                                buttonUp[1] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[2].x && x <= (elevator_outside_button_up[2].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[2].y && y <= elevator_outside_button_up[2].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('w') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('w');//点亮图标
                                createList('w');
                                buttonUp[2] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[3].x && x <= (elevator_outside_button_up[3].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[3].y && y <= elevator_outside_button_up[3].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('e') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('e');//点亮图标
                                createList('w');
                                buttonUp[3] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[4].x && x <= (elevator_outside_button_up[4].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[4].y && y <= elevator_outside_button_up[4].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('r') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('r');//点亮图标
                                createList('r');
                                buttonUp[4] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[5].x && x <= (elevator_outside_button_up[5].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[5].y && y <= elevator_outside_button_up[5].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('t') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('t');//点亮图标
                                createList('t');
                                buttonUp[5] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[6].x && x <= (elevator_outside_button_up[6].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[6].y && y <= elevator_outside_button_up[6].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('y') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('y');//点亮图标
                                createList('y');
                                buttonUp[6] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[7].x && x <= (elevator_outside_button_up[7].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[7].y && y <= elevator_outside_button_up[7].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('u') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('u');//点亮图标
                                createList('u');
                                buttonUp[7] = 1;
                            }

                            if ( ( x >= elevator_outside_button_up[8].x && x <= (elevator_outside_button_up[8].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_up[8].y && y <= elevator_outside_button_up[8].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('i') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('i');//点亮图标
                                createList('i');
                                buttonUp[8] = 1;
                            }


                            if ( ( x >= elevator_outside_button_down[2].x && x <= (elevator_outside_button_down[2].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[2].y && y <= elevator_outside_button_down[2].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('a') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('a');//点亮图标
                                createList('a');
                                buttonDown[2] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[3].x && x <= (elevator_outside_button_down[3].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[3].y && y <= elevator_outside_button_down[3].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('s') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('s');//点亮图标
                                createList('s');
                                buttonDown[3] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[4].x && x <= (elevator_outside_button_down[4].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[4].y && y <= elevator_outside_button_down[4].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('d') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('d');//点亮图标
                                createList('d');
                                buttonDown[4] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[5].x && x <= (elevator_outside_button_down[5].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[5].y && y <= elevator_outside_button_down[5].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('f') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('f');//点亮图标
                                createList('f');
                                buttonDown[5] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[6].x && x <= (elevator_outside_button_down[6].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[6].y && y <= elevator_outside_button_down[6].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('g') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('g');//点亮图标
                                createList('g');
                                buttonDown[6] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[7].x && x <= (elevator_outside_button_down[7].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[7].y && y <= elevator_outside_button_down[7].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('h') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('h');//点亮图标
                                createList('h');
                                buttonDown[7] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[8].x && x <= (elevator_outside_button_down[8].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[8].y && y <= elevator_outside_button_down[8].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('j') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('j');//点亮图标
                                createList('j');
                                buttonDown[8] = 1;
                            }

                            if ( ( x >= elevator_outside_button_down[9].x && x <= (elevator_outside_button_down[9].x + OUTSIDE_BUTTON_LENGTH) ) && ( y >= elevator_outside_button_down[9].y && y <= elevator_outside_button_down[9].y + OUTSIDE_BUTTON_HEIGHT ) )
                            {
                                if (checkFloor('k') <= blockedFloor && Profile == D)
                                {
                                    break;
                                }

                                lightOn('k');//点亮图标
                                createList('k');
                                buttonDown[9] = 1;
                            }
                        }
                        break;

                        //在egg界面按下键盘按键的判断
                    case
                            81:
                        lightOn('q');//点亮图标
                        createList('q');
                        buttonUp[1] = 1;
                        break;

                    case
                            87:
                        if (checkFloor('w') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('w');//点亮图标
                        createList('w');
                        buttonUp[2] = 1;
                        break;

                    case
                            69:
                        if (checkFloor('e') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('e');//点亮图标
                        createList('e');
                        buttonUp[3] = 1;
                        break;

                    case
                            82:
                        if (checkFloor('r') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('r');//点亮图标
                        createList('r');
                        buttonUp[4] = 1;
                        break;

                    case
                            84:
                        if (checkFloor('t') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('t');//点亮图标
                        createList('t');
                        buttonUp[5] = 1;
                        break;

                    case
                            89:
                        if (checkFloor('y') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('y');//点亮图标
                        createList('y');
                        buttonUp[6] = 1;
                        break;

                    case
                            85:
                        if (checkFloor('u') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('u');//点亮图标
                        createList('u');
                        buttonUp[7] = 1;
                        break;

                    case
                            73:
                        if (checkFloor('i') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('i');//点亮图标
                        createList('i');
                        buttonUp[8] = 1;
                        break;

                    case
                            65:
                        if (checkFloor('a') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('a');//点亮图标
                        createList('a');
                        buttonDown[2] = 1;
                        break;

                    case
                            83:
                        if (checkFloor('s') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('s');//点亮图标
                        createList('s');
                        buttonDown[3] = 1;
                        break;

                    case
                            68:
                        if (checkFloor('d') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('d');//点亮图标
                        createList('d');
                        buttonDown[4] = 1;
                        break;

                    case
                            70:
                        if (checkFloor('f') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('f');//点亮图标
                        createList('f');
                        buttonDown[5] = 1;
                        break;

                    case
                            71:
                        if (checkFloor('g') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('g');//点亮图标
                        createList('g');
                        buttonDown[6] = 1;
                        break;

                    case
                            72:
                        if (checkFloor('h') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('h');//点亮图标
                        createList('h');
                        buttonDown[7] = 1;
                        break;

                    case
                            74:
                        if (checkFloor('j') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('j');//点亮图标
                        createList('j');
                        buttonDown[8] = 1;
                        break;

                    case
                            75:
                        if (checkFloor('k') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('k');//点亮图标
                        createList('k');
                        buttonDown[9] = 1;
                        break;

                    case
                            49:
                        lightOn('1');//点亮图标
                        createList('1');
                        buttonNumber[1] = 1;
                        break;

                    case
                            50:
                        if (checkFloor('2') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('2');//点亮图标
                        createList('2');
                        buttonNumber[2] = 1;
                        break;

                    case
                            51:
                        if (checkFloor('3') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('3');//点亮图标
                        createList('3');
                        buttonNumber[3] = 1;
                        break;

                    case
                            52:
                        if (checkFloor('4') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        createList('4');//点亮图标
                        lightOn('4');
                        buttonNumber[4] = 1;
                        break;

                    case
                            53:
                        if (checkFloor('5') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('5');//点亮图标
                        createList('5');
                        buttonNumber[5] = 1;
                        break;

                    case
                            54:
                        if (checkFloor('6') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('6');//点亮图标
                        createList('6');
                        buttonNumber[6] = 1;
                        break;

                    case
                            55:
                        if (checkFloor('7') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('7');//点亮图标
                        createList('7');
                        buttonNumber[7] = 1;
                        break;

                    case
                            56:
                        if (checkFloor('8') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('8');//点亮图标
                        createList('8');
                        buttonNumber[8] = 1;
                        break;

                    case
                            57:
                        if (checkFloor('9') <= blockedFloor && Profile == D)
                        {
                            break;
                        }

                        lightOn('9');//点亮图标
                        createList('9');
                        buttonNumber[9] = 1;
                        break;

                }

                break;

            case
                    KEYUP://按键抬起
                if (GetStruckKey() == VK_LBUTTON)//左键为开关门按键的处理
                {
                    Go = 0;
                    lightOff('G');
                    openbutton = 0;
                    lightOff('O');
                }

                if (GetStruckKey() == VK_RBUTTON)   	//如按的是鼠标右键,则在面板上弹出对话框,询问是否显示控制台
                    if (IDYES == MessageBox(GetEggHwnd(), TEXT("是否显示DOS控制台?"),
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
    //关闭程序版权声明
    MessageBox(NULL, TEXT("版权所有(C)2011\n          感谢您使用FGF电梯系统!\n          组长：黄昱恺\n          组员：胡梓庭、李宏凯\
		   \n"), TEXT("copyright"), MB_ICONINFORMATION);

    startexit = 1;//图形界面关闭标志
}
