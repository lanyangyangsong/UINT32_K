// UINT32_K.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

/************************************************************************************
给定正整数 K，你需要找出可以被 K 整除的、仅包含数字 1 的最小正整数 N。
返回 N 的长度。如果不存在这样的 N，就返回 -1。
示例 1：
输入：1
输出：1
解释：最小的答案是 N = 1，其长度为 1。
示例 2：
输入：2
输出：-1
解释：不存在可被 2 整除的正整数 N 。
示例 3：
输入：3
输出：3
解释：最小的答案是 N = 111，其长度为 3。

提示：

1 <= K <= 10^5
*************************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef _DEBUG
#define SW_PRINT printf
#else
#define SW_PRINT //
#endif

#define MAX_RETRY_CNT (10)
#define MAX_UINT32_NUM (0xFFFFFFFF)

typedef unsigned int UINTSW;

const UINTSW MIN_NUM = 1;
const UINTSW MAX_NUM = 10000;

#define SW_LOG(str) 1


typedef struct T_RESULT
{
	UINTSW k;
	int length;
} RESULT;


#if SW_LOG("输入模块")

UINTSW Get_Input(void)
{
	UINTSW input = 0;
	UINTSW retryCnt = 0;
	char temp = '\0';
	printf("请输入一个正整数（%u - %u）：", MIN_NUM, MAX_NUM);

	while ((input < MIN_NUM) || (input > MAX_NUM) || (retryCnt < MAX_RETRY_CNT))
	{
		if (retryCnt != 0)
		{
			printf("输入参数不对！请重新输入：<错误次数：%u 剩余输入次数：%u>", retryCnt, MAX_RETRY_CNT - retryCnt);
		}

		while (!scanf_s("%d", &input))
		{
			temp = getchar();
			SW_PRINT("缓冲区字符为：%c\n", temp);
			//	fflush(stdin);
			continue;
		}

		if ((input >= MIN_NUM) && (input <= MAX_NUM))
		{
			return input;
		}
		retryCnt++;
	}

	return  (MAX_NUM + 1);
}

bool Check_Input(UINTSW input)
{
	SW_PRINT("你最终输入的数字为 %u\n", input);

	if (input == MAX_NUM + 1)
	{
		printf("你的输入错误！退出程序！\n");
		return false;
	}
	return true;
}

#endif


#if SW_LOG("获取输出数据方法一")

bool Check_Num_Have_1(UINTSW num)
{
	if (num == 1)
	{
		return true;
	}
	else if (num < 10)
	{
		return false;
	}
	else
	{
		int yushu = num % 10;
		int shang = num / 10;
		return (Check_Num_Have_1(yushu) && Check_Num_Have_1(shang));
	}

	return false;
}

UINTSW Calc_Length(UINTSW input)
{
	UINTSW data = input;
	if (data < 10)
	{
		return 1; /* 小于10为1位数 */
	}
	else
	{
		UINTSW next = data / 10;
		return (1 + Calc_Length(next));
	}
}

bool Get_Right_Num1(UINTSW input, RESULT *result)
{
	int data = input;

	if (result == NULL)
	{
		return false;
	}

	if (data % 2 == 0)
	{
		SW_PRINT("找不到这样的正整数K!\n");
		result->k = 0;
		result->length = -1;
		return false;
	}
	for (UINTSW i = data; i <= MAX_UINT32_NUM; )
	{
		if (Check_Num_Have_1(i))
		{
			if (i % data == 0) {
				int length = Calc_Length(i);
				SW_PRINT("最小正整数K为：%u， 宽度为：%u.\n", i, length);
				result->k = i;
				result->length = length;
				return true;
			}
			else
			{
				if (i <= ((MAX_UINT32_NUM -1)/ 10 ))
				{
					i *= 10;
					i++;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			i++;
		}
	}

	SW_PRINT("找不到这样的正整数K!\n");
	result->k = 0;
	result->length = -1;
	return false;
}

#endif


#if SW_LOG("获取输出数据方法二")

typedef struct T_DATA
{
	UINTSW data;
	UINTSW dataLength;
	T_DATA *pNext;
}DATA;

bool Build_Data(DATA *dataHead)
{
	if (dataHead == NULL)
	{
		SW_PRINT("申请内存失败!\n");
		return false;
	}

	UINTSW data = 1; /* 第一个数据 */
	UINTSW dataLength = 1; /* 第一个数据长度 */
	DATA *pLast = dataHead;
	
	while(data <= MAX_UINT32_NUM)
	{		
		DATA *pData = (DATA *)malloc(sizeof(DATA));
		if (pData == NULL)
		{
			SW_PRINT("申请内存失败!\n");
			return false;
		}
		pData->data = data;
		pData->dataLength = dataLength;
		pData->pNext = NULL;
		pLast->pNext = pData;
		pLast = pData;

		data *= 10;
		data++;
		dataLength++;
	}

	return true;
}

void Print_Data(DATA *dataHead)
{
	if (dataHead == NULL)
	{
		SW_PRINT("STRUCT DATA is NULL!\n");
		return;
	}

	DATA *pData = dataHead->pNext;

	while (pData != NULL)
	{
		SW_PRINT("第 %u 个数据为 %u ,它的宽度为 %u \n", pData->dataLength, pData->data, pData->dataLength);
		pData = pData->pNext;
	}
	return;
}

void Destroy_Data(DATA *dataHead)
{
	DATA *pData = dataHead;

	if (pData == NULL)
	{
		SW_PRINT("STRUCT DATA is already destroyed!\n");
	}

	while (pData != NULL)
	{
		DATA *pNext = pData->pNext;
		free(pData);
		pData = pNext;
	}

	return;
}

bool Get_Right_Num2(UINTSW input, RESULT *result)
{
	DATA dataHead = { 0 };
	int length = -1;

	if (result == NULL)
	{
		return false;
	}

	bool creatData = Build_Data(&dataHead);
	
	if (!creatData)
	{
		SW_PRINT("创建数据失败！\n");
		result->k = 0;
		result->length = -1;
		return false;
	}

	DATA *pData = dataHead.pNext;
	while (pData != NULL)
	{
		if (pData->data % input == 0)
		{
			SW_PRINT("最小正整数K为：%u， 宽度为：%u.\n", pData->data, pData->dataLength);
			length = pData->dataLength;
			result->k = pData->data;
			result->length = length;
			break;
		}
		pData = pData->pNext;
	}

	//Print_Data(&dataHead);

	pData = dataHead.pNext;
	Destroy_Data(pData);
	dataHead.pNext = NULL;

	if (length == -1)
	{
		SW_PRINT("找不到这样的正整数K!\n");
		result->k = 0;
		result->length = -1;
		return false;
	}

	return true;
}

#endif


int main()
{
#if 0
	UINTSW input = Get_Input();

	if (!Check_Input(input))
	{
		return -1;
	}
#endif

	RESULT resultFunc1 = { 0 };
	RESULT resultFunc2 = { 0 };

#if 1
	for (int i = 1; i <= 50000; i++)
	{
		bool res1 = Get_Right_Num1(i, &resultFunc1);
		bool res2 = Get_Right_Num2(i, &resultFunc2);	

		if (res1 != res2)
		{
			printf("当输入数据为 %u 时，", i);
			printf("结论不一致！方法一的K为：%u, 宽度为： %d, 方法二的K为：%u, 宽度为： %d.\n", resultFunc1.k, resultFunc1.length, resultFunc2.k, resultFunc2.length);
		}
		else 
		{
			SW_PRINT("当输入数据为 %u 时，结论一致!\n", i);
			if (resultFunc1.length != -1)
			{
				SW_PRINT("K为：%u, 宽度为： %d.\n", resultFunc1.k, resultFunc1.length);
			}
		}
	}
#endif

	//int K = Get_Right_Num(input);

	system("pause");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件