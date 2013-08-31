/***********************************************************
	�ļ����ƣ� ���ܼ�������
	�� �ߣ� ������
	�� ���� 5.0
	˵ ���� ���ܼ�������
	���ݰ�ť����������
	�޸ļ�¼�����Ӱ�ȫ��Ӧ �޸���:������
***********************************************************/
#include <stdio.h>
#include <conio.h>
#include "list.h"
#include "sharedVariables.h"


extern int buttonUp[10];
extern int buttonDown[10];
extern int buttonNumber[10];
extern int currentFloor;
extern int nextFloor;
extern int moveDirection;//���з���
extern int state;
extern int Profile;
extern int profileChange;
extern int initialization;
extern int blockedFloor;
extern int Go;
int ignore = 0;//�ж��Ƿ�ȫ����

/***********************************************************
	�������ƣ�getInput()
	�������ܣ� ��ü��̵�ָ��
	��ڲ����� ��
	���ڲ����� ��
	�� ע�� ʹ��getche�ɲ��ûس�
***********************************************************/
void getInput(void)//�õ���������ָ��
{
    char input;//��ǰ�����ַ�

    while(1)
    {
        if (initialization == 0)
        {
            input = getche();

            if ( ((checkFloor(input) > blockedFloor || (checkFloor(input) == 1) && Profile == D) || Profile != D))
            {

                switch(input)//�������������ͬ�İ�ť�����л�����
                {
                    case '\n'
                            ://�������лس�����
                        break;

                        //�������ϵİ�ť������
                    case 'q'
                            :
                        if(currentFloor != 1 || (currentFloor == 1 && state != STOP))
                        {
                            buttonUp[1] = 1;
                            createList(input);
                        }

                        break;

                    case 'w'
                            :
                        if(currentFloor != 2 || (currentFloor == 2 && state != STOP))
                        {
                            buttonUp[2] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 2))
                            {
                                ignore = 2;
                            }
                        }

                        break;

                    case 'e'
                            :
                        if(currentFloor != 3 || (currentFloor == 3 && state != STOP))
                        {
                            buttonUp[3] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 3))
                            {
                                ignore = 3;
                            }
                        }

                        break;

                    case 'r'
                            :
                        if(currentFloor != 4 || (currentFloor == 4 && state != STOP))
                        {
                            buttonUp[4] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 4))
                            {
                                ignore = 4;
                            }
                        }

                        break;

                    case 't'
                            :
                        if(currentFloor != 5 || (currentFloor == 5 && state != STOP))
                        {
                            buttonUp[5] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 5))
                            {
                                ignore = 5;
                            }
                        }

                        break;

                    case 'y'
                            :
                        if(currentFloor != 6 || (currentFloor == 6 && state != STOP))
                        {
                            buttonUp[6] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 6))
                            {
                                ignore = 6;
                            }
                        }

                        break;

                    case 'u'
                            :
                        if(currentFloor != 7 || (currentFloor == 7 && state != STOP))
                        {
                            buttonUp[7] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 7))
                            {
                                ignore = 7;
                            }
                        }

                        break;

                    case 'i'
                            :
                        if(currentFloor != 8 || (currentFloor == 8 && state != STOP))
                        {
                            buttonUp[8] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == UP) && ((currentFloor + 1) == 8))
                            {
                                ignore = 8;
                            }
                        }

                        break;

                        //�������°�ť������
                    case 'a'
                            :
                        if(currentFloor != 2 || (currentFloor == 2 && state != STOP))
                        {
                            buttonDown[2] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 2))
                            {
                                ignore = 2;
                            }
                        }

                        break;

                    case 's'
                            :
                        if(currentFloor != 3 || (currentFloor == 3 && state != STOP))
                        {
                            buttonDown[3] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 3))
                            {
                                ignore = 3;
                            }
                        }

                        break;

                    case 'd'
                            :
                        if(currentFloor != 4 || (currentFloor == 4 && state != STOP))
                        {
                            buttonDown[4] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 4))
                            {
                                ignore = 4;
                            }
                        }

                        break;

                    case 'f'
                            :
                        if(currentFloor != 5 || (currentFloor == 5 && state != STOP))
                        {
                            buttonDown[5] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 5))
                            {
                                ignore = 5;
                            }
                        }

                        break;

                    case 'g'
                            :
                        if(currentFloor != 6 || (currentFloor == 6 && state != STOP))
                        {
                            buttonDown[6] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 6))
                            {
                                ignore = 6;
                            }
                        }

                        break;

                    case 'h'
                            :
                        if(currentFloor != 7 || (currentFloor == 7 && state != STOP))
                        {
                            buttonDown[7] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 7))
                            {
                                ignore = 7;
                            }
                        }

                        break;

                    case 'j'
                            :
                        if(currentFloor != 8 || (currentFloor == 8 && state != STOP))
                        {
                            buttonDown[8] = 1;
                            createList(input);

                            if ((state == RUN) && (moveDirection == DOWN) && ((currentFloor - 1) == 8))
                            {
                                ignore = 8;
                            }
                        }

                        break;

                    case 'k'
                            :
                        if(currentFloor != 9 || (currentFloor == 9 && state != STOP))
                        {
                            buttonDown[9] = 1;
                            createList(input);
                        }

                        break;

                        //�����ڲ���ť����
                    case '1'
                            :
                        if(currentFloor != 1 || (currentFloor == 1 && state != STOP))
                        {
                            buttonNumber[1] = 1;
                            createList(input);
                        }

                        break;

                    case '2'
                            :
                        if(currentFloor != 2 || (currentFloor == 2 && state != STOP))
                        {
                            if (state == RUN && ((currentFloor + moveDirection) == 2))
                            {
                                ignore = 2;
                            }

                            buttonNumber[2] = 1;
                            createList(input);

                        }

                        break;

                    case '3'
                            :
                        if(currentFloor != 3 || (currentFloor == 3 && state != STOP))
                        {
                            if (state == RUN && ((currentFloor + moveDirection) == 3))
                            {
                                ignore = 3;
                            }

                            buttonNumber[3] = 1;
                            createList(input);

                        }

                        break;

                    case '4'
                            :
                        if(currentFloor != 4 || (currentFloor == 4 && state != STOP))
                        {
                            if (state == RUN && ((currentFloor + moveDirection) == 4))
                            {
                                ignore = 4;
                            }

                            buttonNumber[4] = 1;
                            createList(input);

                        }

                        break;

                    case '5'
                            :
                        if(currentFloor != 5 || (currentFloor == 5 && state != STOP))
                        {
                            if (state == RUN && ((currentFloor + moveDirection) == 5))
                            {
                                ignore = 5;
                            }

                            buttonNumber[5] = 1;
                            createList(input);

                        }

                        break;

                    case '6'
                            :
                        if(currentFloor != 6 || (currentFloor == 6 && state != STOP))
                        {
                            if (state == RUN && ((currentFloor + moveDirection) == 6))
                            {
                                ignore = 6;
                            }

                            buttonNumber[6] = 1;
                            createList(input);

                        }

                        break;

                    case '7'
                            :
                        if(currentFloor != 7 || (currentFloor == 7 && state != STOP))
                        {
                            if (state == RUN && ((currentFloor + moveDirection) == 7))
                            {
                                ignore = 7;
                            }

                            buttonNumber[7] = 1;
                            createList(input);

                        }

                        break;

                    case '8'
                            :
                        if(currentFloor != 8 || (currentFloor == 8 && state != STOP))
                        {
                            if (state == RUN && ((currentFloor + moveDirection) == 8))
                            {
                                ignore = 8;
                            }

                            buttonNumber[8] = 1;
                            createList(input);

                        }

                        break;

                    case '9'
                            :
                        if(currentFloor != 9 || (currentFloor == 9 && state != STOP))
                        {
                            buttonNumber[9] = 1;
                            createList(input);
                        }

                        break;

                    case 'G'
                            :
                        Go = 1;
						break;

                        //�����л�
                    case 'A'
                            :
                        Profile = A;
                        profileChange = 1;
                        break;

                    case 'B'
                            :
                        Profile = B;
                        profileChange = 1;
                        break;

                    case 'C'
                            :
                        Profile = C;
                        profileChange = 1;
                        break;

                    case 'D'
                            :
                        Profile = D;
                        profileChange = 1;
                        break;

                        //���������Ϊ�Ƿ�����
                    default
                            :
                        printf("\b����������������룡");
                        break;
                }//end of switch
            }
        }//end of if
    }//end of while
}

