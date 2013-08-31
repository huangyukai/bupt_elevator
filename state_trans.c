/***********************************************************
	�ļ����ƣ� ���ݵ�״̬����
	�� �ߣ� ������
	�� ���� 3.0
	˵ ���� �����Զ���ģ�ͺ�control()������ĵ���Ŀ��¥������з�������˿̵��ݵ�״̬
	�޸ļ�¼�� 1���޸���9������е�bug            �޸��ˣ�������
			   2���޸�����ͣ��������Sleep��ɵĴ��� �޸��ˣ�������
			   3��ȫ��ȥ��Sleep                     �޸��ˣ�������
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
	�������ƣ� state_trans()
	�������ܣ� ���Ƶ��ݵ�״̬
	��ڲ����� ��
	���ڲ����� ��
	�� ע�� ʹ�õ���ȫ�ֱ���
			buttonUp,buttonDown,buttonNumber,currentFloor,state,nextFloor,moveDirection
			����nextFloor��moveDirectionΪֻ�� �����޸�
			ʹ���Զ���ģ�� ���������ٶ�2��ÿ�� ����ͣ��ʱ��Ϊ4��
***********************************************************/
void state_trans()
{
    switch (state) /*����״̬���¼���������Ӧ�Ĵ���*/
    {
        case
                IDLE: //���ݿ���״̬

            if (moveDirection != STOP) //��control���������в�ͬ����Ӧ���� ���ݽ�������״̬
            {
                state = RUN;
                startIDLE = 1;
            }
            else
                if (currentFloor == nextFloor) //��control����������ͬ����Ӧ���� ���ݽ���ͣ��״̬
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

                            if (c > waitTime) //�ȴ�waitTime��
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
                RUN://��������״̬
            if (currentFloor == ignore)//��ȫ���н���
            {
                ignore = 0;
            }

            if (nextFloor < 0)
            {

                if (currentFloor != 1) //δ��Ŀ��¥��
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

                        if (cr > velocity)//ʱ�䵽velocity��
                        {
                            currentFloor--;
                            startRUN = 1;
                        }

                    }

                }

                if (currentFloor == 1) //���ݵ���Ŀ��¥��
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

                if (currentFloor != nextFloor) //δ��Ŀ��¥��
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

                if (currentFloor == nextFloor) //���ݵ���Ŀ��¥��
                {
                    if (moveDirection == UP) //�ر���Ӧ�İ�ť ���ݽ���ͣ��״̬
                    {
                        if (Profile == B)//B���Ե�������
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
                        totalTime[previousProfile] += (double) (staticStop - staticStart) / CLOCKS_PER_SEC;//ͳ��ʱ��

                    }

                    if (moveDirection == DOWN) //�ر���Ӧ�İ�ť ���ݽ���ͣ��״̬

                    {
                        if (Profile == B)//B�����赥������
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

                        state = STOP;//����ͣ��
                        startRun = 1;
                        staticStop = clock();

                        totalTime[previousProfile] += (double) (staticStop - staticStart) / CLOCKS_PER_SEC;//ͳ��ʱ��

                    }

                    if (moveDirection == STOP) //������������з��� ���ݽ���ͣ��״̬
                    {
                        state = STOP;
                        startRun = 1;
                        staticStop = clock();

                        totalTime[previousProfile] += (double) (staticStop - staticStart) / CLOCKS_PER_SEC;//ͳ��ʱ��
                    }
                }

            }

            break;

        case
                STOP: //����ͣ��״̬

            control();//�����ж�һ��Ŀ��¥������з���

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

                if (cs > stopTime || Go == 1)//Goָ���ж�
                {
                    startSTOP = 1;
                    Go = 0;
                }
            }

            if (startSTOP == 1)
            {

                if (nextFloor == 0) //�����Ŀ��¥�� ���ݽ������״̬
                {
                    moveDirection = STOP;
                    state = IDLE;
                }
                else//��Ŀ��¥������ݽ�������״̬
                {
                    state = RUN;
                }

            }

            break;
    }//end of switch
}

