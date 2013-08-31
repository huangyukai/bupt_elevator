/***********************************************************
文件名称：输出
作 者： 黄昱恺
版 本： 1.0
说 明： 输出电梯所有参数
电梯状态、当前楼层、目标楼层、电梯所有按钮状态
修改记录：
***********************************************************/
#include <stdio.h>
#include <windows.h>
#include "initialize.h"
#include "sharedVariables.h"

extern int currentFloor;
extern int nextFloor;
extern int moveDirection;
extern int state;
extern int buttonUp[10];
extern int buttonDown[10];
extern int buttonNumber[10];
extern int Profile;//电梯控制策略 默认为策略A(顺便服务策略)
extern double totalTime[5];
extern double eachNumber[5];
extern double averageTime[5];
extern double restTime;
extern int ignore;
/***********************************************************
	函数名称： buttonstation()
	函数功能： 判断所有按钮目前的状态并输出状态
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void buttonstation(void)
{
    int i;
    printf("按钮状态\n");

    //listPrint();
    for (i = 1; i <= 9; i++)
    {

        printf("	第%d层", i);

        if (buttonUp[i] == 1)
        {
            printf("向上灯  亮  ", i);
        }
        else
        {
            printf("向上灯灭    ", i);
        }

        if (buttonDown[i] == 1)
        {
            printf("向下灯  亮  ", i);
        }
        else
        {
            printf("向下灯灭    ", i);
        }

        if (buttonNumber[i] == 1)
        {
            printf("内部灯  亮  ", i);
        }
        else
        {
            printf("内部灯灭    ", i);
        }

        printf("\n");
    }
}

/***********************************************************
	函数名称：print_message()
	函数功能： 输出电梯的所有参数并提示用户输入格式
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void print_message(void)
{
    int i;

    initialize();


    while(1)
    {

        Sleep(700);
        system("cls");

        printf("电梯状态");

        switch(Profile)
        {
            case
                    A:
                printf("（电梯使用策略为A）:\n");
                break;

            case
                    B:
                printf("（电梯使用策略为B）:\n");
                break;

            case
                    C:
                printf("（电梯使用策略为C）:\n");
                break;

            case
                    D:
                printf("（电梯使用策略为D）:\n");
                break;
        }




        if (state == IDLE)


        {
            printf("	电梯空闲\n	门关闭\n");
        }

        if (state == RUN)
        {
            if (nextFloor < 0)
            {
                printf("	电梯长时间无人使用，正在回到1层\n	门关闭\n");
            }

            if(moveDirection == UP && nextFloor >= 0)
            {
                printf("	电梯正在向上运动\n	门关闭\n");
            }

            if(moveDirection == DOWN && nextFloor >= 0)

            {
                printf("	电梯正在向下运动\n	门关闭\n");
            }
        }
        else
        {
            if (state == STOP)
            {
                printf("	电梯停靠···     停靠时间剩余：%.2f秒\n	门打开\n", restTime);
            }
        }

        printf("	电梯正在第%d层\n", currentFloor);

        if ((nextFloor != 0) && (nextFloor != currentFloor) && (nextFloor > 0))
        {
            printf("	电梯运行目标为第%d层\n", nextFloor);
        }
        else
        {
            printf("\n");
        }


        buttonstation();
        printf("\n");
        printf("统计数据（平均每个响应的耗时）:\n");

        for (i = A; i <= D; i++)
        {
            switch(i)
            {
                case
                        A:
                    printf("	A策略:");
                    break;

                case
                        B:
                    printf("B策略:");
                    break;

                case
                        C:
                    printf("C策略:");
                    break;

                case
                        D:
                    printf("D策略:");
                    break;
            }

            if (eachNumber[i] > 0.5)
            {




                printf("%5.2f秒   ", totalTime[i] / eachNumber[i]);
            }
            else
            {
                printf("统计中    ");
            }

        }

        printf("\n");


        printf("\n请从键盘输入请求来控制电梯运行：(输入后无需回车)    键盘输入G代表Go按钮\n");
        printf("键盘输入q w e r t y u i分别代表第1 2 3 4 5 6 7 8层有向上呼叫\n");
        printf("键盘输入a s d f g h j k分别代表第2 3 4 5 6 7 8 9层有向下呼叫\n");
        printf("键盘输入1 2 3 4 5 6 7 8 9分别代表电梯内部有第1 2 3 4 5 6 7 8 9层呼叫\n");
        printf("键盘输入A B C D代表在A B C D策略间切换\n");
    }


}
