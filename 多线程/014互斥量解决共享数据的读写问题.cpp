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
			
			my_mutex.lock();
			msgRecvQueue.push_back(i);//�����������i�����յ�����ҵ�����
			my_mutex.unlock();
		}
	}
	////���������ݺ����ķ�װ����
	//bool outMsgprocess(int&command)
	//{
	//	my_mutex.lock();
	//	if (!msgRecvQueue.empty())
	//	{
	//		//��Ϣ���в�Ϊ��
	//		int command = msgRecvQueue.front();//���ص�һ��Ԫ��
	//		msgRecvQueue.pop_front();//�Ƴ���һ��Ԫ��
	//		my_mutex.unlock();
	//		return true;
	//	}
	//	my_mutex.unlock();
	//	return false;
	//	//���з�֧��Ҫ��unlock()���������ڱ���������unlock()
	//	
	//}


	//���������ݺ����ķ�װ������ʹ��lock_guard()
	bool outMsgprocess(int&command)
	{
		lock_guard<mutex> myguard(my_mutex);//myguard�������������
		//lock_guard�Ĺ��캯������ִ����mutex::lock()��������myguard�ֲ�����
		//������ʱ��ִ��unlock()������
		//my_mutex.lock();
		if (!msgRecvQueue.empty())
		{
			//��Ϣ���в�Ϊ��
			int command = msgRecvQueue.front();//���ص�һ��Ԫ��
			msgRecvQueue.pop_front();//�Ƴ���һ��Ԫ��
			//my_mutex.unlock();
			return true;
		}
		//my_mutex.unlock();
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
			if (result==true)
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
	mutex my_mutex;
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
*�е��߳�д���ݣ��е��߳�д���ݣ���ô��Ҫ����Ĵ���,
*��򵥵Ĵ�����Ƕ���ʱ����д��д��ʱ���ܶ���ֻ����һ���߳�д
*Ҳ����ֻ����һ���߳�ռ�����ݡ���������д���ݺͶ����ݶ��Ƿֺܶಽ��
*�磺�ƶ�ָ��ȡ����������л��ᵼ�ºܶ��������鷢����
*
*
*���������
*���ݹ����ʵ������Ʊ��ʣ��Ʊ������Ҫ�����еĿͻ��˽��й������Ҳ���֮��
*Ҫԭ���Ե�
*
*�������ݵı�����������
*����Ҫ��һ��������Ϸ�����������������̣߳�һ���߳��ռ���������������д��һ��������
*�ڶ����̴߳Ӷ�����ȡ����ҷ������������ִ����ҵĶ�����
*���������ֱ�ʾ��ҷ��͹��������ʹ��list���档��Ƶ���İ�˳���ȡ����Ч�ʸ�--˫���б�����
*
*���ж�����д�������̣߳�������п��ƣ���ֻ֤��һ���߳̽��ж�����д���ɡ�
*���룺����������--���̹߳������ݵı�������
*
*------------------------------------------------------------------------------------
*�����������ݣ�����ʱ���ô���ѹ���������ס������������������ݵ��̵߳ȴ�������Ȼ����ס������
*
*������(mutex)�Ļ�������--��ʵ����һ�����������һ����������̳߳�����lock()��Ա����������
*ֻ��һ���߳̿��Խ����ɹ����ɹ��ı�־�Ƿ����ˣ����û�гɹ�����ô�߳̾ͻ���������ȴ���ס��ִ�����
*��unlock()������
*��������Ӱ��Ч�ʡ�������Сû������
*(1)����ͷ�ļ�#include<mutex>
*(2)��lock()����unlock()Ҫ�ɶ�ʹ�ã����ܶ�Ҳ�����١��ǳɶԵ��ûᵼ�´��벻�ȶ�
*(3)�м������ھ�Ҫ�м���unlock()�����ִ���ǳ������Ų顣����lock_guard()���Զ��������ǽ�����
*	����������ָ�룬���Զ��ͷ�
*	
*��4������lock_guard()����ȡ��lock() and unlock()��ֻ��Ҫʹ��lock_guard()���ɡ�����ʹ��{}
*��Լ��lock_guard()�������������ڡ�
*
*/

