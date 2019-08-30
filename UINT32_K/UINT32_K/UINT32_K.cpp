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

int Get_Right_Num(UINTSW input)
{
	if (input % 2 == 0)
	{
		printf("找不到这样的正整数K!\n");
		return -1;
	}
	for (UINTSW i = input; i <= MAX_UINT32_NUM; )
	{
		if (Check_Num_Have_1(i))
		{
			if (i % input == 0) {
				printf("最小正整数K为： %u\n", i);
				return i;
			}
			else
			{
				if (i <= MAX_UINT32_NUM / 10 - 1)
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

	printf("找不到这样的正整数K!\n");
	return -1;
}

int main()
{
	UINTSW input = Get_Input();

	if (!Check_Input(input))
	{
		return -1;
	}

	int K = Get_Right_Num(input);

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