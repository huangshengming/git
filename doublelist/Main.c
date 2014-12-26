#include "doublelist.h"

void menu();
void inputElement(elemType *peValue);
void outputElement(elemType *peValue);
WORD EqualElem(elemType *peSource, elemType *peTarget);

int main()
{
	List_t  DL;
	int iChoice;
	int iFlag = 1;
	//int iSize;
	int iState;

	DoubleListInit(&DL);

	while(iFlag)
    {
        menu();
        printf("\t��ѡ��˵���(0--6)��");
		fflush(stdin);
        scanf("%d",&iChoice);
        
        switch(iChoice)
        {
        case 0:
            {
                iFlag = 0;
			}
			break;
		case 1:
			{
				elemType Pvalue;
				Pvalue = DoubleListDisplay(&DL,outputElement);
				if (ILLEGAL == Pvalue)
				{
					printf("�Ƿ���˫����\n");
				}
				else if (ERROR == Pvalue)
				{
					printf("˫����Ϊ��\n");
				}
			}
			break;
        case 2:
            {
				elemType eSize;
				printf("\n������е�Ԫ�ظ���: ");
				inputElement(&eSize);

				iState = DoubleListHead(&DL, eSize, inputElement, EqualElem);


				if (TRUE == iState)
				{
					printf("\n��ֵ�ɹ���");
				}
				else if (ERROR == iState)
				{
					printf("����������Ԫ�ظ�������\n");
				}
				else
				{
					printf("�޷����룡");
				}
			}
			break;
        case 3:
            {
				int iPostion = 0;
				elemType eOutValue;

				printf("\n������Ҫɾ���ڼ�λ��");
				scanf("%d", &iPostion);

				iState = DoubleListDelete(&DL, iPostion, &eOutValue);

				if (TRUE == iState)
				{
					printf("ɾ���ɹ���");
				}
				else if (ILLEGAL == iState)
				{
					printf("�Ƿ�������!");
				}
				else if (ERROR == iState)
				{
					printf("����Ϊ��!");
				}
				else
				{
					printf("Ҫɾ����λ�ó���");
				}
			}
			break;
        case 4:
            {
				elemType eSize;
				printf("\n������е�Ԫ�ظ���: ");
				inputElement(&eSize);
				
				iState = DoubleListLast(&DL, eSize, inputElement, EqualElem);
				
				if (TRUE == iState)
				{
					printf("��ֵ�ɹ���");
				}
				else if (ERROR == iState)
				{
					printf("����������Ԫ�ظ�������\n");
				}
				else
				{
					printf("�޷����룡");
				}
			}
			break;
		case 5:
			{
			    iState = DoubleListEmpty(&DL);

				if (TRUE == iState)
				{
					printf("�ձ�û���κ�ֵ��");
				}
				else
				{
					printf("��Ϊ�գ��ɶ�ȡ����");
				}
			}
			break;
		case 6:
			{
				elemType pOutValue;
				pOutValue = DoubleListLength(&DL);
				
				printf("����Ԫ�ظ���: %d\n", pOutValue);
			}
			break;
		case 7:
			{
				int iPostion = 0;
				elemType eInValue;
				
				printf("\n������Ҫ���뵽�ڼ�λ��");
				scanf("%d", &iPostion);

				printf("\n�������е�Ԫ��: ");
				inputElement(&eInValue);

				iState = DoubleListInsert(&DL, iPostion, &eInValue, EqualElem);

				if (TRUE == iState)
				{
					printf("����ɹ���");
				}
				else if (ILLEGAL == iState)
				{
					printf("�Ƿ�������!");
				}
				else if (ISVALID == iState)
				{
					printf("Ҫ�����λ�ó���");
				}
				else if (EXIST == iState)
				{
					printf("�������и�Ԫ��");
				}
				else
				{
					printf("�����ڴ�ռ䲻�ɹ�");
				}
			}
			break;
		case 8:
			{
				int iOutPostion = 0;
				elemType eInValue = 0;

				printf("������Ҫ���ҵ�Ԫ��ֵ: ");
				inputElement(&eInValue);

				iState = DoubleListValueFind(&DL, &eInValue, &iOutPostion, EqualElem);

				if (EXIST == iState)
				{
					printf("Ԫ��%d�ڱ��еĵ�%dλ!\n", eInValue, iOutPostion);
				}
				else if (NOEXIST == iState)
				{
					printf("����û��Ԫ��: %d\n", eInValue);
				}
				else
				{
					printf("�Ƿ�������!");
				}
			}
			break;
		default:
			{
				printf("������Ŵ���");
				break;
			}
        }
    }
	return 0;
}

void menu()
{
	printf("\n");
	printf("****************************************************\n");
	printf("\n*             ˫   ��   ��   ϵ   ͳ               *");
	printf("\n****************************************************");
	printf("\n*            0----------��      ��                 *");
	printf("\n*            1----------��      ��                 *");
	printf("\n*                                                  *");
	printf("\n*            2----------ͷ  ��  ��                 *");
	printf("\n*            3----------ɾ      ��                 *");
	printf("\n*            4----------β  ��  ��                 *");
	printf("\n*                                                  *");
	printf("\n*            5----------�жϱ�Ϊ��                 *");
	printf("\n*            6----------��ȡ����Ԫ�ظ���           *");
	printf("\n*            7----------�� �� Ԫ ��                *");
	printf("\n*            8----------�� �� Ԫ ��                *");
	printf("\n****************************************************");
	printf("\n");
	
}

void inputElement(elemType *peValue)
{
	scanf("%d", peValue);
}

void outputElement(elemType *peValue)
{
	printf("%d ", *peValue);
}

WORD EqualElem(elemType *peSource, elemType *peTarget)
{
    if (*peSource == *peTarget)
    {
        return(TRUE);
    }
    else
    {
        return(FALSE);
    }     
}