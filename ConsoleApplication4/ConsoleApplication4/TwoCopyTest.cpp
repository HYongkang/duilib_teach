#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

/*DeepCopy  and  Shallow Copy Test*/

class Rect
{
public:
	Rect()      // 构造函数，p指向堆中分配的一空间
	{
		p = new int(100);
	}

	//没有以下深拷贝构造函数运行会报错：默认为浅拷贝——两个对象的析构函数将对同一个内存空间释放两次
	Rect(const Rect& r)
	{
		width = r.width;
		height = r.height;
		p = new int(100);    // 为新对象重新动态分配空间
		*p = *(r.p);
	}

	void ShowRect() {
		cout << "Width:" << width << endl;
		cout << "Height:" << height << endl;
	}

	~Rect()     // 析构函数，释放动态分配的空间
	{
		if (p != NULL)
		{
			delete p;
		}
	}
private:
	int width=100;
	int height=100;
	int *p;     // 一指针成员
};

int main()
{
	Rect rect1;
	cout << "Rect1的Width和Height分别为：" << endl;
	rect1.ShowRect();

	cout << "Rect2将拷贝Rect1" << endl;

	Rect rect2(rect1);   // 复制对象
	cout << "Rect2的Width和Height分别为：" << endl;
	rect2.ShowRect();

	return 0;
}