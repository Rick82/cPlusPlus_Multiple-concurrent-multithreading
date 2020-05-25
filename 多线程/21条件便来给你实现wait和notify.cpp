#include <iostream>
#include <string>
#include<thread>
#include <vector>
#include<list>
#include<mutex>
#include <condition_variable>//��Ҫ�������������ᱨ�����Ͳ�����
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

			unique_lock<mutex> myGuard1(my_mutex1);
			msgRecvQueue.push_back(i);
			//my_cond.notify_one();//���ǳ��԰�wait�̻߳��ѣ�ִ�к�wait�����ѣ����������
			my_cond.notify_all();
		}
	}
	//���������ݺ����ķ�װ����
	//bool outMsgprocess(int&command)
	//{
	//	//���˫�ؼ��---˼�����ܷ��Ϊ�����ݲ�Ϊ�յ�ʱ��֪ͨ����
	//	if (!msgRecvQueue.empty())
	//	{
	//		unique_lock<mutex> myGuard1(my_mutex1);
	//		if (!msgRecvQueue.empty())
	//		{
	//			//��Ϣ���в�Ϊ��
	//			command = msgRecvQueue.front();//���ص�һ��Ԫ��
	//			msgRecvQueue.pop_front();//�Ƴ���һ��Ԫ��
	//			return true;
	//		}
	//	}
	//	

	//	return false;
	//	//���з�֧��Ҫ��unlock()���������ڱ���������unlock()
	//}

public:
	//�����ݴ���Ϣ������ȡ�������߳�
	void outMsgRecvQueue()
	{
		int command = 0;
		while (true)
		{
			unique_lock<mutex>sbguard1(my_mutex1);
			my_cond.wait(sbguard1,[this]
			{
				if (!msgRecvQueue.empty())
				{
					return true;
				}
				return  false;
			});
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			sbguard1.unlock();//��Ϊunique_lock������ԣ�������ʱ����
			//������һЩ����Ķ�����������ҳ鿨�Ȳ�����������
			//�����������ڴ���һ��������Ҫһ��ʱ�䣬�����ǿ���wait()�ȴ�����ʱ���
			//notify_one()������û�����á�Ҳ����˵notify_one()��һ�����Ի���wait����
		}
		/*
		 * wait()�����ȴ�һ������
		 * �ڶ�������lambad���ʽ����ֵ��false����ôwait�������������������������У�˯�ߣ���
		 * ������������������notify_one()Ϊֹ��û�еڶ��������ȼ���false��
		 * 
		 * ����ڶ�������ֵ��true������ôwaitֱ�ӷ���
		 * �������߳�ʹ��notefy_one()����wait�ٴγ��Ի�ȡ���������������ȡ�����߳�
		 * ��������ȴ���ȡ�������ȡ������wait�ͼ���ִ��b
		 * ��b������
		 *		���wait�еڶ����������ͣ�lambda�������ж�������ʽ��������ʽΪfalse���ͽ�����������
		 *		���½���˯�ߣ��ȴ��ٴα�notefy_one()����
		 *		�����ʾʽΪtrue����ô����ֱ������������ʱ�������������š�
		 *		����ֻҪ���ߵ����ﻥ����һ�������ŵġ�
		 *	���waitû�еڶ������������������ߡ�
		 * 
		 * 
		 */
		
	}

		/*cout << endl;*/
private:
	list<int>msgRecvQueue;//�������������ҷ��͹���������
	//����һ���������ĳ�Ա����
	std::mutex my_mutex1;
	std::condition_variable my_cond;//2017���Բ�����()
	//����һ����������
};


int main(void)
{
	A myobj;
	//������һ���̱߳�����
	thread myOutMsgObj(&A::outMsgRecvQueue, &myobj);//�ڶ��������ò��ܱ�֤�߳����õ���ͬһ������
	thread myOutMsgObj2(&A::outMsgRecvQueue, &myobj);

	thread myInMsObj(&A::inMsgRecvQueue, &myobj);
	myOutMsgObj.join();
	myInMsObj.join();
	myOutMsgObj2.join();

	cout << "main�߳�" << endl;//���ִ����һ�䣬�����߳��˳�
	system("pause");
	return 0;
}
/*
 *�������� std::condition_variable 
 *��������--�����߳��У����߳�A�ȴ��������㣬�߳�Bר������Ϣ����������Ϣ
 *��һ����������ص��࣬˵���˾��ǵȴ��������㣬��Ҫ�ͻ��������ʹ��
 *
 *
 *wait  ()--��Ҫ����һ������������˯�߽���
 *notify_one()--����wait()���̣����ǲ��ܱ�֤һ���ܻ���
 *
 *����˼����
 *�������߳��õ����Ĵ�����һ����Ҳ��˵���ݴ���������ô��
 *		��������̻߳���Լ�����ݵĴ���
 *		ʵ�ʵĻ����У������ҵĲ���һֱ�ò���ִ���ǲ����Եġ�
 *
 *�ܶ๫˾ϲ��Ҫ�����ˣ��������ܼӰ࣬���ڼ򵥵����⣬��������û���⡣
 *Խ�����ѵ����⣬Խ��Ҫ�����ˣ�����ḻ�����⣬���԰�������ʧ����ѿ֮�С�
 *��Ҫ��λһ��Ҫʹ�þ���ḻ����
 *
 *notify_all()����
 *		notify_one()ֻ��֪ͨһ���߳�,Ҫ��֪ͨ����߳̾���Ҫʹ��notify_one()
*/

