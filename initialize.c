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
#include "egg.h"
#include "graphical_interface.h"

extern int velocity;
extern int stopTime;
extern int waitTime;
extern int Profile;
extern int blockedFloor;
extern int previousProfile;

int ok = 0;//判断输入是否出错
char ShowConsole;
extern HEGG background, elevator, button;

/***********************************************************
	函数名称： initialize()
	函数功能： 初始化电梯参数和版权声明
	入口参数： 无
	出口参数： 无
	备 注：
***********************************************************/
void initialize(void)
{
    //定义变量
    int i;
    char temp;
    DWORD ThreadID3 = 3;
    HANDLE hRead2;

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

    //判断输入数据是否合法
    for (; velocity <= 0;)
    {
        printf("\t    时间为正值、请重新输入：");
        scanf("%d", &velocity);
    }

    printf("\t    请输入电梯停靠时间（单位秒），建议输入5:  ");
    scanf("%d", &stopTime);

    //判断输入数据是否合法
    for (; stopTime <= 0;)
    {
        printf("\t    时间为正值、请重新输入：");
        scanf("%d", &stopTime);
    }

    printf("\t    请选择电梯初始策略\n\t        A:顺便服务策略\n\t        B:先来先服务策略\n\t        C:一般电梯策略\n\t        D:宏福电梯策略\n\t        E:最快响应策略\n\t        F:最短平均等待时间策略\n\t    请输入策略类型：");

    //判断输入数据是否合法
    for (; ok == 0;)
    {
        fflush(stdin);
        scanf("%c", &temp);

        //选择策略
        switch(temp)
        {
            case 'A'
                    :
                Profile = A;
                previousProfile = Profile;//前一策略的参数初始化
                ok = 1;//输入数据符合格式要求
                break;

            case 'B'
                    :
                Profile = B;
                previousProfile = Profile;//前一策略的参数初始化
                ok = 1;//输入数据符合格式要求
                break;

            case 'C'
                    :
                Profile = C;
                previousProfile = Profile;//前一策略的参数初始化
                ok = 1;//输入数据符合格式要求
                break;

            case 'D'
                    :
                Profile = D;
                previousProfile = Profile;//前一策略的参数初始化
                ok = 1;//输入数据符合格式要求
                break;

            case 'E'
                    :

                Profile = E;
                previousProfile = Profile;//前一策略的参数初始化
                ok = 1;//输入数据符合格式要求
                break;

            case 'F'
                    :

                Profile = F;
                previousProfile = Profile;//前一策略的参数初始化
                ok = 1;//输入数据符合格式要求
                break;

            default
                    :
                printf("\t    输入错误，请重新输入：");
        }


    }

    //策略为C、D时单独初始化数据
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

    //提示是否隐藏DOS窗口
    printf("\t    是否显示DOS控制台\n\t    （显示输入Y，隐藏输入N，可在图形界面按右键随时调出），建议输入N:  ");
    fflush(stdin);
    scanf("%c", &ShowConsole);
    fflush(stdin);

    //判断输入数据是否合法
    for (; ShowConsole != 'N' && ShowConsole != 'Y';)
    {
        printf("\t    输入错误，请重新输入：");
        fflush(stdin);
        scanf("%c", &ShowConsole);
    }

    //系统环境的提示
    MessageBox(NULL, TEXT("  本电梯系统图形界面分辨率为1024*768\n  如果系统分辨率过低可能导致电梯界面显示不完全\n  如果电梯下部分显示不完全，建议隐藏系统任务栏后使用"), TEXT("使用环境注意"), MB_ICONINFORMATION);

    if (ShowConsole == 'N')
    {
        EggStart(1024, 768);
        ShowConsoleWindow(0);//隐藏DOS窗口
    }
    else
    {
        EggStart(1024, 768);
    }


    //开始初始化,首先获得背景的句柄
    background = GetActiveEgg();
    //图形界面初始化新建一个线程
    hRead2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initializeanimation, NULL, 0, &ThreadID3);

    //输入初始数据后,进入电梯界面
    for (i = 1; i <= 2; i++)
    {
        printf("\n");
    }

    //DOS界面初始化
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
        Sleep(45);
    }


}