#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

/*ʵ�顪�����ÿ������캯�����������Σ�*/

class CExample {
private:
	string str1;
public:
	//���캯��
	CExample(string str2)
	{
		str1 = str2;
	}

	//�������캯��
	CExample(const CExample& C)
	{
		str1 = C.str1;
	}

	//һ�㺯��
	void Show()
	{
		cout << str1 << endl;
	}
};

//ȫ�ֺ���,������ֵ���ݵķ�ʽ�Ӻ�������
CExample ObjectValueOut()
{
	CExample strTemp("Hellow New World!");
	return strTemp;
}

//ȫ�ֺ���,������ֵ���ݵķ�ʽ���뺯������
void ObjectValueIn(CExample strTemp)
{
	strTemp.Show();//��������еı���ֵ
}

//int main()//ʵ�顪�����ÿ������캯�����������Σ�
//{
//	string str = "Hellow World!";
//	CExample A(str);//��ֵ������ÿ������캯����ֻ����ù��캯��
//	CExample B = A; //����������ÿ������캯������ϵ㷢����һ����û�е��ù��캯��������ֱ�ӵ��ÿ������캯����������������
//	CExample C(A); //���ÿ������캯�������Σ�1��������Ҫͨ������һ��������г�ʼ��
//	CExample D(B); //����B�Ƿ񿽱�A
//
//	B.Show();//���B�е�˽�г�Ա����
//	C.Show();//���C�е�˽�г�Ա����
//	D.Show();//���D�е�˽�г�Ա����
//
//	
//	CExample strTemp1= ObjectValueOut();//���ÿ������캯�������Σ�2�����������ֵ���ݵķ�ʽ�Ӻ�������
//	strTemp1.Show();//���temp�����еı���
//
//	//���ÿ������캯�������Σ�3��������ֵ���ݵķ�ʽ���뺯������
//	CExample strTemp2("Hellow New World Again!");
//	ObjectValueIn(strTemp2);//�������,�ں��������
//
//
//	return 0;
//}
