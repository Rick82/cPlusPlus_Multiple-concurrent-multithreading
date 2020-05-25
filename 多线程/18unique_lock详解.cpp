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
	//ͨ����������һ��unique_lock����
	unique_lock<mutex> rtn_unique_lock()
	{
		unique_lock<mutex> temGuard(my_mutex1);
		return temGuard;//�Ӻ�������һ���ֲ���unique_lock�ǿ��Ե�
		//�ƶ����캯����ϵͳ��ʱ����һ����ʱ����
	}


	//���յ�����Ϣ�뵽һ�����У����̵߳���������
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 10000; i++)
		{
			cout << "inMsgQueue����һ��Ԫ��" << i << endl;
		
			//lock_guard<mutex> myGuard2(my_mutex1);
			//unique_lock<mutex> myGuard1(my_mutex1,try_to_lock);
			//����õ�����
			//if (myGuard1.owns_lock())
			//{
			//	msgRecvQueue.push_back(i);//�����������i�����յ�����ҵ�����

			//}
			//else
			//{
			//	cout << "û���õ���----------------------" << endl;
			//}


			//unique_lock<mutex> myGuard1(my_mutex1,defer_lock);
			//û�м�����my_mutex1
			//����֮�����Լ�����
			///*myGuard1.lock();*/
			//if (myGuard1.try_lock()==true)
			//{
			//	msgRecvQueue.push_back(i);
			//}
			//else
			//{
			//	cout << "û���õ���----------------------" << endl;
			//}


		/*	unique_lock<mutex> myGuard1(my_mutex1);
			mutex*ptx = myGuard1.release();
			msgRecvQueue.push_back(i);
			ptx->unlock();
*/


			//����Ȩת��
			unique_lock<mutex> myGuard1(my_mutex1);
			unique_lock<mutex> myGuard2(move(myGuard1));

			mutex*ptx = myGuard2.release();
			msgRecvQueue.push_back(i);
			ptx->unlock();



		}
	}
	//���������ݺ����ķ�װ����
	bool outMsgprocess(int&command)
	{
		
		//lock_guard<mutex> myGuard1(my_mutex1);
		unique_lock<mutex> myGuard1(my_mutex1);

		//˯��20s
		/*chrono::milliseconds dura(20000);
		this_thread::sleep_for(dura);*/

		if (!msgRecvQueue.empty())
		{
			//��Ϣ���в�Ϊ��
			command = msgRecvQueue.front();//���ص�һ��Ԫ��
			msgRecvQueue.pop_front();//�Ƴ���һ��Ԫ��
			return true;
		}
		
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
 *unique_lock()ȡ��lock_guard()
 *unique_lock��һ��ģ���࣬������һ���Ƽ�ʹ��lock_guard()����ȡ����lock(),unlock()����
 *Ĭ�ϲ�������lock_guard��unique����lock��ͬ
 *unique_lock֧�ָ���Ĳ���
 *adopt_lock:��ʾ�������Ѿ���lock�ˣ�������������ǰ��lock�ˣ�����ᱨ�쳣��
 *����Ҫ�ڹ��캯�����ٴ�lock�ˡ�
 *
 *try_to_lock()�����ǻ᳢����mutex��lockȥ����mutex���������û�������ɹ���
 *���������أ�����ȴ���ס��(ǰ�治����ס)
 *
 *default_lock,������lockס��
 *����û�и�mutex��������ʼ����һ��û�м�����mutex���������ĵ���һЩunique_lock
 *�ĳ�Ա������
 *lock()
 * unlock()--���Զ��������������м䴦��һЩ�ǹ�����룬Ȼ�������ϣ�
 * try_lock()--���Լ��������ɹ�Ҳ������
 * release()--�������������mutex����ָ�룬���ͷŹ���Ȩ
 *	Ҳ����unique_lock��mutex�����й�ϵ,���ԭ��mutex���ڼ���״̬������Ҫ�Լ��ӹܽ�����
 *	��Ҫ����release()��unlock()
 * �ò�����ʹ�ó�Ա�������ǿ��Եġ�
 *
 *Ϊʲô��ʱ����Ҫunlock()����Ϊ��lock��ס�Ĵ���Խ�٣���������Խ��
 *��ʱ��Ҳ����ס�Ĵ�����ٳ�Ϊ�������ȣ�����һ���ô�ϸ��������ס�Ĵ���Խ�٣�ִ��Ч��Խ�ߡ�
 *����Խ�֣�ִ�е�Ч��Խ�͡�����ѡ����ʵ������ǳ���Ա������ʵ��������
 *
 *
 *unique_lock()����Ȩ�Ĵ��ݣ�
 *ͨ�������unique_lockӦ�ú�һ��mutex�໥������
 unique_lock<mutex> myGuard1(my_mutex1);
 *myGuardӵ��my_mutex1������Ȩ����������Ȩ����ת�Ƹ�����unique_lock����
 *����Ȩ���ܸ��ơ�
 Ҳ����ͨ����������
 *
*/

