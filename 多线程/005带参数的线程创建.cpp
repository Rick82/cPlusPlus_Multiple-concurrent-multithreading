#include <iostream>
#include <string>
#include<thread>

using namespace std;



//�̺߳���
//void MyPrint(int&i,char*pMyBuf)
void MyPrint(int&i,const string&pMyBuf)
//�������ʹ������,������MyBuf��������ʲôʱ��ת��Ϊstring�ģ���
//ȷʵ���ڵ�mian()����ִ�й�����ϣ��Ż���ַ�����MyBufת��Ϊstring
{
	cout << i << endl;
	cout << pMyBuf << endl;
	return;
}

int main(void)
{
	//������ʱ������Ϊ�������
	int  myvar = 10;
	int& myvarReference = myvar;
	char mybuf[] = "���ǲ����ַ���";
	//��һ���������̵߳�ִ�к�����ʣ�µ��Ƕ�������б�
	//thread myThread(MyPrint, myvar, mybuf);
	thread myThread(MyPrint, myvar, string(mybuf));
	//������ַ�����MyBuf����ת��Ϊ��ʱ��string�����ٽ��в�������

	//myThread.join();
	//�����̺߳����̷߳����ʱ�򣬴��ݵĲ���int&i�����ã��Ḵ�ƣ����᲻�����
	//���ᣬд�Ĳ�����Ȼ�����ã����ǻḴ��һ��.���ǵڶ���ָ��������������
	//ʹ��ָ��Ĭ��ִ�е���ǳ����
	myThread.detach();
	cout << "�������̵߳�ִ��" << endl;

	system("pause");
	return 0;
}

