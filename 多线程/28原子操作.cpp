#include <iostream>
#include <string>
#include<thread>
#include <future>

using namespace std;
//int g_mycout = 0;
//std::mutex g_mutex;//���뻥����������ӷ�����
//void mythread()
//{
//	for (int i = 0; i < 1000000;i++)
//	{
//		g_mutex.lock();
//		g_mycout++;
//		g_mutex.unlock();
//	}
//}

//
//std::atomic<int> g_mycout = 0;//��װ��һ������Ϊԭ�����͵�int���ҿ����������ͨ����һ��
//void mythread()
//{
//	for (int i = 0; i < 1000000; i++)
//	{
//		g_mycout++;//�Ѿ���һ��atomic�����ˣ��������ᱻ���
//		
//	}
//}

//�߳��˳����,������Ԫ�����
std::atomic<bool> isEnd = false;
void mythread()
{
	chrono::milliseconds dura(1000);
	std::this_thread::sleep_for(dura);
	while (isEnd==false)
	{
		//�߳�û���˳������Ա��߳̿������Լ�����������
		cout << "�߳�������" << endl;

	}
}
int main(void)
{
	thread	t1(mythread);
	thread	t2(mythread);
	

	chrono::milliseconds dura(4000);
	std::this_thread::sleep_for(dura);
	//sʹ��ԭ�Ӳ��������߳��Զ�����
	isEnd = true;

	t1.join();
	t2.join();
	cout << "g_mycout=" << isEnd<<endl;
	system("pause");
	return 0;
}

/*
 * ԭ�Ӳ���std::automic
 * ԭ�Ӳ�����������
 * ������������̱߳���У������������ݣ�����������
 * �������̣߳�һ��������һ���߳������дֵ��һ���߳�ֻ��������ֵ
 * һ�����̣߳�һ��д�̣߳��������----
 * ��ͬһ��ȫ�ֱ���д100000��
 * ��1����������2��ԭ�Ӳ���
 * 
 * //��ҿ��԰�ԭ�Ӳ����������������Ĳ�����Ҳ�������ԭ�Ӳ����ǲ��ᱻ��ϵĴ����
 * ԭ�Ӳ����Ȼ�����Ч��Ҫ��
 * ������һ�������Զ��д��룬ԭ�Ӳ���һ�㶼�����һ������������i��һ�������
 * ԭ�Ӳ���һ��ָ���ɷָ�Ĳ������������Ҫô��ɣ�Ҫôû�����������м�״̬��
 * c++��ʹ��atomic��ģ����ʵ��
 * 
 *ԭ�Ӳ���--- �������÷�����
 *
 *�ĵã�ԭ�Ӳ���ֻ���һ��������һ����ԭ�Ӳ������м������緢�͵����ݰ���
 *���յ����ݰ�
 *
 */