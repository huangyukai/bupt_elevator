/***********************************************************
	文件名称： 电梯的状态控制
	作 者： 黄昱恺
	版 本： 3.0
	说 明： 根据自动机模型和control()计算出的电梯目标楼层和运行方向决定此刻电梯的状态
	修改记录： 1、修复到9层后不运行的bug            修改人：黄昱恺
			   2、修复电梯停靠后由于Sleep造成的错误 修改人：黄昱恺
			   3、全面去除Sleep                     修改人：黄昱恺
***********************************************************/



#include <windows.h>
#include <time.h>
#include "list.h"

#include "control.h"
#include "sharedVariables.h"

extern int buttonUp[10];
extern int buttonDown[10];
extern int buttonNumber[10];
extern int currentFloor;
extern int nextFloor;
extern int moveDirection;
extern int state;
extern int velocity;
extern int stopTime;
extern int Profile;
extern int profileChange;
extern int previousProfile;
extern double totalTime[5];
extern double eachNumber[5];
extern int Go;
extern double restTime;
extern int ignore;
extern LISTNODEPTR headPtr;
extern LISTNODEPTR lastPtr;
extern LISTNODEPTR currentPtr;
extern LISTNODEPTR tempPtr;
extern char listUp[10];
extern char listDown[10];
extern char listNumber[10];
extern int waitTime;
int startIDLE = 1;
int startRun = 1;
int startRUN = 1;
int startSTOP = 1;
double a, b, c;
double as, bs, cs;
double ar, br, cr;
double staticStart, staticStop;

/***********************************************************
	函数名称： state_trans()
	函数功能： 控制电梯的状态
	入口参数： 无
	出口参数： 无
	备 注： 使用到的全局变量
			buttonUp,buttonDown,buttonNumber,currentFloor,state,nextFloor,moveDirection
			其中nextFloor，moveDirection为只读 不可修改
			使用自动机模型 电梯运行速度2秒每层 电梯停靠时间为4秒
***********************************************************/
void state_trans()
{
    switch (state) /*根据状态和事件，进行相应的处理*/
    {
        case
                IDLE: //电梯空闲状态

            if (moveDirection != STOP) //由control函数发现有不同层响应呼叫 电梯进入运行状态
            {
                state = RUN;
                startIDLE = 1;
            }
            else
                if (currentFloor == nextFloor) //由control函数发现有同层响应呼叫 电梯进入停靠状态
                {
                    state = STOP;
                    startIDLE = 1;
                }
                else
                {
                    if (Profile == C)
                    {
                        if (startIDLE == 1)
                        {
                            a = clock();
                            startIDLE = 0;
                        }
                        else
                        {
                            b = clock();
                            c = (double) (b - a) / CLOCKS_PER_SEC;

                            if (c > waitTime) //等待waitTime秒
                            {
                                if (currentFloor != 1)
                                {
                                    nextFloor = -1;
                                    moveDirection = DOWN;
                                    state = RUN;
                                    startIDLE = 1;
                                }

                            }
                        }
                    }

                }

            break;

        case
                RUN://电梯运行状态
            if (currentFloor == ignore)//安全运行结束
            {
                ignore = 0;
            }

            if (nextFloor < 0)
            {

                if (currentFloor != 1) //未到目标楼层
                {

                    if (startRUN == 1)
                    {
                        ar = clock();
                        startRUN = 0;
                    }
                    else
                    {
                        br = clock();
                        cr = (double) (br - ar) / CLOCKS_PER_SEC;

                        if (cr > velocity)//时间到velocity秒
                        {
                            currentFloor--;
                            startRUN = 1;
                        }

                    }

                }

                if (currentFloor == 1) //电梯到达目标楼层
                {
                    nextFloor = 0;
                    state = IDLE;
                    moveDirection = STOP;
                }

            }
            else
            {

                if (startRun == 1)
                {
                    staticStart = clock();
                    startRun = 0;
                }

                if (currentFloor != nextFloor) //未到目标楼层
                {
                    if (startRUN == 1)
                    {
                        ar = clock();
                        startRUN = 0;
                    }
                    else
                    {
                        br = clock();
                        cr = (double) (br - ar) / CLOCKS_PER_SEC;

                        if (cr > velocity)
                        {
                            currentFloor += moveDirection;
                            startRUN = 1;
                        }
                    }
                }

                if (currentFloor == nextFloor) //电梯到达目标楼层
                {
                    if (moveDirection == UP) //关闭相应的按钮 电梯进入停靠状态
                    {
                        if (Profile == B)//B策略单独处理
                        {
                            if (headPtr != NULL)
                            {

                                closeButton();
                                eachNumber[previousProfile]++;
                                deleteNode(headPtr->data);

                            }
                        }

                        else
                        {

                            if((buttonUp[currentFloor] == 0) && (buttonNumber[currentFloor] == 0))
                            {
                                buttonDown[currentFloor] = 0;
                                deleteNode(listDown[currentFloor]);
                                eachNumber[previousProfile]++;
                            }
                            else
                            {

                                buttonUp[currentFloor] = 0;
                                buttonNumber[currentFloor] = 0;

                                if (headPtr != NULL)
                                {
                                    eachNumber[previousProfile]++;
                                    deleteNode(listUp[currentFloor]);
                                    deleteNode(listNumber[currentFloor]);
                                }


                            }
                        }

                        state = STOP;
                        startRun = 1;
                        staticStop = clock();
                        totalTime[previousProfile] += (double) (staticStop - staticStart) / CLOCKS_PER_SEC;//统计时间

                    }

                    if (moveDirection == DOWN) //关闭相应的按钮 电梯进入停靠状态

                    {
                        if (Profile == B)//B策略需单独处理
                        {
                            if (headPtr != NULL)
                            {
                                closeButton();
                                deleteNode(headPtr->data);
                                eachNumber[previousProfile]++;
                            }
                        }
                        else
                        {
                            if ((buttonDown[currentFloor] == 0) && (buttonNumber[currentFloor] == 0))
                            {
                                buttonUp[currentFloor] = 0;
                                deleteNode(listUp[currentFloor]);
                                eachNumber[previousProfile]++;
                            }
                            else
                            {

                                buttonDown[currentFloor] = 0;
                                buttonNumber[currentFloor] = 0;

                                if (headPtr != NULL)
                                {
                                    eachNumber[previousProfile]++;
                                    deleteNode(listDown[currentFloor]);
                                    deleteNode(listNumber[currentFloor]);
                                }
                            }
                        }

                        state = STOP;//进入停靠
                        startRun = 1;
                        staticStop = clock();

                        totalTime[previousProfile] += (double) (staticStop - staticStart) / CLOCKS_PER_SEC;//统计时间

                    }

                    if (moveDirection == STOP) //如果电梯无运行方向 电梯进入停靠状态
                    {
                        state = STOP;
                        startRun = 1;
                        staticStop = clock();

                        totalTime[previousProfile] += (double) (staticStop - staticStart) / CLOCKS_PER_SEC;//统计时间
                    }
                }

            }

            break;

        case
                STOP: //电梯停靠状态

            control();//重新判断一次目标楼层和运行方向

            if (startSTOP == 1)
            {
                as = clock();
                startSTOP = 0;
                Go = 0;
            }
            else
            {

                bs = clock();
                cs = (double) (bs - as) / CLOCKS_PER_SEC;
                restTime = stopTime - cs;

                if (cs > stopTime || Go == 1)//Go指令判断
                {
                    startSTOP = 1;
                    Go = 0;
                }
            }

            if (startSTOP == 1)
            {

                if (nextFloor == 0) //如果无目标楼层 电梯进入空闲状态
                {
                    moveDirection = STOP;
                    state = IDLE;
                }
                else//有目标楼层则电梯进入运行状态
                {
                    state = RUN;
                }

            }

            break;
    }//end of switch
}

