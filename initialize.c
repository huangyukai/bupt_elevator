/***********************************************************
	文件名称： 电梯初始化
	作 者： 黄昱恺
	版 本： 4.0
	说 明： 初始化电梯参数和版权声明
	修改记录:增加计时 修改人:黄昱恺
***********************************************************/
#include<stdio.h>
#include<windows.h>
#include <stdlib.h>
#include "sharedVariables.h"

extern int velocity;
extern int stopTime;
extern int waitTime;
extern int initialization;
extern int Profile;//电梯控制策略 默认为策略A(顺便服务策略)
extern int blockedFloor;
extern int previousProfile;
int ok = 0;//判断输入是否出错
/***********************************************************
	函数名称： initialize()
	函数功能： 初始化电梯参数和版权声明
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void initialize(void)
{
    int i;
    char temp;
    printf("\t                                                \\\\\\|///\n");
    printf("\t                                              \\\\\  - -  //\n");
    printf("\t                                               (  @ @  )\n");
    printf("\t┏━━━━━━━━━━━━━━━━━━━━━━oOOo-(_)-oOOo━┓\n");
    printf("\t┃                        电梯系统                           ┃\n");
    printf("\t┃                  组长：黄昱恺                             ┃\n");
    printf("\t┃                  组员：胡梓庭、李宏凯                     ┃\n");
    printf("\t┃                  版权所有、翻版必究                Oooo   ┃\n");
    printf("\t┗━━━━━━━━━━━━━━━━━━━━━━ oooO━-(   )━┛\n");
    printf("\t                                               (   )   ) /\n");
    printf("\t                                                \\ (   (_/\n");
    printf("\t                                                 \\_)\n");


    //电梯初始参数设置
    printf("\n\t电梯初始参数设置：\n\n");
    printf("\t    请输入电梯每运行一层需要的时间（单位秒），建议输入5:  ");
    scanf("%d", &velocity);

    for (; velocity <= 0;)
    {
        printf("\t    时间为正值、请重新输入：");
        scanf("%d", &velocity);
    }

    printf("\t    请输入电梯停靠时间（单位秒），建议输入5:  ");
    scanf("%d", &stopTime);

    for (; stopTime <= 0;)
    {
        printf("\t    时间为正值、请重新输入：");
        scanf("%d", &stopTime);
    }

    printf("\t    请输入电梯初始策略（A、B、C或D）:  ");

    //判断输入数据是否合法
    for (; ok == 0;)
    {

        fflush(stdin);
        scanf("%c", &temp);

        switch(temp)
        {
            case 'A'
                    :
                Profile = A;
                previousProfile = Profile;
                ok = 1;
                break;

            case 'B'
                    :
                Profile = B;
                previousProfile = Profile;
                ok = 1;
                break;

            case 'C'
                    :
                Profile = C;
                previousProfile = Profile;
                ok = 1;
                break;

            case 'D'
                    :
                Profile = D;
                previousProfile = Profile;
                ok = 1;
                break;

            default
                    :
                printf("\t    输入错误，请重新输入：");
        }


    }
	fflush(stdin);
    if (Profile == C)
    {
        printf("\t    请输入电梯空闲多久后回到一层（单位秒），建议输入10:  ");
        scanf("%d", &waitTime);

        for (; waitTime <= 0;)
        {
            printf("\t    时间为正值、请重新输入：");
            scanf("%d", &waitTime);
        }
    }

    if (Profile == D)
    {
        printf("\t    请输入屏蔽电梯二层到第几层的请求（单位秒），建议输入5:  ");
        scanf("%d", &blockedFloor);

        for (; blockedFloor <= 1 || blockedFloor > 9;)
        {
            printf("\t    楼层输入不符合、请重新输入：");
            scanf("%d", &blockedFloor);
        }

    }



    //输入初始数据后,进入电梯界面
    for (i = 1; i <= 2; i++)
    {
        printf("\n");
    }

    printf("\t电梯系统正在初始化");

    for (i = 1; i <= 2; i++)
    {
        printf("\n");
    }

    for (i = 1; i <= 14; i++)
    {
        printf(" ");
    }

    for (i = 1; i <= 50; i++)
    {
        printf("\|");
        Sleep(10);
    }

    initialization = 0;//初始化完毕
}