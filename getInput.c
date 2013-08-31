/***********************************************************
	文件名称： 接受键盘输入
	作 者： 黄昱恺
	版 本： 5.0
	说 明： 接受键盘输入
	电梯按钮、策略类型
	修改记录：增加安全响应 修改人:黄昱恺
***********************************************************/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "egg.h"
#include "list.h"
#include "sharedVariables.h"
//外部变量的引用
extern HANDLE hMutex;
extern HEGG background, elevator, button, head, string;
extern int buttonUp[10];
extern int buttonDown[10];
extern int buttonNumber[10];
extern int currentFloor;
extern int nextFloor;
extern int moveDirection;//运行方向
extern int state;
extern int Profile;
extern int profileChange;
extern int blockedFloor;
extern int Go;
int ignore = 0;//判断是否安全运行


void controllight(char input)
{
    if ( ((checkFloor(input) > blockedFloor || (checkFloor(input) == 1) && Profile == D) || Profile != D))
    {

        switch(input)//根据输入点亮不同的按钮或者切换策略
        {
            case '\n'
                    ://忽略所有回车输入
                break;

                //电梯向上的按钮的请求
            case 'q'
                    :
                if(currentFloor != 1 || (currentFloor == 1 && state != STOP))
                {
                    buttonUp[1] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮
                }

                break;

            case 'w'
                    :
                if(currentFloor != 2 || (currentFloor == 2 && state != STOP))
                {
                    buttonUp[2] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 2))
                    {
                        ignore = 2;
                    }
                }

                break;

            case 'e'
                    :
                if(currentFloor != 3 || (currentFloor == 3 && state != STOP))
                {
                    buttonUp[3] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 3))
                    {
                        ignore = 3;
                    }
                }

                break;

            case 'r'
                    :
                if(currentFloor != 4 || (currentFloor == 4 && state != STOP))
                {
                    buttonUp[4] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 4))
                    {
                        ignore = 4;
                    }
                }

                break;

            case 't'
                    :
                if(currentFloor != 5 || (currentFloor == 5 && state != STOP))
                {
                    buttonUp[5] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 5))
                    {
                        ignore = 5;
                    }
                }

                break;

            case 'y'
                    :
                if(currentFloor != 6 || (currentFloor == 6 && state != STOP))
                {
                    buttonUp[6] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 6))
                    {
                        ignore = 6;
                    }
                }

                break;

            case 'u'
                    :
                if(currentFloor != 7 || (currentFloor == 7 && state != STOP))
                {
                    buttonUp[7] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 7))
                    {
                        ignore = 7;
                    }
                }

                break;

            case 'i'
                    :
                if(currentFloor != 8 || (currentFloor == 8 && state != STOP))
                {
                    buttonUp[8] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 8))
                    {
                        ignore = 8;
                    }
                }

                break;

                //电梯向下按钮的请求
            case 'a'
                    :
                if(currentFloor != 2 || (currentFloor == 2 && state != STOP))
                {
                    buttonDown[2] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 2))
                    {
                        ignore = 2;
                    }
                }

                break;

            case 's'
                    :
                if(currentFloor != 3 || (currentFloor == 3 && state != STOP))
                {
                    buttonDown[3] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 3))
                    {
                        ignore = 3;
                    }
                }

                break;

            case 'd'
                    :
                if(currentFloor != 4 || (currentFloor == 4 && state != STOP))
                {
                    buttonDown[4] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 4))
                    {
                        ignore = 4;
                    }
                }

                break;

            case 'f'
                    :
                if(currentFloor != 5 || (currentFloor == 5 && state != STOP))
                {
                    buttonDown[5] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 5))
                    {
                        ignore = 5;
                    }
                }

                break;

            case 'g'
                    :
                if(currentFloor != 6 || (currentFloor == 6 && state != STOP))
                {
                    buttonDown[6] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 6))
                    {
                        ignore = 6;
                    }
                }

                break;

            case 'h'
                    :
                if(currentFloor != 7 || (currentFloor == 7 && state != STOP))
                {
                    buttonDown[7] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 7))
                    {
                        ignore = 7;
                    }
                }

                break;

            case 'j'
                    :
                if(currentFloor != 8 || (currentFloor == 8 && state != STOP))
                {
                    buttonDown[8] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                    if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 8))
                    {
                        ignore = 8;
                    }
                }

                break;

            case 'k'
                    :
                if(currentFloor != 9 || (currentFloor == 9 && state != STOP))
                {
                    buttonDown[9] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮
                }

                break;

                //电梯内部按钮请求
            case '1'
                    :
                if(currentFloor != 1 || (currentFloor == 1 && state != STOP))
                {
                    buttonNumber[1] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮
                }

                break;

            case '2'
                    :
                if(currentFloor != 2 || (currentFloor == 2 && state != STOP))
                {
                    if (state == RUN && ((currentFloor + moveDirection) == 2))
                    {
                        ignore = 2;
                    }

                    buttonNumber[2] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                }

                break;

            case '3'
                    :
                if(currentFloor != 3 || (currentFloor == 3 && state != STOP))
                {
                    if (state == RUN && ((currentFloor + moveDirection) == 3))
                    {
                        ignore = 3;
                    }

                    buttonNumber[3] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                }

                break;

            case '4'
                    :
                if(currentFloor != 4 || (currentFloor == 4 && state != STOP))
                {
                    if (state == RUN && ((currentFloor + moveDirection) == 4))
                    {
                        ignore = 4;
                    }

                    buttonNumber[4] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                }

                break;

            case '5'
                    :
                if(currentFloor != 5 || (currentFloor == 5 && state != STOP))
                {
                    if (state == RUN && ((currentFloor + moveDirection) == 5))
                    {
                        ignore = 5;
                    }

                    buttonNumber[5] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                }

                break;

            case '6'
                    :
                if(currentFloor != 6 || (currentFloor == 6 && state != STOP))
                {
                    if (state == RUN && ((currentFloor + moveDirection) == 6))
                    {
                        ignore = 6;
                    }

                    buttonNumber[6] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮//点亮按钮

                }

                break;

            case '7'
                    :
                if(currentFloor != 7 || (currentFloor == 7 && state != STOP))
                {
                    if (state == RUN && ((currentFloor + moveDirection) == 7))
                    {
                        ignore = 7;
                    }

                    buttonNumber[7] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                }

                break;

            case '8'
                    :
                if(currentFloor != 8 || (currentFloor == 8 && state != STOP))
                {
                    if (state == RUN && ((currentFloor + moveDirection) == 8))
                    {
                        ignore = 8;
                    }

                    buttonNumber[8] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮

                }

                break;

            case '9'
                    :
                if(currentFloor != 9 || (currentFloor == 9 && state != STOP))
                {
                    buttonNumber[9] = 1;
                    createList(input);//创建链表
                    lightOn(input);//点亮按钮
                }

                break;

            case 'G'
                    :
                Go = 1;
                Sleep(10);
                Go = 0;
                break;

                //策略切换
            case 'A'
                    :
                Profile = A;
                profileChange = 1;
                WaitForSingleObject(hMutex, INFINITE);//互斥对象
                SetActiveEgg(button);
                MovePen(672, 512);
                DrawBitmap("img\\A.bmp");
                MovePen(687, 226);
                DrawBitmap("img\\showa.bmp");
                ReleaseMutex(hMutex);//释放互斥对象
                break;

            case 'B'
                    :
                Profile = B;
                profileChange = 1;
                WaitForSingleObject(hMutex, INFINITE);//互斥对象
                SetActiveEgg(button);
                MovePen(672, 512);
                DrawBitmap("img\\B.bmp");
                MovePen(687, 226);
                DrawBitmap("img\\showb.bmp");
                ReleaseMutex(hMutex);//释放互斥对象
                break;

            case 'C'
                    :
                Profile = C;
                profileChange = 1;
                WaitForSingleObject(hMutex, INFINITE);//互斥对象
                SetActiveEgg(button);
                MovePen(672, 512);
                DrawBitmap("img\\C.bmp");
                MovePen(687, 226);
                DrawBitmap("img\\showc.bmp");
                ReleaseMutex(hMutex);//释放互斥对象
                break;

            case 'D'
                    :
                Profile = D;
                profileChange = 1;
                WaitForSingleObject(hMutex, INFINITE);//互斥对象
                SetActiveEgg(button);
                MovePen(672, 512);
                DrawBitmap("img\\D.bmp");
                MovePen(687, 226);
                DrawBitmap("img\\showd.bmp");
                ReleaseMutex(hMutex);//释放互斥对象
                break;

            case 'E'
                    :
                Profile = E;
                profileChange = 1;
                WaitForSingleObject(hMutex, INFINITE);//互斥对象
                SetActiveEgg(button);
                MovePen(672, 512);
                DrawBitmap("img\\E.bmp");
                MovePen(687, 226);
                DrawBitmap("img\\showe.bmp");
                ReleaseMutex(hMutex);//释放互斥对象
                break;

            case 'F'
                    :
                Profile = F;
                profileChange = 1;
                WaitForSingleObject(hMutex, INFINITE);//互斥对象
                SetActiveEgg(button);
                MovePen(672, 512);
                DrawBitmap("img\\F.bmp");
                MovePen(687, 226);
                DrawBitmap("img\\showf.bmp");

                ReleaseMutex(hMutex);//释放互斥对象
                break;

                //其余输入均为非法输入
            default
                    :
                printf("\b输入错误，请重新输入！");
                break;
        }//end of switch
    }
}
/***********************************************************
	函数名称：getInput()
	函数功能： 获得键盘的指令
	入口参数： 无
	出口参数： 无
	备 注： 使用getche可不用回车
***********************************************************/
void getInput(void)//得到键盘输入指令
{
    char input;//当前输入字符

    while(1)
    {
        input = getche();
        controllight(input);//判断输入对应的响应
    }//end of while
}


