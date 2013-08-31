/***********************************************************
	文件名称： 电梯主函数
	作 者： 黄昱恺
	版 本： 2.1
	说 明： 采用顺便服务策略，可在无图形界面下可较直观的观察电梯运行状态，
			时间原因未加上最后2个策略，已预留升级接口。经多次测试已修复所有已知bug。
	修改记录:1、增加输出函数为独立线程         修改人: 黄昱恺
			 2、去除时间控制函数 改为Sleep控制 修改人: 黄昱恺
			 3、添加时间控制 去除Sleep         修改人: 黄昱恺
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <winbase.h>
#include "egg.h"
#include "getInput.h"
#include "control.h"
#include "state_trans.h"
#include "print_message.h"
#include "sharedVariables.h"
#include "initialize.h"
#include "IO.h"

int buttonUp[10] = {0}; //电梯向上按钮
int buttonDown[10] = {0}; //电梯向下按钮
int buttonNumber[10] = {0}; //电梯内部按钮
int currentFloor = 1; //当前楼层 默认电梯在1楼
int nextFloor = 0; //电梯运行目标楼层 为0表示无呼叫需要响应
int state = IDLE; //电梯运行状态(空闲、停靠或运行) 默认为空闲
int moveDirection = STOP; //电梯运行方向(向上、向下或停止) 默认为停止
int Profile = A; //电梯控制策略 默认为策略A(顺便服务策略)
int previousProfile;//切换策略时的前一个策略
int profileChange = 0; //电梯策略更改标记
int velocity = 5; //电梯运行速度
int stopTime = 5; //电梯停靠时间
int waitTime = 10;//空闲等待时间
int blockedFloor = 5;//屏蔽响应的楼层
double totalTime[7] = {0};//统计总共时间
double eachNumber[7] = {0};//统计响应次数
double averageTime[7] = {0};//统计平均时间
int Go = 0;//Go按钮
double restTime = 0;//统计停靠剩余时间
HEGG background, elevator, button, head, string, initial; //egg中的图层
int startexit = 0;//图形界面关闭标识变量
int openbutton = 0;//电梯关门时按下开门键的标识变量
//链表时使用
char listUp[10] = {0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 0};
char listDown[10] = {0, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k'};
char listNumber[10] = {0, '1', '2', '3', '4', '5', '6', '7', '8', '9'};
HANDLE hMutex;//互斥对象

main()
{
    //创建负责读取输入的线程
    DWORD ThreadID = 1, ThreadID1 = 2;
    HANDLE hRead, hRead1;

    initialize();//初始化数据

    hMutex = CreateMutex(NULL, FALSE, NULL);//创建互斥对象

    //建立两个线程
    hRead = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)getInput, NULL, 0, &ThreadID);//接受键盘输入
    hRead1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)IO, NULL, 0, &ThreadID1);//接受屏幕输入和dos输出

    while (1)//不断重复判断电梯运行情况
    {

        state_trans(); //根据自动机模型和control()计算出的电梯目标楼层和运行方向决定此刻电梯的状态
        control();   //根据当前策略决定此刻电梯目标楼层和运行方向

        if (startexit == 1)//检测到图形界面关闭 return退出
        {
            return 0;
        }
    }
}

