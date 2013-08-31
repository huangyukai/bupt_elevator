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
#include "egg.h"
#include "control.h"
#include "sharedVariables.h"
#include "graphical_interface.h"
//�ⲿ��������
extern HEGG background, elevator, button, head, string;
extern HANDLE hMutex;
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
extern double totalTime[7];
extern double eachNumber[7];
extern int Go;
extern int openbutton;
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
extern int profileCfindnextfloor;
extern int profileEFfindnextfloor;
//���벻ͬ״̬�ı�ʾ
int startIDLE = 1;
int startRun = 1;
int startRUN = 1;
int startSTOP = 1;
int startRUNEF = 1 ;
//ʱ��ͳ�Ʊ���
double a, b, c;
double as, bs, cs;
double ar, br, cr;
double directa, directb, directc;
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
    static int reopen = 0;//���ݹ���ʱ���¿��ż��ı�ʾ

    switch (state) //����״̬���¼���������Ӧ�Ĵ���
    {
        case
                IDLE: //���ݿ���״̬
            if (openbutton == 1)
            {
                state = STOP;//���ݰ��¿��Ű�ť����ͣ��״̬
            }

            if (moveDirection != STOP) //��control���������в�ͬ����Ӧ���� ���ݽ�������״̬
            {
                state = RUN;//���ݽ�������״̬
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
                    else
                    {
                        moveDirection = STOP;
                    }
                }

            break;

        case
                RUN://��������״̬
            if (currentFloor == ignore)//��ȫ���н���
            {
                ignore = 0;
            }

            if (nextFloor == -1 || profileCfindnextfloor == 1)
            {

                if (currentFloor != 1) //δ��Ŀ��¥��
                {

                    if (startRUN == 1)//��ʱ����ʼ��ʱ
                    {
                        directa = ar = clock();
                        startRUN = 0;
                    }
                    else
                    {
                        directb = br = clock();
                        cr = (double) (br - ar) / CLOCKS_PER_SEC;
                        directc = (double) (directb - directa) / CLOCKS_PER_SEC;
                        elevatorMove((double)cr / velocity);//�������ж���

                        if (directc >= 0.05)
                        {
                            directa = clock();
                            showDirection_run(0);//ָʾ�ƶ���
                        }

                        if (cr > velocity)//ʱ�䵽velocity��
                        {
                            currentFloor--;
                            profileCfindnextfloor = 0;
                            showFloor();
                            elevatorMove(0);
                            startRUN = 1;
                        }

                    }

                }

                if (currentFloor == 1) //���ݵ���Ŀ��¥��
                {
                    nextFloor = 0;
                    state = IDLE;
                    moveDirection = STOP;
                    showDirection_stop();
                }

            }
            else//profileCfindnextfloor==0
            {

                if (startRun == 1)
                {
                    staticStart = clock();//ͳ�Ƽ�ʱ
                    startRun = 0;
                }

                if (currentFloor != nextFloor || profileEFfindnextfloor == 1) //δ��Ŀ��¥��
                {
                    if (startRUN == 1)
                    {
                        directa = ar = clock();
                        startRUN = 0;
                        profileEFfindnextfloor = 0;
                    }
                    else
                    {

                        if (profileEFfindnextfloor == 1)
                        {
                            static double temptime1, temptime = 0;

                            if (startRUNEF == 1)
                            {
                                br = clock();
                                temptime = (double) (br - ar) / CLOCKS_PER_SEC;
                                temptime1 = temptime;
                                ar = clock();
                                startRUNEF = 0;
                            }
                            else
                            {

                                directb = br = clock();
                                cr = (double) (br - ar) / CLOCKS_PER_SEC;
                                directc = (double) (directb - directa) / CLOCKS_PER_SEC;


                                temptime = temptime1 - cr;

                                if (temptime > 0)
                                {

                                    elevatorMove((double)(velocity - temptime) / velocity);

                                }

                                if (directc >= 0.05)
                                {
                                    directa = clock();
                                    showDirection_run(0);//ָʾ�ƶ���
                                }

                                if (temptime < 0)
                                {

                                    showFloor();//��ʾ��ǰ¥��

                                    profileEFfindnextfloor = 0;
                                    elevatorMove(0);//�������ж���
                                    startRUNEF = 1;
                                    startRUN = 1;
                                    temptime = 0;
                                }


                            }


                        }

                        else

                        {
                            directb = br = clock();

                            cr = (double) (br - ar) / CLOCKS_PER_SEC;
                            directc = (double) (directb - directa) / CLOCKS_PER_SEC;

                            if (profileEFfindnextfloor == 0)
                            {
                                elevatorMove((double)cr / velocity);//�������ж���
                            }

                            if (directc >= 0.05)
                            {
                                directa = clock();
                                showDirection_run(0);//ָʾ�ƶ���
                            }

                            if (cr > velocity)
                            {
                                currentFloor += moveDirection;
                                showFloor();//��ʾ��ǰ¥��

                                if (profileEFfindnextfloor == 0)
                                {
                                    elevatorMove(0);//�������ж���
                                }

                                startRUN = 1;
                            }
                        }


                    }
                }




                if ((currentFloor == nextFloor) && (profileEFfindnextfloor == 0)) //���ݵ���Ŀ��¥��
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

                        else//�رհ�ť
                        {
                            if((buttonUp[currentFloor] == 0) && (buttonNumber[currentFloor] == 0))
                            {
                                buttonDown[currentFloor] = 0;
                                deleteNode(listDown[currentFloor]);
                                lightOff(listDown[currentFloor]);

                                eachNumber[previousProfile]++;
                            }
                            else//�رհ�ť
                            {
                                buttonUp[currentFloor] = 0;
                                buttonNumber[currentFloor] = 0;
                                lightOff(listUp[currentFloor]);
                                lightOff(listNumber[currentFloor]);

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
                        else//�رհ�ť
                        {
                            if ((buttonDown[currentFloor] == 0) && (buttonNumber[currentFloor] == 0))
                            {
                                buttonUp[currentFloor] = 0;
                                lightOff(listUp[currentFloor]);
                                deleteNode(listUp[currentFloor]);

                                eachNumber[previousProfile]++;
                            }
                            else//�رհ�ť
                            {

                                buttonDown[currentFloor] = 0;
                                buttonNumber[currentFloor] = 0;
                                lightOff(listDown[currentFloor]);
                                lightOff(listNumber[currentFloor]);

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
                        //ʱ��ͳ��
                        totalTime[previousProfile] += (double) (staticStop - staticStart) / CLOCKS_PER_SEC;//ͳ��ʱ��
                    }
                }

            }

            break;

        case
                STOP: //����ͣ��״̬

            if (startSTOP == 1)//�տ�ʼͣ��
            {
                DWORD ThreadIDa = 1, ThreadIDb = 2;
                HANDLE hReada, hReadb;
                as = clock();//��ʱ����ʼ��

                if (reopen == 1)//�ж��Ƿ���
                {
                    reopen = 0;
                }
                else
                {
                    //���Ŷ���,ָʾ�ƶ������Ҳ�������
                    hReada = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)arriveSound, NULL, 0, &ThreadIDa);
                    hReadb = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)showDirection_stop, NULL, 0, &ThreadIDb);
                    openDoor();

                    startSTOP = 0;
                }

            }
            else
            {

                if (openbutton == 1)//�������ż��򲻹���
                {
                    as = clock();
                    restTime = stopTime;
                }
                else
                {
                    showDirection_stop();
                    bs = clock();
                    cs = (double) (bs - as) / CLOCKS_PER_SEC;
                    restTime = stopTime - cs;

                    if (cs > stopTime || Go == 1)//Goָ���ж�
                    {
                        startSTOP = 1;

                    }

                }

            }

            if (startSTOP == 1)
            {

                if (nextFloor == 0) //�����Ŀ��¥�� ���ݽ������״̬
                {
                    if (closeDoor() == 1)
                    {
                        state = STOP;
                        startSTOP = 1;
                        reopen = 1;
                        break;
                    }

                    moveDirection = STOP;
                    state = IDLE;

                    if (Profile == B)
                    {
                        showDirection_stop();
                    }

                }
                else//��Ŀ��¥������ݽ�������״̬
                {
                    if (closeDoor())
                    {
                        state = STOP;
                        startSTOP = 1;
                        reopen = 1;
                        break;
                    }

                    state = RUN;
                    control();
                    gosound();

                }

            }

            break;

    }//end of switch
}

