/***********************************************************
	�ļ����ƣ� ����������
	�� �ߣ� ������
	�� ���� 2.1
	˵ ���� ����˳�������ԣ�������ͼ�ν����¿ɽ�ֱ�۵Ĺ۲��������״̬��
			ʱ��ԭ��δ�������2�����ԣ���Ԥ�������ӿڡ�����β������޸�������֪bug��
	�޸ļ�¼:1�������������Ϊ�����߳�         �޸���: ������
			 2��ȥ��ʱ����ƺ��� ��ΪSleep���� �޸���: ������
			 3�����ʱ����� ȥ��Sleep         �޸���: ������
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

int buttonUp[10] = {0}; //�������ϰ�ť
int buttonDown[10] = {0}; //�������°�ť
int buttonNumber[10] = {0}; //�����ڲ���ť
int currentFloor = 1; //��ǰ¥�� Ĭ�ϵ�����1¥
int nextFloor = 0; //��������Ŀ��¥�� Ϊ0��ʾ�޺�����Ҫ��Ӧ
int state = IDLE; //��������״̬(���С�ͣ��������) Ĭ��Ϊ����
int moveDirection = STOP; //�������з���(���ϡ����»�ֹͣ) Ĭ��Ϊֹͣ
int Profile = A; //���ݿ��Ʋ��� Ĭ��Ϊ����A(˳��������)
int previousProfile;//�л�����ʱ��ǰһ������
int profileChange = 0; //���ݲ��Ը��ı��
int velocity = 5; //���������ٶ�
int stopTime = 5; //����ͣ��ʱ��
int waitTime = 10;//���еȴ�ʱ��
int blockedFloor = 5;//������Ӧ��¥��
double totalTime[7] = {0};//ͳ���ܹ�ʱ��
double eachNumber[7] = {0};//ͳ����Ӧ����
double averageTime[7] = {0};//ͳ��ƽ��ʱ��
int Go = 0;//Go��ť
double restTime = 0;//ͳ��ͣ��ʣ��ʱ��
HEGG background, elevator, button, head, string, initial; //egg�е�ͼ��
int startexit = 0;//ͼ�ν���رձ�ʶ����
int openbutton = 0;//���ݹ���ʱ���¿��ż��ı�ʶ����
//����ʱʹ��
char listUp[10] = {0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 0};
char listDown[10] = {0, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k'};
char listNumber[10] = {0, '1', '2', '3', '4', '5', '6', '7', '8', '9'};
HANDLE hMutex;//�������

main()
{
    //���������ȡ������߳�
    DWORD ThreadID = 1, ThreadID1 = 2;
    HANDLE hRead, hRead1;

    initialize();//��ʼ������

    hMutex = CreateMutex(NULL, FALSE, NULL);//�����������

    //���������߳�
    hRead = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)getInput, NULL, 0, &ThreadID);//���ܼ�������
    hRead1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)IO, NULL, 0, &ThreadID1);//������Ļ�����dos���

    while (1)//�����ظ��жϵ����������
    {

        state_trans(); //�����Զ���ģ�ͺ�control()������ĵ���Ŀ��¥������з�������˿̵��ݵ�״̬
        control();   //���ݵ�ǰ���Ծ����˿̵���Ŀ��¥������з���

        if (startexit == 1)//��⵽ͼ�ν���ر� return�˳�
        {
            return 0;
        }
    }
}

