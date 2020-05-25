#include <iostream>
#include <string>
#include<thread>
#include <future>
using namespace std;

class A
{
public:
	int mythread(int mypar)
	{
		cout << "mpar=" << mypar << endl;
		chrono::milliseconds dura(5000);
		this_thread::sleep_for(dura);
		cout << "�߳̿�ʼִ��,�̵߳�id�ǣ�" << std::this_thread::get_id() << endl;
		//��Ϣ5s

		return 5884;
	}
	
};


int main(void)
{
	A a;
	int tempar = 12;
	cout << "main thread id:" << std::this_thread::get_id() << endl;
	//std::future<int> result = std::async(mythread);
	//std::future<int> result = std::async(&A::mythread,&a,tempar);//�ڶ�������ʹ�ö������ã����ܱ�֤ʹ�õ���ͬһ������
	std::future<int> result = std::async(std::launch::deferred,&A::mythread,&a,tempar);//�ڶ�������ʹ�ö������ã����ܱ�֤ʹ�õ���ͬһ������

	//�Զ�����һ���̣߳��������߳���ں���
	/*����ͨ����async()��������һ������Ĳ������ò���������std::launcher���ͣ���
	 *�ﵽһЩ�����Ŀ��
	 *std::launch::deferred--��ʾ�߳���ں������ñ��ӳٵ�std::future��get����wait()���ò�ִ��
	 *��ô���get����waitû�е��ã�������ִ����??---û��ִ�У�
	 *�̶߳�û�д������̣߳������߳���ִ�����߳���ں�����---ִ��ͦ���
	 *std::launch::async --�첽���ڵ���asyncde ʱ��ʹ��������̣߳������д��һ����ǣ�Ĭ�Ͼ������
	 *std::launch::sync--ͬ��
	 *std::launch::any
	 *
	 *
	 */

	cout << "continue........" << endl;
	int def = 0;
	//��������ȴ��߳�ִ����ϣ�ͨ��future�����get���������ȴ�����������õ����ؽ��
	cout << "δ����ִ�н���ǣ�" << result.get() << endl;
	system("pause");
	return 0;
}

/*
* async--����ģ�壬��������һ���첽������������󣬷���һ��std::future����
* ʲô������һ���첽����--�Զ�����һ���̲߳������̵߳���ں���������һ��future����
* �����������Ͱ����߳���ں��������صĽ���������̷߳��صĽ����Ҳ����ʹ��get������������ȡ
*
* future--δ��---����Ҳ��Ϊfuture�ṩ��һ�ַ����첽��������Ļ��ƣ����ӵ����㣬��Ҫ�ȴ�δ����������
* --�����߳�ִ����ϾͿ����õ�����ˣ�
* future��wait()����ֻ�ȴ��߳̽������������ؽ����
*/

