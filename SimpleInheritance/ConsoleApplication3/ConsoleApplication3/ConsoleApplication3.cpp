// ConsoleApplication3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "string.h"
#include <iostream>
using namespace std;

class IAnimal {
public:
	virtual void Walk() = 0;
	virtual void Voice() =0;

};

class Human :public IAnimal{
public:
	virtual void Walk() { printf("Human: walk\n"); }
	virtual void Voice() { printf("Human: speak\n");}
};

class Man :public Human{
public:
	void Walk() { printf("Man: walk_fast\n"); }
	void Voice() { printf("Man: speak_loudly\n"); }
};

class Woman :public Human {
public:
	void Walk() { printf("Woman: walk_slow\n"); }
	void Voice() { printf("Woman: speak_softly\n");}
};

int main()
{
	Human human;
	Man man;
	Woman woman;

	human.Walk();
	human.Voice();
	//IAnimal* animal = &human;
	man.Walk();
	man.Voice();

	woman.Walk();
	woman.Voice();
    //std::cout << "Hello World!\n"; 
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
