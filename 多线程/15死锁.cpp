#include <iostream>
#include <string>
#include<thread>
#include <vector>
#include<list>
#include<mutex>
using namespace std;

//�ó�Ա������Ϊ�̳߳�ʼ������

class A
{
public:
	//���յ�����Ϣ�뵽һ�����У����̵߳���������
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 10000; i++)
		{
			cout << "inMsgQueue����һ��Ԫ��" << i << endl;

			my_mutex1.lock();//����һ����������һ����
			//��������һ�����ţ����ܱ��治ͬ�Ĵ���
			my_mutex2.lock();
			//Ҳ����ʹ��lock_guard()
			//lock_guard<mutex> mylock1(my_mutex1);

			msgRecvQueue.push_back(i);//�����������i�����յ�����ҵ�����
			my_mutex1.unlock();
			my_mutex2.unlock();
		}
	}
	//���������ݺ����ķ�װ����
	bool outMsgprocess(int&command)
	{
		my_mutex2.lock();
		my_mutex1.lock();
		if (!msgRecvQueue.empty())
		{
			//��Ϣ���в�Ϊ��
			int command = msgRecvQueue.front();//���ص�һ��Ԫ��
			msgRecvQueue.pop_front();//�Ƴ���һ��Ԫ��
			my_mutex1.unlock();
			my_mutex2.unlock();
			return true;
		}
		my_mutex1.unlock();
		my_mutex2.unlock();
		return false;
		//���з�֧��Ҫ��unlock()���������ڱ���������unlock()
		
	}


	//�����ݴ���Ϣ������ȡ�������߳�
	void outMsgRecvQueue()
	{
		int command = 0;
		for (int i = 0; i < 10000; i++)
		{
			bool result = outMsgprocess(command);
			if (result == true)
			{
				cout << "ȡ��Ϣ����ִ�гɹ�" << command << endl;
			}
			else
			{
				cout << "��Ϣ�����е���ϢΪ��" << i << endl;
			}
		}

		cout << endl;
	}
private:
	list<int>msgRecvQueue;//�������������ҷ��͹���������
	//����һ���������ĳ�Ա����
	mutex my_mutex1;
	mutex my_mutex2;
};


int main(void)
{
	A myobj;
	thread myOutMsgObj(&A::outMsgRecvQueue, &myobj);//�ڶ��������ò��ܱ�֤�߳����õ���ͳһ������
	thread myInMsObj(&A::inMsgRecvQueue, &myobj);
	myOutMsgObj.join();
	myInMsObj.join();

	cout << "main�߳�" << endl;//���ִ����һ�䣬�����߳��˳�
	system("pause");
	return 0;
}
/*
*������������������Ҳ�������������������������߳�	A B��ʹ����������������
*�߳�Aִ�е�ʱ��lock a�ɹ���Ȼ����ȥ������һ����b��
*�������������л����߳�B������b����Ȼ����a��,����a���Ѿ���ʹ�ã�
*�߳� A B������Ҫ�Է��Ľ���������ȴ���
*�߳�A���߳�B����ȴ��Է�������(������˳���෴)���������߳�������˳����ͬ��
*�����������
*
*������ʾ��
*
*std::lock()����ģ�壬
*������һ����ס���������������ϵĻ��������������ٶ���߳��У�
*��Ϊ����˳�����⵼�µ������ķ������������������һ��û���ţ��������������
*�ȵ����л��������������Ż����ִ�С��������ȫ���������Ͱ��Ѿ���ס�Ķ����ͷŵ���
*Ҳ����˵ֻ��ȫ�����Ų�������
*/

