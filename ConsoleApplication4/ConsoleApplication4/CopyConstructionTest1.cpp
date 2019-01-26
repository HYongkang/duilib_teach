#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

/*实验——调用拷贝构造函数的三种情形：*/

class CExample {
private:
	string str1;
public:
	//构造函数
	CExample(string str2)
	{
		str1 = str2;
	}

	//拷贝构造函数
	CExample(const CExample& C)
	{
		str1 = C.str1;
	}

	//一般函数
	void Show()
	{
		cout << str1 << endl;
	}
};

//全局函数,对象以值传递的方式从函数返回
CExample ObjectValueOut()
{
	CExample strTemp("Hellow New World!");
	return strTemp;
}

//全局函数,对象以值传递的方式传入函数参数
void ObjectValueIn(CExample strTemp)
{
	strTemp.Show();//输出对象中的变量值
}

//int main()//实验——调用拷贝构造函数的三种情形：
//{
//	string str = "Hellow World!";
//	CExample A(str);//传值不会调用拷贝构造函数，只会调用构造函数
//	CExample B = A; //传入对象会调用拷贝构造函数，打断点发现这一步并没有调用构造函数，而是直接调用拷贝构造函数，拷贝对象即跳出
//	CExample C(A); //调用拷贝构造函数的情形：1、对象需要通过另外一个对象进行初始化
//	CExample D(B); //测验B是否拷贝A
//
//	B.Show();//输出B中的私有成员变量
//	C.Show();//输出C中的私有成员变量
//	D.Show();//输出D中的私有成员变量
//
//	
//	CExample strTemp1= ObjectValueOut();//调用拷贝构造函数的情形：2、对象对象以值传递的方式从函数返回
//	strTemp1.Show();//输出temp对象中的变量
//
//	//调用拷贝构造函数的情形：3、对象以值传递的方式传入函数参数
//	CExample strTemp2("Hellow New World Again!");
//	ObjectValueIn(strTemp2);//传入对象,在函数中输出
//
//
//	return 0;
//}
