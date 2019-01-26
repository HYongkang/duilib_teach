#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

/*DeepCopy  and  Shallow Copy Test*/

class Rect
{
public:
	Rect()      // ���캯����pָ����з����һ�ռ�
	{
		p = new int(100);
	}

	//û������������캯�����лᱨ��Ĭ��Ϊǳ�����������������������������ͬһ���ڴ�ռ��ͷ�����
	Rect(const Rect& r)
	{
		width = r.width;
		height = r.height;
		p = new int(100);    // Ϊ�¶������¶�̬����ռ�
		*p = *(r.p);
	}

	void ShowRect() {
		cout << "Width:" << width << endl;
		cout << "Height:" << height << endl;
	}

	~Rect()     // �����������ͷŶ�̬����Ŀռ�
	{
		if (p != NULL)
		{
			delete p;
		}
	}
private:
	int width=100;
	int height=100;
	int *p;     // һָ���Ա
};

int main()
{
	Rect rect1;
	cout << "Rect1��Width��Height�ֱ�Ϊ��" << endl;
	rect1.ShowRect();

	cout << "Rect2������Rect1" << endl;

	Rect rect2(rect1);   // ���ƶ���
	cout << "Rect2��Width��Height�ֱ�Ϊ��" << endl;
	rect2.ShowRect();

	return 0;
}