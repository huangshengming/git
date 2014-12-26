#include "doublelist.h"

WORD DoubleListInit(List_t *pDL)
{
	//�ж��Ƿ�Ϸ�
	if (NULL == pDL)
	{
		return ILLEGAL;
	}

	//��ʼ��
	pDL->pHead = NULL;
	pDL->pCur = NULL;
	pDL->iCount = 0;

	return TRUE;
}

WORD DoubleListClear(List_t *pDL)
{
	List_Node *pTemp = NULL;
	//�ж��Ƿ�Ϸ�
	if (NULL == pDL)
	{
		return ILLEGAL;
	}

	pDL->pCur = pDL->pHead;

	//�����������
	while (NULL != pDL->pCur)
	{
		pTemp = pDL->pCur;
		pDL->pCur = pDL->pCur->pNext;
		free(pTemp);
		pTemp = NULL;
	}
	return TRUE;
}

WORD DoubleListHead(List_t *pDL, int iInSize, void (*InputElem)(elemType *), WORD (*EqualElem)(elemType *, elemType *))
{
	List_Node *pTemp;
	List_Node *pTemp2;
	int i = 0;
	int iFlag = 0;
	elemType eData;
	//�ж��Ƿ�Ϸ�
	if (NULL == pDL)
	{
		return ILLEGAL;
	}
	//�жϽ������Ƿ���Ч
	if (iInSize <= 0)
	{
		return ERROR;
	}

	for (; i < iInSize; i++)
	{
		printf("��ӵ�����ĵ�%d��ֵ: \n", (i+1));
		InputElem(&eData);

		//�����жϲ����Ԫ���Ƿ�����Ѵ���
		pTemp2 = pDL->pHead;
		while(NULL != pTemp2)
		{
			iFlag = EqualElem(&eData, &(pTemp2->iData));
			if (TRUE == iFlag)
			{
				break;
			}
			pTemp2 = pTemp2->pNext;
		}
		if (TRUE == iFlag)
		{
			continue;
		}

		//�����ڴ�ռ�
		pDL->pCur = (List_Node *)malloc(sizeof(List_Node));
		if (NULL == pDL->pCur)
		{
			return OVERFLOW;
		}
		pDL->pCur->iData = eData;
		pDL->pCur->pNext = NULL;
		
		//����
		if(NULL != pDL->pHead)
		{
			pTemp = pDL->pHead;
			pTemp->pPrev = pDL->pCur;
			pDL->pCur->pNext = pTemp;
		}
		
		pDL->pHead = pDL->pCur;
		pDL->iCount++;
	}
	printf("\n�ɹ����뵽�����Ԫ�ظ���Ϊ: %d", pDL->iCount);

    return TRUE;
}

WORD DoubleListLast(List_t *pDL, int iInSize, void (*InputElem)(elemType *), WORD (*EqualElem)(elemType *, elemType *))
{
	List_Node *pTemp = NULL;
	List_Node *pTemp1 = NULL;
	List_Node *pTemp2 = NULL;
	int i = 0;
	int iFlag = 0;
	elemType eData;
	//�ж��Ƿ�Ϸ�
	if (NULL == pDL)
	{
		return ILLEGAL;
	}

	//�жϽ������Ƿ���Ч
	if (iInSize <= 0)
	{
		return ERROR;
	}

	for (; i < iInSize; i++)
	{
		printf("��ӵ�����ĵ�%d��ֵ: \n", (i+1));
		InputElem(&eData);

		//�����жϲ����Ԫ���Ƿ�����Ѵ���
		pTemp = pDL->pHead;
		while(NULL != pTemp)
		{
			iFlag = EqualElem(&eData, &(pTemp->iData));
			if (TRUE == iFlag)
			{
				break;
			}
			pTemp = pTemp->pNext;
		}
		if (TRUE == iFlag)
		{
			continue;
		}
		
		//�����ڴ�ռ�
		pTemp1 = (List_Node *)malloc(sizeof(List_Node));
		if (NULL == pTemp1)
		{
			return OVERFLOW;
		}
		pTemp1->iData = eData;
		pTemp1->pNext = NULL;

		//ͷ���
		pDL->pCur = pDL->pHead;
		
		//����
		if (NULL != pDL->pCur)
		{
			while(NULL != pDL->pCur)
			{
				pTemp2 = pDL->pCur;
				pDL->pCur = pDL->pCur->pNext;
			}
			pTemp1->pPrev = pTemp2;
			pTemp2->pNext = pTemp1;
		}
		else
		{
			pDL->pHead = pTemp1;
		}
		
		pDL->iCount++;
	}

	printf("\n�ɹ����뵽�����Ԫ�ظ���Ϊ: %d", pDL->iCount);
	
    return TRUE;
}

WORD DoubleListInsert(List_t *pDL, int iPosition, elemType *peInValue, WORD (*EqualElem)(elemType *, elemType *))
{
	List_Node *pTemp = NULL;
	List_Node *pTemp1 = NULL;
	List_Node *pTemp2 = NULL;
	int i = 0;
	int iFlag = 0;

	//�ж��Ƿ�Ϸ�
	if (NULL == pDL)
	{
		return ILLEGAL;
	}

	//��֤λ���Ƿ���Ч
	if (iPosition < 1 || iPosition > pDL->iCount)
	{
		return ISVALID; 
	}

	//ȡ��ͷ���
	pTemp = pDL->pHead;
	while (NULL != pTemp)
	{
		iFlag = EqualElem(peInValue, (&pTemp->iData));
		if (TRUE == iFlag)
		{
			return EXIST;
		}
		pTemp = pTemp->pNext;
	}

	//����ռ�
	pDL->pCur = (List_Node *)malloc(sizeof(List_Node));
	if (NULL == pDL->pCur)
	{
		return OVERFLOW;
	}
	pDL->pCur->iData = *peInValue;
	pDL->pCur->pNext = NULL;

	if (TRUE == DoubleListEmpty(pDL))
	{
		pDL->pHead = pDL->pCur;
	}
	else if(FALSE == DoubleListEmpty(pDL))
	{
		//�ٽ�pTemp1��ֵΪͷ���
		pTemp1 = pDL->pHead;

		//��ֵ����һ��λ��
		if (1 == iPosition)
		{
			pDL->pCur->pNext = pDL->pHead;
			pDL->pHead->pPrev = pDL->pCur;
			pDL->pHead = pDL->pCur;
		}
		//�����һ��λ�ò�ֵ
		else if (pDL->iCount == iPosition)
		{
			while(NULL != pTemp1)
			{
				pTemp2 = pTemp1;
				pTemp1 = pTemp1->pNext;
			}
			pTemp2->pNext = pDL->pCur;
			pDL->pCur->pPrev = pTemp2;
		}
		else
		{
			//�ҵ�����λ��
			for (i = iPosition - 1; i > 0; i--)
			{
				pTemp1 = pTemp1->pNext;
			}
			pTemp1->pPrev->pNext = pDL->pCur;
			pDL->pCur->pPrev = pTemp1->pPrev;
			pDL->pCur->pNext = pTemp1;
			pTemp1->pPrev = pDL->pCur;
		}
	}
	else
	{
		return ILLEGAL;
	}

	pDL->iCount++;
	return TRUE;
}

WORD DoubleListValueFind(List_t *pDL, elemType *peInValue, int *piOutPosition, WORD (*EqualElem)(elemType *, elemType *))
{
	int iFlag = 0;
	int iPostion = 1;
	//�ж��Ƿ�Ϸ�
	if (NULL == pDL)
	{
		return ILLEGAL;
	}

	//ȡ��ǰ���Ϊͷ���
	pDL->pCur = pDL->pHead;

	while (NULL != pDL->pCur)
	{
		iFlag = EqualElem(peInValue, &pDL->pCur->iData);
		if (TRUE == iFlag)
		{
			*piOutPosition = iPostion;
			return EXIST;
		}
		iPostion++;
		pDL->pCur = pDL->pCur->pNext;
	}

	return NOEXIST;
}

WORD DoubleListEmpty(List_t *pDL)
{
	//�ж��Ƿ�Ϸ�
	if (NULL == pDL)
	{
		return ILLEGAL;
	}

	if (NULL == pDL->pHead)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

WORD DoubleListLength(List_t *pDL)
{
	int iLength;
	//�ж��Ƿ�Ϸ�
	if (NULL == pDL)
	{
		return ILLEGAL;
	}

	iLength = pDL->iCount;
	return iLength;
}

WORD DoubleListDisplay(List_t *pDL, void(*OutPut)(elemType *))
{
	int iCount = 0;
	//�ж��Ƿ�Ϸ�
	if (NULL == pDL)
	{
		return ILLEGAL;
	}
	//�ж��Ƿ�Ϊ��
	if (TRUE == DoubleListEmpty(pDL))
	{
		return ERROR;
	}

	pDL->pCur = pDL->pHead;
	while(NULL != pDL->pCur)
	{
		iCount++;
		printf("\n��%d��Ԫ�أ�", iCount);
		//��ӡ����ǰ���
		OutPut(&pDL->pCur->iData);

		pDL->pCur = pDL->pCur->pNext;
	}

	return TRUE;
}

WORD DoubleListDelete(List_t *pDL, int iPosition, elemType *peOutValue)
{
	int i;

	//�ж��Ƿ�Ϸ�
	if (NULL == pDL)
	{
		return ILLEGAL;
	}
	//�ж��Ƿ�Ϊ��
	if (TRUE == DoubleListEmpty(pDL))
	{
		return ERROR;
	}
	//��֤λ���Ƿ���Ч
	if (iPosition < 1 || iPosition > pDL->iCount)
	{
		return ISVALID; 
	}
	//��ɾ��λ��Ϊ1ʱ
	if (1 == iPosition)
	{
		pDL->pCur = pDL->pHead;
		pDL->pHead = pDL->pCur->pNext;
		pDL->iCount--;

		*peOutValue = pDL->pCur->iData;
		free(pDL->pCur);
		pDL->pCur = NULL;
	}
	//ɾ��λ�ò�Ϊ1
	else
	{
		List_Node *pTemp = NULL;

		pDL->pCur = pDL->pHead;
		for (i = iPosition - 1; i > 0; i--)
		{
			pDL->pCur = pDL->pCur->pNext;
		}
		
		pTemp = pDL->pCur->pNext;
		pTemp->pPrev = pDL->pCur->pPrev;
		pDL->pCur->pPrev->pNext = pTemp;
		pDL->iCount--;

		*peOutValue = pDL->pCur->iData;
		free(pDL->pCur);
		pDL->pCur = NULL;
	}
	return TRUE;
}