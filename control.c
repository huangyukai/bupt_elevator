/***********************************************************
文件名称： 策略控制
作 者： 黄昱恺
版 本： 7.02
说 明： 用不同的策略控制电梯
修改记录：增加BCD策略     修改人：黄昱恺
修正顺便服务bug 修改人：黄昱恺
修改安全响应bug 修改人：黄昱恺
增加统计        修改人：黄昱恺
***********************************************************/
#include "list.h"
#include <stdlib.h>
#include "sharedVariables.h"
#include "graphical_interface.h"
//全局变量调用
extern int buttonUp[10];
extern int buttonDown[10];
extern int buttonNumber[10];
extern int currentFloor;
extern int nextFloor;
extern int moveDirection;
extern int Profile;
extern int profileChange;
extern int previousProfile;
extern int state;
extern char listUp[10];
extern char listDown[10];
extern char listNumber[10];
extern double eachNumber[7];
extern int ignore;
extern LISTNODEPTR headPtr;
extern LISTNODEPTR lastPtr;
extern LISTNODEPTR currentPtr;
extern LISTNODEPTR tempPtr;
extern int velocity;
extern int stopTime;
extern int waitTime;
int profileCfindnextfloor = 0;//C策略中如果在回到一层时发现响应时图形界面的处理
int profileEFfindnextfloor = 0;
/***********************************************************
函数名称： control()
函数功能： 根据策略 决定电梯运行的目标楼层和电梯运行方向
入口参数： 无
出口参数： 无
备 注：    只可修改nextFloor和moveDirection
***********************************************************/
void control()
{
    int i;//循环变量

    switch(Profile)//策略切换
    {
        case
                A://A策略
            if (profileChange == 1) //变化策略时的过度
            {
                if (currentFloor == nextFloor || nextFloor == 0)
                {
                    profileChange = 0; //完成策略切换的过度
                    previousProfile = Profile;
                }
            }
            else//策略A控制
            {
                switch (moveDirection)//根据电梯运行方向判断目标楼层和下一步的运行方向
                {
                    case
                            STOP://电梯无运行方向
                        nextFloor = 0; //默认无目标楼层 接下来开始搜索目标楼层

                        //如果有同层响应
                        if(buttonUp[currentFloor] == 1)
                        {
                            moveDirection = UP;
                            buttonUp[currentFloor] = 0;
                            lightOff(listUp[currentFloor]);//关闭图形界面的按钮
                            eachNumber[previousProfile]++;//统计响应次数
                            if (headPtr != NULL)//B策略删除链表
                            {
                                deleteNode(listUp[currentFloor]);
                            }

                            nextFloor = currentFloor;
                        }
                        else
                            if (buttonDown[currentFloor] == 1)
                            {
                                moveDirection = DOWN;
                                buttonDown[currentFloor] = 0;
                                lightOff(listDown[currentFloor]);//关闭图形界面的按钮
                                eachNumber[previousProfile]++;//统计响应次数

                                if (headPtr != NULL)//B策略删除链表
                                {
                                    deleteNode(listDown[currentFloor]);
                                }

                                nextFloor = currentFloor;
                            }
                            else
                                if (buttonNumber[currentFloor] == 1)
                                {
                                    nextFloor = currentFloor;
                                    buttonNumber[currentFloor] = 0;
                                    lightOff(listNumber[currentFloor]);//关闭图形界面的按钮

                                    eachNumber[previousProfile]++;//统计响应次数

                                    if (headPtr != NULL)//B策略删除链表
                                    {
                                        deleteNode(listNumber[currentFloor]);
                                    }
                                }
                                else

                                    //无同层相应 则从本层为中心 向上向下搜索响应
                                    for(i = 1; i <= 9; i++)
                                    {
                                        //向下搜索
                                        if ((currentFloor - i) > 0 && (currentFloor - i) <= 9) //判断欲搜索的楼层是否在1-9层
                                        {
                                            if(buttonUp[currentFloor - i] == 1 || buttonDown[currentFloor - i] == 1 || buttonNumber[currentFloor - i] == 1)
                                            {
                                                nextFloor = currentFloor - i;
                                                moveDirection = DOWN;
                                                break;
                                            }
                                        }

                                        //向上搜索
                                        if ((currentFloor + i) > 0 && (currentFloor + i) <= 9) //判断欲搜索的楼层是否在1-9层
                                        {
                                            if(buttonUp[currentFloor + i] == 1 || buttonDown[currentFloor + i] == 1 || buttonNumber[currentFloor + i] == 1)
                                            {
                                                nextFloor = currentFloor + i;
                                                moveDirection = UP;
                                                break;
                                            }
                                        }

                                    }//end of for
                        break;

                    case
                            UP://电梯运行方向向上

                        if (currentFloor == 9) //如果到达顶层 电梯为无运动方向
                        {
                            moveDirection = STOP;
                        }
                        else
                        {
                            int find = 0, temp = 0;

                            if (ignore != 0)//安全运行的判断 不响应临近楼层
                            {
                                temp = 1;
                            }

                            for(i = currentFloor + 1 + temp; i <= 9; i++)//先检查有无导致方向向上的请求
                            {
                                if(buttonUp[i] == 1 || buttonNumber[i] == 1)
                                {
                                    nextFloor = i;
                                    moveDirection = UP;
                                    find = 1;
                                    break;
                                }
                            }

                            temp = 0;

                            if (find != 1)
                            {
                                for (i = 9; i >= currentFloor + 1; i--)//再检查有无导致方向向下的请求
                                {
                                    if (buttonDown[i] == 1)
                                    {
                                        nextFloor = i;
                                        moveDirection = UP;
                                        find = 1;
                                        break;
                                    }
                                }

                                if (find != 1)
                                {
                                    moveDirection = STOP;
                                }
                                else
                                {
                                    find = 0;
                                }

                            }
                            else
                            {
                                find = 0;
                            }

                        }

                        break;

                    case
                            DOWN://电梯运行方向向下
                        if (currentFloor == 1)//如果到达一层,电梯运行方向无
                        {
                            moveDirection = STOP;
                        }

                        else
                        {
                            int find = 0, temp = 0;

                            if (ignore != 0)//安全响应的判断
                            {
                                temp = 1;
                            }

                            for(i = currentFloor - 1 - temp; i >= 1; i--)//检查会引起方向向下的请求
                            {
                                if( buttonDown[i] == 1 || buttonNumber[i] == 1)
                                {
                                    nextFloor = i;
                                    moveDirection = DOWN;
                                    find = 1;
                                    break;
                                }


                            }//end of for

                            temp = 0;

                            if (find != 1)
                            {
                                for (i = 1; i <= currentFloor - 1; i++)//再检查会导致方向向上的请求
                                {
                                    if (buttonUp[i] == 1)
                                    {
                                        nextFloor = i;
                                        moveDirection = DOWN;
                                        find = 1;
                                        break;
                                    }
                                }

                                if (find != 1)
                                {
                                    moveDirection = STOP;
                                }
                                else
                                {
                                    find = 0;
                                }

                            }
                            else
                            {
                                find = 0;
                            }


                        }

                        break;
                }
            }

            break;

        case
                B://策略B

            if (profileChange == 1)//策略变化时的过度
            {
                if (currentFloor == nextFloor || nextFloor == 0)
                {
                    profileChange = 0;
                    previousProfile = Profile;
                }
            }
            else
            {
                if (headPtr != NULL)
                {
                    if (checkFloor(headPtr->data) == currentFloor)
                    {
                        //如果有同层响应
                        if(buttonUp[currentFloor] == 1)
                        {
                            moveDirection = UP;
                            if (headPtr != NULL)
                            {
                                closeButton();//关闭电梯按钮
                                eachNumber[previousProfile]++;//统计次数
                                deleteNode(listUp[currentFloor]);
                                lightOff(listUp[currentFloor]);
                            }

                            nextFloor = currentFloor;
                        }
                        else
                            if (buttonDown[currentFloor] == 1)
                            {
                                moveDirection = DOWN;

                                if (headPtr != NULL)
                                {
                                    closeButton();
                                    eachNumber[previousProfile]++;
                                    deleteNode(listDown[currentFloor]);
                                    lightOff(listDown[currentFloor]);
                                }

                                nextFloor = currentFloor;
                            }
                            else
                                if (buttonNumber[currentFloor] == 1)
                                {
                                    if (headPtr != NULL)
                                    {
                                        closeButton();
                                        eachNumber[previousProfile]++;
                                        deleteNode(listNumber[currentFloor]);
                                        lightOff(listNumber[currentFloor]);
                                    }

                                    nextFloor = currentFloor;
                                }
                    }
                    else
                    {
                        switch(headPtr->data)//根据链表中的数据决定电梯运行方向
                        {
                            case 'q'
                                    :
                                nextFloor = 1;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case 'w'
                                    :
                                nextFloor = 2;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case 'e'
                                    :
                                nextFloor = 3;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case 'r'
                                    :
                                nextFloor = 4;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case 't'
                                    :
                                nextFloor = 5;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case 'y'
                                    :
                                nextFloor = 6;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case 'u'
                                    :
                                nextFloor = 7;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case 'i'
                                    :
                                nextFloor = 8;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case 'a'
                                    :
                                nextFloor = 2;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }
                                break;

                            case 's'
                                    :
                                nextFloor = 3;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }
                                break;

                            case 'd'
                                    :
                                nextFloor = 4;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }
                                break;

                            case 'f'
                                    :
                                nextFloor = 5;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }
                                break;

                            case 'g'
                                    :
                                nextFloor = 6;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }
                                break;

                            case 'h'
                                    :
                                nextFloor = 7;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }
                                break;

                            case 'j'
                                    :
                                nextFloor = 8;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }
                                break;

                            case 'k'
                                    :
                                nextFloor = 9;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }
                                break;

                            case '1'
                                    :
                                nextFloor = 1;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case '2'
                                    :
                                nextFloor = 2;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case '3'
                                    :
                                nextFloor = 3;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case '4'
                                    :
                                nextFloor = 4;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case '5'
                                    :
                                nextFloor = 5;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case '6'
                                    :
                                nextFloor = 6;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case '7'
                                    :
                                nextFloor = 7;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case '8'
                                    :
                                nextFloor = 8;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            case '9'
                                    :
                                nextFloor = 9;

                                if (currentFloor < nextFloor)
                                {
                                    moveDirection = UP;
                                }
                                else
                                {
                                    if (currentFloor > nextFloor)
                                    {
                                        moveDirection = DOWN;
                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }

                                break;

                            default
                                    :
                                nextFloor = 0;
                                break;
                        }//end of switch
                    }

                }
                else
                {
                    nextFloor = 0;
                }
            }

            break;

        case
                C:
            if (profileChange == 1) //变化策略时的过度
            {
                if (currentFloor == nextFloor || nextFloor == 0)
                {
                    profileChange = 0; //完成策略切换的过度
                    previousProfile = Profile;
                }
            }
            else
            {
                switch (moveDirection)//根据电梯运行方向判断目标楼层和下一步的运行方向
                {
                    case
                            STOP://电梯无运行方向
                        if (nextFloor != -1)
                        {
                            nextFloor = 0; //默认无目标楼层 接下来开始搜索目标楼层
                        }
                        //如果有同层响应
                        if(buttonUp[currentFloor] == 1)
                        {
                            moveDirection = UP;
                            buttonUp[currentFloor] = 0;
                            lightOff(listUp[currentFloor]);
                            eachNumber[previousProfile]++;

                            if (headPtr != NULL)
                            {
                                deleteNode(listUp[currentFloor]);

                            }
                            nextFloor = currentFloor;
                        }
                        else
                            if (buttonDown[currentFloor] == 1)
                            {
                                moveDirection = DOWN;
                                buttonDown[currentFloor] = 0;
                                lightOff(listDown[currentFloor]);
                                eachNumber[previousProfile]++;

                                if (headPtr != NULL)
                                {
                                    deleteNode(listDown[currentFloor]);
                                }

                                nextFloor = currentFloor;
                            }
                            else
                                if (buttonNumber[currentFloor] == 1)
                                {
                                    nextFloor = currentFloor;
                                    buttonNumber[currentFloor] = 0;
                                    lightOff(listNumber[currentFloor]);
                                    eachNumber[previousProfile]++;

                                    if (headPtr != NULL)
                                    {
                                        deleteNode(listNumber[currentFloor]);
                                    }
                                }
                                else
                                    //无同层相应 则从本层为中心 向上向下搜索响应
                                {
                                    for(i = 1; i <= 9; i++)
                                    {
                                        //向下搜索
                                        if ((currentFloor - i) > 0 && (currentFloor - i) <= 9) //判断欲搜索的楼层是否在1-9层
                                        {
                                            if(buttonUp[currentFloor - i] == 1 || buttonDown[currentFloor - i] == 1 || buttonNumber[currentFloor - i] == 1)
                                            {
                                                nextFloor = currentFloor - i;
                                                moveDirection = DOWN;
                                                break;
                                            }
                                        }

                                        //向上搜索
                                        if ((currentFloor + i) > 0 && (currentFloor + i) <= 9) //判断欲搜索的楼层是否在1-9层
                                        {
                                            if(buttonUp[currentFloor + i] == 1 || buttonDown[currentFloor + i] == 1 || buttonNumber[currentFloor + i] == 1)
                                            {
                                                nextFloor = currentFloor + i;
                                                moveDirection = UP;
                                                break;
                                            }
                                        }

                                    }//end of for
                                }

                        break;

                    case
                            UP://电梯运行方向向上

                        if (currentFloor == 9) //如果到达顶层 电梯为无运动方向
                        {
                            int i;

                            for (i = 1; i <= 9; i++)
                            {
                                buttonNumber[i] = 0;

                                deleteNode(listNumber[i]);
                                lightOff(listNumber[i]);
                            }

                            moveDirection = STOP;
                        }
                        else
                        {
                            int find = 0;

                            for(i = currentFloor + 1; i <= 9; i++)
                            {
                                if(buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                {
                                    nextFloor = i;
                                    moveDirection = UP;
                                    find = 1;
                                    break;
                                }
                            }

                            if (find != 1)
                            {
                                for (i = 9; i >= currentFloor + 1; i--)
                                {
                                    if (buttonDown[i] == 1)
                                    {
                                        nextFloor = i;
                                        moveDirection = UP;
                                        find = 1;
                                        break;
                                    }
                                }

                                if (find != 1)
                                {
                                    moveDirection = STOP;
                                }
                                else
                                {
                                    find = 0;
                                }

                            }
                            else
                            {
                                find = 0;
                            }
                        }
                        break;

                    case
                            DOWN://电梯运行方向向下
                        if (nextFloor == -1)
                        {
                            int i;

                            for (i = 1; i <= 9; i++)
                            {
                                if (buttonUp[i] == 1 || buttonDown[i] == 1 || buttonNumber[i] == 1)
                                {
                                    nextFloor = i;

                                    if (nextFloor > currentFloor)
                                    {
                                        profileCfindnextfloor = 1;
                                        moveDirection = UP;
                                    }
                                    else
                                    {
                                        if (nextFloor < currentFloor)
                                        {
                                            profileCfindnextfloor = 1;
                                            moveDirection = DOWN;
                                        }
                                        else
                                        {
                                            profileCfindnextfloor = 1;
                                            moveDirection = STOP;
                                        }
                                    }

                                    break;
                                }
                            }
                        }
                        else
                        {
                            if (currentFloor == 1) //如果到达顶层 电梯为无运动方向
                            {
                                int i;

                                for (i = 1; i <= 9; i++)
                                {
                                    buttonNumber[i] = 0;
                                    deleteNode(listNumber[i]);
                                    lightOff(listNumber[i]);
                                }

                                moveDirection = STOP;
                            }
                            else
                            {
                                int find = 0;

                                for(i = currentFloor - 1; i >= 1; i--)
                                {
                                    if(buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                    {
                                        nextFloor = i;
                                        moveDirection = DOWN;
                                        find = 1;
                                        break;
                                    }
                                }

                                if (find != 1)
                                {
                                    for (i = 1; i <= currentFloor - 1; i++)
                                    {
                                        if (buttonUp[i] == 1)
                                        {
                                            nextFloor = i;
                                            moveDirection = DOWN;
                                            find = 1;
                                            break;
                                        }
                                    }

                                    if (find != 1)
                                    {
                                        moveDirection = STOP;
                                    }
                                    else
                                    {
                                        find = 0;
                                    }
                                }
                                else
                                {
                                    find = 0;
                                }
                            }
                        }
                }
            }

            break;

        case
                D:
            if (profileChange == 1) //变化策略时的过度
            {
                if (currentFloor == nextFloor || nextFloor == 0)
                {
                    profileChange = 0; //完成策略切换的过度
                    previousProfile = Profile;
                }
            }
            else
            {
                switch (moveDirection)//根据电梯运行方向判断目标楼层和下一步的运行方向
                {
                    case
                            STOP://电梯无运行方向
                        nextFloor = 0; //默认无目标楼层 接下来开始搜索目标楼层

                        //如果有同层响应
                        if(buttonUp[currentFloor] == 1)
                        {
                            moveDirection = UP;
                            buttonUp[currentFloor] = 0;
                            lightOff(listUp[currentFloor]);
                            eachNumber[previousProfile]++;

                            if (headPtr != NULL)
                            {
                                deleteNode(listUp[currentFloor]);
                            }

                            nextFloor = currentFloor;
                        }
                        else
                            if (buttonDown[currentFloor] == 1)
                            {
                                moveDirection = DOWN;
                                buttonDown[currentFloor] = 0;
                                lightOff(listDown[currentFloor]);
                                eachNumber[previousProfile]++;

                                if (headPtr != NULL)
                                {

                                    deleteNode(listDown[currentFloor]);
                                }

                                nextFloor = currentFloor;
                            }
                            else
                                if (buttonNumber[currentFloor] == 1)
                                {
                                    nextFloor = currentFloor;
                                    buttonNumber[currentFloor] = 0;
                                    lightOff(listNumber[currentFloor]);
                                    eachNumber[previousProfile]++;

                                    if (headPtr != NULL)
                                    {

                                        deleteNode(listNumber[currentFloor]);
                                    }
                                }
                                else
                                    //无同层相应 则从本层为中心 向上向下搜索响应
                                {
                                    for(i = 1; i <= 9; i++)
                                    {
                                        //向下搜索
                                        if ((currentFloor - i) > 0 && (currentFloor - i) <= 9) //判断欲搜索的楼层是否在1-9层
                                        {
                                            if(buttonUp[currentFloor - i] == 1 || buttonDown[currentFloor - i] == 1 || buttonNumber[currentFloor - i] == 1)
                                            {
                                                nextFloor = currentFloor - i;
                                                moveDirection = DOWN;
                                                break;
                                            }
                                        }

                                        //向上搜索
                                        if ((currentFloor + i) > 0 && (currentFloor + i) <= 9) //判断欲搜索的楼层是否在1-9层
                                        {
                                            if(buttonUp[currentFloor + i] == 1 || buttonDown[currentFloor + i] == 1 || buttonNumber[currentFloor + i] == 1)
                                            {
                                                nextFloor = currentFloor + i;
                                                moveDirection = UP;
                                                break;
                                            }
                                        }

                                    }//end of for
                                }
                        break;

                    case
                            UP://电梯运行方向向上

                        if (currentFloor == 9) //如果到达顶层 电梯为无运动方向
                        {
                            int i;

                            for (i = 1; i <= 9; i++)
                            {
                                buttonNumber[i] = 0;
                                deleteNode(listNumber[i]);
                                lightOff(listNumber[i]);
                            }

                            moveDirection = STOP;
                        }
                        else
                        {
                            int find = 0;

                            for(i = currentFloor + 1; i <= 9; i++)
                            {
                                if(buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                {
                                    nextFloor = i;
                                    moveDirection = UP;
                                    find = 1;
                                    break;
                                }
                            }

                            if (find != 1)
                            {
                                for (i = 9; i >= currentFloor + 1; i--)
                                {
                                    if (buttonDown[i] == 1)
                                    {
                                        nextFloor = i;
                                        moveDirection = UP;
                                        find = 1;
                                        break;
                                    }
                                }

                                if (find != 1)
                                {
                                    moveDirection = STOP;
                                }
                                else
                                {
                                    find = 0;
                                }
                            }
                            else
                            {
                                find = 0;
                            }
                        }
                        break;
                    case
                            DOWN://电梯运行方向向下
                        if (currentFloor == 1) //如果到达顶层 电梯为无运动方向
                        {
                            int i;

                            for (i = 1; i <= 9; i++)
                            {
                                buttonNumber[i] = 0;

                                deleteNode(listNumber[i]);
                                lightOff(listNumber[i]);
                            }

                            moveDirection = STOP;
                        }
                        else
                        {
                            int find = 0;

                            for(i = currentFloor - 1; i >= 1; i--)
                            {
                                if(buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                {
                                    nextFloor = i;
                                    moveDirection = DOWN;
                                    find = 1;
                                    break;
                                }
                            }
                            if (find != 1)
                            {
                                for (i = 1; i <= currentFloor - 1; i++)
                                {
                                    if (buttonUp[i] == 1)
                                    {
                                        nextFloor = i;
                                        moveDirection = DOWN;
                                        find = 1;
                                        break;
                                    }
                                }
                                if (find != 1)
                                {
                                    moveDirection = STOP;
                                }
                                else
                                {
                                    find = 0;
                                }

                            }
                            else
                            {
                                find = 0;
                            }
                        }

                        break;
                }//end of switch
            }

            break;

        case
                E:
            if (profileChange == 1) //变化策略时的过度
            {
                if (currentFloor == nextFloor || nextFloor == 0)
                {
                    profileChange = 0; //完成策略切换的过度
                    previousProfile = Profile;
                }
            }
            else
            {
                switch (moveDirection)//根据电梯运行方向判断目标楼层和下一步的运行方向
                {
                    case
                            STOP://电梯无运行方向
                        if (nextFloor != -1)
                        {
                            nextFloor = 0; //默认无目标楼层 接下来开始搜索目标楼层
                        }

                        //如果有同层响应
                        if(buttonUp[currentFloor] == 1)
                        {
                            if (profileEFfindnextfloor == 0)
                            {
                                moveDirection = UP;
                                buttonUp[currentFloor] = 0;
                                lightOff(listUp[currentFloor]);
                                eachNumber[previousProfile]++;

                                if (headPtr != NULL)
                                {
                                    deleteNode(listUp[currentFloor]);

                                }

                                nextFloor = currentFloor;
                            }
                            else
                            {
                                nextFloor = currentFloor;
                                moveDirection = UP;
                            }
                        }
                        else
                            if (buttonDown[currentFloor] == 1)
                            {
                                if (profileEFfindnextfloor == 0)
                                {

                                    moveDirection = DOWN;
                                    buttonDown[currentFloor] = 0;
                                    lightOff(listDown[currentFloor]);
                                    eachNumber[previousProfile]++;

                                    if (headPtr != NULL)
                                    {
                                        deleteNode(listDown[currentFloor]);
                                    }

                                    nextFloor = currentFloor;
                                }
                                else
                                {
                                    nextFloor = currentFloor;
                                    moveDirection = DOWN;
                                }

                            }
                            else
                                if (buttonNumber[currentFloor] == 1)
                                {
                                    nextFloor = currentFloor;
                                    buttonNumber[currentFloor] = 0;
                                    lightOff(listNumber[currentFloor]);
                                    eachNumber[previousProfile]++;

                                    if (headPtr != NULL)
                                    {
                                        deleteNode(listNumber[currentFloor]);
                                    }
                                }
                                else
                                    //无同层相应 则从本层为中心 向上向下搜索响应
                                {
                                    for(i = 1; i <= 9; i++)
                                    {
                                        //向下搜索
                                        if ((currentFloor - i) > 0 && (currentFloor - i) <= 9) //判断欲搜索的楼层是否在1-9层
                                        {
                                            if(buttonUp[currentFloor - i] == 1 || buttonDown[currentFloor - i] == 1 || buttonNumber[currentFloor - i] == 1)
                                            {
                                                nextFloor = currentFloor - i;
                                                moveDirection = DOWN;
                                                break;
                                            }
                                        }

                                        //向上搜索
                                        if ((currentFloor + i) > 0 && (currentFloor + i) <= 9) //判断欲搜索的楼层是否在1-9层
                                        {
                                            if(buttonUp[currentFloor + i] == 1 || buttonDown[currentFloor + i] == 1 || buttonNumber[currentFloor + i] == 1)
                                            {
                                                nextFloor = currentFloor + i;
                                                moveDirection = UP;
                                                break;
                                            }
                                        }
                                    }//end of for
                                }

                        break;

                    case
                            UP://电梯运行方向向上
                        if (currentFloor == 9) //如果到达顶层 电梯为无运动方向
                        {
                            moveDirection = STOP;
                        }
                        else
                        {
                            int find = 0, i;
                            int nextFloor1, nextFloor2, count = 0, startjudge = 0, uptime = 0, downtime = 0;

                            if (profileEFfindnextfloor == 0)
                            {
                                for (i = 1; i <= currentFloor; i++)
                                {
                                    if (buttonUp[i] == 1 ||  buttonNumber[i] == 1 || buttonDown[i] == 1)
                                    {
                                        startjudge = 1;
                                        break;
                                    }
                                }

                                if (startjudge == 1)
                                {
                                    startjudge = 0;

                                    for (i = currentFloor + 1; i <= 9; i++)
                                    {
                                        count++;

                                        if (buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                        {
                                            uptime += velocity * count;

                                        }
                                    }

                                    for (i = 8; i >= currentFloor + 1; i--)
                                    {
                                        count++;

                                        if (buttonDown[i] == 1)
                                        {
                                            uptime += velocity * count;

                                        }
                                    }

                                    for (i = currentFloor; i >= 1; i--)
                                    {
                                        count++;

                                        if (buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                        {
                                            uptime += velocity * count;

                                        }
                                    }

                                    for (i = 2; i <= currentFloor; i++)
                                    {
                                        count++;

                                        if (buttonUp[i] == 1)
                                        {
                                            uptime += velocity * count;

                                        }
                                    }
                                    count = 0;
                                    for (i = currentFloor; i >= 1; i--)
                                    {
                                        count++;

                                        if (buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                        {
                                            downtime += velocity * count;

                                        }
                                    }

                                    for (i = 2; i <= currentFloor; i++)
                                    {
                                        count++;

                                        if (buttonUp[i] == 1)
                                        {
                                            downtime += velocity * count;

                                        }
                                    }

                                    for (i = currentFloor + 1; i <= 9; i++)
                                    {
                                        count++;

                                        if (buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                        {
                                            downtime += velocity * count;

                                        }
                                    }

                                    for (i = 8; i >= currentFloor + 1; i--)
                                    {
                                        count++;

                                        if (buttonDown[i] == 1)
                                        {
                                            downtime += velocity * count;

                                        }
                                    }

                                    count = 0;

                                    if (uptime * 5 > downtime * 6)
                                    {
                                        moveDirection = DOWN;
                                        profileEFfindnextfloor = 1;
                                        break;
                                    }

                                }

                            }

                            if (buttonNumber[currentFloor] == 1 && profileEFfindnextfloor == 1)
                            {
                                nextFloor = currentFloor;
                            }

                            for(i = currentFloor + 1; i <= 9; i++)
                            {
                                if(buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                {
                                    nextFloor = i;

                                    if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                    {
                                    }
                                    else
                                    {

                                        moveDirection = UP;
                                    }

                                    find = 1;
                                    break;
                                }


                            }

                            if (find != 1)
                            {
                                for (i = 9; i >= currentFloor + 1; i--)
                                {
                                    if (buttonDown[i] == 1)
                                    {
                                        nextFloor = i;

                                        if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                        {

                                        }
                                        else
                                        {
                                            moveDirection = UP;
                                        }

                                        find = 1;
                                        break;
                                    }
                                }

                                if (find != 1)
                                {
                                    if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                    {

                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }
                                else
                                {
                                    find = 0;
                                }



                            }
                            else
                            {
                                find = 0;
                            }
                        }

                        break;

                    case
                            DOWN://电梯运行方向向下

                        {

                            if (currentFloor == 1) //如果到达顶层 电梯为无运动方向
                            {



                                moveDirection = STOP;
                            }
                            else
                            {
                                int find = 0, i;



                                int nextFloor1, nextFloor2, count = 0, startjudge = 0, uptime = 0, downtime = 0;





                                if (profileEFfindnextfloor == 0)
                                {
                                    for (i = currentFloor; i <= 9; i++)
                                    {
                                        if (buttonUp[i] == 1 ||  buttonNumber[i] == 1 || buttonDown[i] == 1)
                                        {
                                            startjudge = 1;
                                            break;
                                        }
                                    }

                                    if (startjudge == 1)
                                    {
                                        startjudge = 0;

                                        for (i = currentFloor - 1; i >= 1; i--)
                                        {
                                            count++;

                                            if (buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                            {
                                                downtime += velocity * count;

                                            }
                                        }

                                        for (i = 2; i <= currentFloor - 1; i++)
                                        {
                                            count++;

                                            if (buttonUp[i] == 1)
                                            {
                                                downtime += velocity * count;

                                            }
                                        }

                                        for (i = currentFloor; i <= 9; i++)
                                        {
                                            count++;

                                            if (buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                            {
                                                downtime += velocity * count;

                                            }
                                        }

                                        for (i = 8; i >= currentFloor; i--)
                                        {
                                            count++;

                                            if (buttonDown[i] == 1)
                                            {
                                                downtime += velocity * count;

                                            }
                                        }



                                        count = 0;


                                        for (i = currentFloor; i <= 9; i++)
                                        {
                                            count++;

                                            if (buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                            {
                                                uptime += velocity * count;

                                            }
                                        }

                                        for (i = 8; i >= currentFloor; i--)
                                        {
                                            count++;

                                            if (buttonDown[i] == 1)
                                            {
                                                uptime += velocity * count;

                                            }
                                        }

                                        for (i = currentFloor - 1; i >= 1; i--)
                                        {
                                            count++;

                                            if (buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                            {
                                                uptime += velocity * count;

                                            }
                                        }

                                        for (i = 2; i <= currentFloor - 1; i++)
                                        {
                                            count++;

                                            if (buttonUp[i] == 1)
                                            {
                                                uptime += velocity * count;

                                            }
                                        }



                                        count = 0;

                                        if (downtime * 5 > uptime * 6)
                                        {
                                            moveDirection = UP;
                                            profileEFfindnextfloor = 1;
                                            break;
                                        }

                                    }

                                }

                                if (buttonNumber[currentFloor] == 1 && profileEFfindnextfloor == 1)
                                {
                                    nextFloor = currentFloor;
                                }


                                for(i = currentFloor - 1; i >= 1; i--)
                                {
                                    if(buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                    {
                                        nextFloor = i;

                                        if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                        {
                                        }
                                        else
                                        {
                                            moveDirection = DOWN;
                                        }

                                        find = 1;

                                        break;
                                    }


                                }


                                if (find != 1)
                                {
                                    for (i = 1; i <= currentFloor - 1; i++)
                                    {
                                        if (buttonUp[i] == 1)
                                        {
                                            nextFloor = i;

                                            if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                            {

                                            }
                                            else
                                            {
                                                moveDirection = DOWN;
                                            }

                                            find = 1;
                                            break;
                                        }
                                    }

                                    if (find != 1)
                                    {
                                        if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                        {

                                        }
                                        else
                                        {
                                            moveDirection = STOP;
                                        }
                                    }
                                    else
                                    {
                                        find = 0;
                                    }



                                }
                                else
                                {
                                    find = 0;
                                }
                            }
                        }
                }
            }

            break;

        case
                F:
            if (profileChange == 1) //变化策略时的过度
            {
                if (currentFloor == nextFloor || nextFloor == 0)
                {
                    profileChange = 0; //完成策略切换的过度
                    previousProfile = Profile;
                }
            }
            else
            {
                switch (moveDirection)//根据电梯运行方向判断目标楼层和下一步的运行方向
                {
                    case
                            STOP://电梯无运行方向
                        if (nextFloor != -1)
                        {

                            nextFloor = 0; //默认无目标楼层 接下来开始搜索目标楼层
                        }

                        //如果有同层响应
                        if(buttonUp[currentFloor] == 1)
                        {
                            if (profileEFfindnextfloor == 0)
                            {
                                moveDirection = UP;
                                buttonUp[currentFloor] = 0;
                                lightOff(listUp[currentFloor]);
                                eachNumber[previousProfile]++;

                                if (headPtr != NULL)
                                {
                                    deleteNode(listUp[currentFloor]);

                                }

                                nextFloor = currentFloor;
                            }
                            else
                            {
                                nextFloor = currentFloor;
                                moveDirection = UP;

                            }
                        }
                        else
                            if (buttonDown[currentFloor] == 1)
                            {
                                if (profileEFfindnextfloor == 0)
                                {
                                    moveDirection = DOWN;
                                    buttonDown[currentFloor] = 0;
                                    lightOff(listDown[currentFloor]);
                                    eachNumber[previousProfile]++;

                                    if (headPtr != NULL)
                                    {

                                        deleteNode(listDown[currentFloor]);
                                    }

                                    nextFloor = currentFloor;
                                }
                                else
                                {
                                    nextFloor = currentFloor;
                                    moveDirection = DOWN;
                                }
                            }
                            else
                                if (buttonNumber[currentFloor] == 1)
                                {
                                    nextFloor = currentFloor;
                                    buttonNumber[currentFloor] = 0;
                                    lightOff(listNumber[currentFloor]);
                                    eachNumber[previousProfile]++;

                                    if (headPtr != NULL)
                                    {

                                        deleteNode(listNumber[currentFloor]);
                                    }
                                }
                                else
                                    //无同层相应 则从本层为中心 向上向下搜索响应
                                {
                                    for(i = 1; i <= 9; i++)
                                    {
                                        //向下搜索
                                        if ((currentFloor - i) > 0 && (currentFloor - i) <= 9) //判断欲搜索的楼层是否在1-9层
                                        {
                                            if(buttonUp[currentFloor - i] == 1 || buttonDown[currentFloor - i] == 1 || buttonNumber[currentFloor - i] == 1)
                                            {
                                                nextFloor = currentFloor - i;
                                                moveDirection = DOWN;
                                                break;
                                            }
                                        }

                                        //向上搜索
                                        if ((currentFloor + i) > 0 && (currentFloor + i) <= 9) //判断欲搜索的楼层是否在1-9层
                                        {
                                            if(buttonUp[currentFloor + i] == 1 || buttonDown[currentFloor + i] == 1 || buttonNumber[currentFloor + i] == 1)
                                            {
                                                nextFloor = currentFloor + i;
                                                moveDirection = UP;
                                                break;
                                            }
                                        }

                                    }//end of for
                                }

                        break;

                    case
                            UP://电梯运行方向向上

                        if (currentFloor == 9) //如果到达顶层 电梯为无运动方向
                        {


                            moveDirection = STOP;
                        }
                        else
                        {

                            int find = 0, i;


                            int nextFloor1, nextFloor2, count = 0, startjudge = 0, uptime = 0, downtime = 0;





                            if (profileEFfindnextfloor == 0)
                            {

                                for (i = 1; i <= currentFloor; i++)
                                {
                                    if (buttonUp[i] == 1 ||  buttonNumber[i] == 1 || buttonDown[i] == 1)
                                    {
                                        startjudge = 1;
                                        break;
                                    }
                                }

                                if (startjudge == 1)
                                {
                                    startjudge = 0;

                                    for (i = currentFloor + 1; i <= 9; i++)
                                    {
                                        count++;

                                        if (buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                        {
                                            uptime += velocity * count;

                                            if (buttonNumber[i] == 1)
                                            {
                                                uptime += (count - 1) * waitTime;
                                            }

                                        }
                                    }

                                    for (i = 8; i >= currentFloor + 1; i--)
                                    {
                                        count++;

                                        if (buttonDown[i] == 1)
                                        {
                                            uptime += velocity * count;

                                        }
                                    }

                                    for (i = currentFloor; i >= 1; i--)
                                    {
                                        count++;

                                        if (buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                        {
                                            uptime += velocity * count;

                                            if (buttonNumber[i] == 1)
                                            {
                                                uptime += (count - 1) * waitTime;
                                            }

                                        }
                                    }

                                    for (i = 2; i <= currentFloor; i++)
                                    {
                                        count++;

                                        if (buttonUp[i] == 1)
                                        {
                                            uptime += velocity * count;

                                        }
                                    }



                                    count = 0;


                                    for (i = currentFloor; i >= 1; i--)
                                    {
                                        count++;

                                        if (buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                        {
                                            downtime += velocity * count;

                                            if (buttonNumber[i] == 1)
                                            {
                                                downtime += (count - 1) * waitTime;
                                            }

                                        }
                                    }

                                    for (i = 2; i <= currentFloor; i++)
                                    {
                                        count++;

                                        if (buttonUp[i] == 1)
                                        {
                                            downtime += velocity * count;

                                        }
                                    }

                                    for (i = currentFloor + 1; i <= 9; i++)
                                    {
                                        count++;

                                        if (buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                        {
                                            downtime += velocity * count;

                                            if (buttonNumber[i] == 1)
                                            {
                                                downtime += (count - 1) * waitTime;
                                            }

                                        }
                                    }

                                    for (i = 8; i >= currentFloor + 1; i--)
                                    {
                                        count++;

                                        if (buttonDown[i] == 1)
                                        {
                                            downtime += velocity * count;

                                        }
                                    }



                                    count = 0;

                                    if (uptime * 5 > downtime * 6)
                                    {
                                        moveDirection = DOWN;
                                        profileEFfindnextfloor = 1;
                                        break;
                                    }



                                }
                            }



                            if (buttonNumber[currentFloor] == 1 && profileEFfindnextfloor == 1)
                            {
                                nextFloor = currentFloor;
                            }


                            for(i = currentFloor + 1; i <= 9; i++)
                            {
                                if(buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                {
                                    nextFloor = i;

                                    if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                    {
                                    }
                                    else
                                    {
                                        moveDirection = UP;
                                    }

                                    find = 1;
                                    break;
                                }


                            }


                            if (find != 1)
                            {
                                for (i = 9; i >= currentFloor + 1; i--)
                                {
                                    if (buttonDown[i] == 1)
                                    {
                                        nextFloor = i;

                                        if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                        {

                                        }
                                        else
                                        {
                                            moveDirection = UP;
                                        }

                                        find = 1;
                                        break;
                                    }
                                }

                                if (find != 1)
                                {
                                    if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                    {

                                    }
                                    else
                                    {
                                        moveDirection = STOP;
                                    }
                                }
                                else
                                {
                                    find = 0;
                                }



                            }
                            else
                            {
                                find = 0;
                            }
                        }

                        break;

                    case
                            DOWN://电梯运行方向向下
                        {

                            if (currentFloor == 1) //如果到达顶层 电梯为无运动方向
                            {



                                moveDirection = STOP;
                            }
                            else
                            {
                                int find = 0, i;



                                int nextFloor1, nextFloor2, count = 0, startjudge = 0, uptime = 0, downtime = 0;

                                if (profileEFfindnextfloor == 0)
                                {
                                    for (i = currentFloor; i <= 9; i++)
                                    {
                                        if (buttonUp[i] == 1 ||  buttonNumber[i] == 1 || buttonDown[i] == 1)
                                        {
                                            startjudge = 1;
                                            break;
                                        }
                                    }

                                    if (startjudge == 1)
                                    {
                                        startjudge = 0;

                                        for (i = currentFloor - 1; i >= 1; i--)
                                        {
                                            count++;

                                            if (buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                            {
                                                downtime += velocity * count;

                                                if (buttonNumber[i] == 1)
                                                {
                                                    downtime += (count - 1) * waitTime;
                                                }
                                            }
                                        }

                                        for (i = 2; i <= currentFloor - 1; i++)
                                        {
                                            count++;

                                            if (buttonUp[i] == 1)
                                            {
                                                downtime += velocity * count;

                                            }
                                        }

                                        for (i = currentFloor; i <= 9; i++)
                                        {
                                            count++;

                                            if (buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                            {
                                                downtime += velocity * count;

                                                if (buttonNumber[i] == 1)
                                                {
                                                    downtime += (count - 1) * waitTime;
                                                }

                                            }
                                        }

                                        for (i = 8; i >= currentFloor; i--)
                                        {
                                            count++;

                                            if (buttonDown[i] == 1)
                                            {
                                                downtime += velocity * count;

                                            }
                                        }



                                        count = 0;


                                        for (i = currentFloor; i <= 9; i++)
                                        {
                                            count++;

                                            if (buttonUp[i] == 1 ||  buttonNumber[i] == 1)
                                            {
                                                uptime += velocity * count;

                                                if (buttonNumber[i] == 1)
                                                {
                                                    uptime += (count - 1) * waitTime;
                                                }

                                            }
                                        }

                                        for (i = 8; i >= currentFloor; i--)
                                        {
                                            count++;

                                            if (buttonDown[i] == 1)
                                            {
                                                uptime += velocity * count;

                                            }
                                        }

                                        for (i = currentFloor - 1; i >= 1; i--)
                                        {
                                            count++;

                                            if (buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                            {
                                                uptime += velocity * count;

                                                if (buttonNumber[i] == 1)
                                                {
                                                    uptime += (count - 1) * waitTime;
                                                }

                                            }
                                        }

                                        for (i = 2; i <= currentFloor - 1; i++)
                                        {
                                            count++;

                                            if (buttonUp[i] == 1)
                                            {
                                                uptime += velocity * count;

                                            }
                                        }



                                        count = 0;

                                        if (downtime * 5 > uptime * 6)
                                        {
                                            moveDirection = UP;
                                            profileEFfindnextfloor = 1;
                                            break;
                                        }


                                    }

                                }

                                if (buttonNumber[currentFloor] == 1 && profileEFfindnextfloor == 1)
                                {
                                    nextFloor = currentFloor;
                                }

                                for(i = currentFloor - 1; i >= 1; i--)
                                {
                                    if(buttonDown[i] == 1 ||  buttonNumber[i] == 1)
                                    {
                                        nextFloor = i;

                                        if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                        {
                                        }
                                        else
                                        {
                                            moveDirection = DOWN;
                                        }

                                        find = 1;
                                        break;
                                    }


                                }


                                if (find != 1)
                                {
                                    for (i = 1; i <= currentFloor - 1; i++)
                                    {
                                        if (buttonUp[i] == 1)
                                        {
                                            nextFloor = i;

                                            if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                            {
                                            }
                                            else
                                            {
                                                moveDirection = DOWN;
                                            }

                                            find = 1;
                                            break;
                                        }
                                    }

                                    if (find != 1)
                                    {
                                        if (currentFloor == nextFloor && profileEFfindnextfloor == 1)
                                        {
                                        }
                                        else
                                        {
                                            moveDirection = STOP;
                                        }
                                    }
                                    else
                                    {
                                        find = 0;
                                    }



                                }
                                else
                                {
                                    find = 0;
                                }
                            }
                        }
                }
            }

            break;

    }//end of switch
}