/***********************************************************
	�ļ����ƣ� ���Կ���
	�� �ߣ� ������
	�� ���� 7.02
	˵ ���� �ò�ͬ�Ĳ��Կ��Ƶ���
	�޸ļ�¼������BCD����     �޸��ˣ�������
			  ����˳�����bug �޸��ˣ�������
			  �޸İ�ȫ��Ӧbug �޸��ˣ�������
			  ����ͳ��        �޸��ˣ�������
***********************************************************/
#include "list.h"
#include <stdlib.h>
#include "sharedVariables.h"

//ȫ�ֱ�������
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
extern int previousProfile;
extern char listUp[10];
extern char listDown[10];
extern char listNumber[10];
extern double eachNumber[5];
extern int ignore;
extern LISTNODEPTR headPtr;
extern LISTNODEPTR lastPtr;
extern LISTNODEPTR currentPtr;
extern LISTNODEPTR tempPtr;

/***********************************************************
	�������ƣ� control()
	�������ܣ� ���ݲ��� �����������е�Ŀ��¥��͵������з���
	��ڲ����� ��
	���ڲ����� ��
	�� ע��    ֻ���޸�nextFloor��moveDirection
***********************************************************/
void control()
{
    int i;//ѭ������

    switch(Profile)//�����л�
    {
        case
                A:
            if (profileChange == 1) //�仯����ʱ�Ĺ���
            {
                if (currentFloor == nextFloor || nextFloor == 0)
                {
                    profileChange = 0; //��ɲ����л��Ĺ���
                    previousProfile = Profile;
                }
            }
            else//����A����
            {
                switch (moveDirection)//���ݵ������з����ж�Ŀ��¥�����һ�������з���
                {
                    case
                            STOP://���������з���
                        nextFloor = 0; //Ĭ����Ŀ��¥�� ��������ʼ����Ŀ��¥��

                        //�����ͬ����Ӧ
                        if(buttonUp[currentFloor] == 1)
                        {
                            moveDirection = UP;
                            buttonUp[currentFloor] = 0;
                            eachNumber[previousProfile]++;//ͳ����Ӧ����

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
                                eachNumber[previousProfile]++;//ͳ����Ӧ����

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
                                    eachNumber[previousProfile]++;//ͳ����Ӧ����

                                    if (headPtr != NULL)
                                    {

                                        deleteNode(listNumber[currentFloor]);
                                    }
                                }
                                else
                                    //��ͬ����Ӧ ��ӱ���Ϊ���� ��������������Ӧ
                                {
                                    for(i = 1; i <= 9; i++)
                                    {
                                        //��������
                                        if ((currentFloor - i) > 0 && (currentFloor - i) <= 9) //�ж���������¥���Ƿ���1-9��
                                        {
                                            if(buttonUp[currentFloor - i] == 1 || buttonDown[currentFloor - i] == 1 || buttonNumber[currentFloor - i] == 1)
                                            {
                                                nextFloor = currentFloor - i;

                                                moveDirection = DOWN;
                                                break;
                                            }
                                        }

                                        //��������
                                        if ((currentFloor + i) > 0 && (currentFloor + i) <= 9) //�ж���������¥���Ƿ���1-9��
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
                            UP://�������з�������

                        if (currentFloor == 9) //������ﶥ�� ����Ϊ���˶�����
                        {
                            moveDirection = STOP;
                        }
                        else
                        {
                            int find = 0, temp = 0;

                            if (ignore != 0)//��ȫ���е��ж� ����Ӧ�ٽ�¥��
                            {
                                temp = 1;
                            }

                            for(i = currentFloor + 1 + temp; i <= 9; i++)//�ȼ�����޵��·������ϵ�����
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
                                for (i = 9; i >= currentFloor + 1; i--)//�ټ�����޵��·������µ�����
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
                            DOWN://�������з�������
                        if (currentFloor == 1)
                        {
                            moveDirection = STOP;
                        }

                        else
                        {
                            int find = 0, temp = 0;

                            if (ignore != 0)
                            {
                                temp = 1;
                            }

                            for(i = currentFloor - 1 - temp; i >= 1; i--)//�������������µ�����
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
                                for (i = 1; i <= currentFloor - 1; i++)//�ټ��ᵼ�·������ϵ�����
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
                B://����B

            if (profileChange == 1)//���Ա仯ʱ�Ĺ���
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
                        //�����ͬ����Ӧ
                        if(buttonUp[currentFloor] == 1)
                        {
                            moveDirection = UP;

                            if (headPtr != NULL)
                            {
                                closeButton();//�رյ��ݰ�ť
                                eachNumber[previousProfile]++;//ͳ�ƴ���
                                deleteNode(listUp[currentFloor]);
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
                                    }

                                    nextFloor = currentFloor;
                                }
                    }
                    else
                    {
                        switch(headPtr->data)//���������е����ݾ����������з���
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
            if (profileChange == 1) //�仯����ʱ�Ĺ���
            {
                if (currentFloor == nextFloor || nextFloor == 0)
                {
                    profileChange = 0; //��ɲ����л��Ĺ���
                    previousProfile = Profile;
                }
            }
            else
            {
                switch (moveDirection)//���ݵ������з����ж�Ŀ��¥�����һ�������з���
                {
                    case
                            STOP://���������з���
                        if (nextFloor != -1)
                        {

                            nextFloor = 0; //Ĭ����Ŀ��¥�� ��������ʼ����Ŀ��¥��
                        }

                        //�����ͬ����Ӧ
                        if(buttonUp[currentFloor] == 1)
                        {
                            moveDirection = UP;
                            buttonUp[currentFloor] = 0;
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
                                    eachNumber[previousProfile]++;

                                    if (headPtr != NULL)
                                    {

                                        deleteNode(listNumber[currentFloor]);
                                    }
                                }
                                else
                                    //��ͬ����Ӧ ��ӱ���Ϊ���� ��������������Ӧ
                                {
                                    for(i = 1; i <= 9; i++)
                                    {
                                        //��������
                                        if ((currentFloor - i) > 0 && (currentFloor - i) <= 9) //�ж���������¥���Ƿ���1-9��
                                        {
                                            if(buttonUp[currentFloor - i] == 1 || buttonDown[currentFloor - i] == 1 || buttonNumber[currentFloor - i] == 1)
                                            {
                                                nextFloor = currentFloor - i;
                                                moveDirection = DOWN;
                                                break;
                                            }
                                        }

                                        //��������
                                        if ((currentFloor + i) > 0 && (currentFloor + i) <= 9) //�ж���������¥���Ƿ���1-9��
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
                            UP://�������з�������

                        if (currentFloor == 9) //������ﶥ�� ����Ϊ���˶�����
                        {
                            int i;

                            for (i = 1; i <= 9; i++)
                            {
                                buttonNumber[i] = 0;

                                deleteNode(listNumber[i]);
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
                            DOWN://�������з�������



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
                                        moveDirection = UP;
                                    }
                                    else
                                    {
                                        if (nextFloor < currentFloor)
                                        {
                                            moveDirection = DOWN;
                                        }
                                        else
                                        {
                                            moveDirection = STOP;
                                        }
                                    }


                                    break;

                                }

                            }

                        }
                        else

                        {



                            if (currentFloor == 1) //������ﶥ�� ����Ϊ���˶�����
                            {
                                int i;

                                for (i = 1; i <= 9; i++)
                                {
                                    buttonNumber[i] = 0;
                                    deleteNode(listNumber[i]);
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
            if (profileChange == 1) //�仯����ʱ�Ĺ���
            {
                if (currentFloor == nextFloor || nextFloor == 0)
                {
                    profileChange = 0; //��ɲ����л��Ĺ���
                    previousProfile = Profile;
                }
            }
            else
            {
                switch (moveDirection)//���ݵ������з����ж�Ŀ��¥�����һ�������з���
                {
                    case
                            STOP://���������з���


                        nextFloor = 0; //Ĭ����Ŀ��¥�� ��������ʼ����Ŀ��¥��

                        //�����ͬ����Ӧ
                        if(buttonUp[currentFloor] == 1)
                        {
                            moveDirection = UP;
                            buttonUp[currentFloor] = 0;
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
                                    eachNumber[previousProfile]++;

                                    if (headPtr != NULL)
                                    {

                                        deleteNode(listNumber[currentFloor]);
                                    }
                                }
                                else
                                    //��ͬ����Ӧ ��ӱ���Ϊ���� ��������������Ӧ
                                {
                                    for(i = 1; i <= 9; i++)
                                    {
                                        //��������
                                        if ((currentFloor - i) > 0 && (currentFloor - i) <= 9) //�ж���������¥���Ƿ���1-9��
                                        {
                                            if(buttonUp[currentFloor - i] == 1 || buttonDown[currentFloor - i] == 1 || buttonNumber[currentFloor - i] == 1)
                                            {
                                                nextFloor = currentFloor - i;
                                                moveDirection = DOWN;
                                                break;
                                            }
                                        }

                                        //��������
                                        if ((currentFloor + i) > 0 && (currentFloor + i) <= 9) //�ж���������¥���Ƿ���1-9��
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
                            UP://�������з�������

                        if (currentFloor == 9) //������ﶥ�� ����Ϊ���˶�����
                        {
                            int i;

                            for (i = 1; i <= 9; i++)
                            {
                                buttonNumber[i] = 0;
                                deleteNode(listNumber[i]);

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
                            DOWN://�������з�������
                        if (currentFloor == 1) //������ﶥ�� ����Ϊ���˶�����
                        {
                            int i;

                            for (i = 1; i <= 9; i++)
                            {
                                buttonNumber[i] = 0;

                                deleteNode(listNumber[i]);
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
    }//end of switch
}