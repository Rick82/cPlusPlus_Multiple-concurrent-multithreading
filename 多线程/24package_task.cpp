#include <iostream>
#include <string>
#include<thread>
#include <future>
using namespace std;


	int mythread(int mypar)
	{
		cout << "mpar=" << mypar << endl;
		chrono::milliseconds dura(5000);
		this_thread::sleep_for(dura);
		cout << "�߳̿�ʼִ��,�̵߳�id�ǣ�" << std::this_thread::get_id() << endl;
		//��Ϣ5s

		return 5884;
	}



int main(void)
{
	cout << "���߳�id=" << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)>mpt(mythread);//����ֵ���ͣ���������--���ǰѺ���mythreadͨpackaged_task��װ
	std::thread t1(std::ref(mpt), 1);//1�Ǵ��ݵĲ���,����һ���̣߳�����ʼִ��
	t1.join();
	//packaged_task���̺߳�����װ��һ��

	//ͨ��future��ȡδ������ִ�е�ֵ
	//std::future��������������߳���ں����Ľ����result����mythread�ķ��ؽ�
	//get_future()��packaged_task()����Ľӿ�
	std::future<int> result = mpt.get_future();
	cout << result.get() << endl;

	system("pause");
	return 0;
}

/*
 *packaged_task ������񣬰������װ����
 *�Ǹ���ģ�壬����ģ������Ǹ��ֿɵ��ö���ͨ��packageed_task���԰�
 *���ֿɵ��ö����װ������������Ϊ�߳���ں��������á�
*/

