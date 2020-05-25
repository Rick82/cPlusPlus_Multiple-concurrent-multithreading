#include <iostream>
#include <string>
#include<thread>
#include <allocators>
#include <mutex>
using namespace std;

//������
std::mutex resource_mutex;


//������
class MyCAS
{
private:
	//���캯��˽�л�
	MyCAS(){}
private:
	static MyCAS*m_instance;//��̬��Ա����ָ��
public:
	static MyCAS*GetInstance()
	{
		if (m_instance == NULL)//˫�ؼ��
		{
			std::unique_lock<std::mutex>MyMutex(resource_mutex);//�Զ��������Զ�����
			//����д��Ч�ʵͣ���Ϊ����ֻ���ڵ�һ�ε��õ�ʱ��Żᴴ�������������ᴴ�������������жϿ��Խ��
			if (m_instance == NULL)
			{
				//m_instance = new MyCAS();
				m_instance = new MyCAS();
				static ReleaseObject ro;

			}
		}
		
		return m_instance;
	}
	//������һ����ʵ���ڴ��ͷţ�����û�����ã�
	class ReleaseObject
	{
	public:
		~ReleaseObject()
		{
			if (MyCAS::m_instance)
			{
				cout << "���ٶ���" << endl;
				delete MyCAS::m_instance;
				MyCAS::m_instance = NULL;
			}
		}
		
	};
	void function1()
	{
		cout << "���Ժ���" << endl;
	}
	
};
//��Ҫ��ʼ����̬��Ա����
MyCAS* MyCAS::m_instance = NULL;

//�߳���ں���
void startThread()
{
	cout << "�߳̿�ʼִ����" << endl;
	MyCAS*p_a = MyCAS::GetInstance();
	cout << "�߳�ִ�������" << endl;
	return;

}

int main(void)
{
	////���ظ�������ָ��
	//MyCAS*p_a = MyCAS::GetInstance();
	//p_a->function1();


	//�����߳���ͬһ����ں�����������������������̻�������ͨ·ͬʱִ��startThread������
	//������һ���߳̽���getInstance�����ǻ�û�д��������л����ڶ����̣߳������Ϳ��ܴ����������
	//m_instance == NULL������û���������󣬿������Ͼͻᴴ���������߳��л���
	thread mythread1(startThread);
	thread mythread2(startThread);
	mythread1.join();
	mythread2.join();

	system("pause");
	return 0;
}
/*
 * ���ģʽ���̸
 * �����ģʽ��--�����һЩ�ض���д��������������ά�������ܷ��㣬���Ǳ����Ķ�������ʹ��
 * �����ģʽд���Ĵ���ܻ�ɬ�Ѷ���head first��
 * ���Ǳ���Ӧ���ر�����Ŀ ��ʱ�򣬸���ʵ�ʿ���������ģ�黮�־��飬�ܽ�����ģʽ�����п������飬�������ģʽ
 * ���ǵ��й�������̫һ��������һ����ĿӲ�����ģʽ��һ��СС��Ŀ����Ҫ�׼������ģʽ��
 * ���ģʽ������ص��е㣬Ҫ��ѧ���ã���Ҫ����Ӳ��
 * 
 * �������ģʽ��ʹ�õ�Ƶ�ʱȽϸߡ�
 * ��������Ŀ�У���ĳ��������ࡣ�����ڸ���Ķ���ֻ�ܴ���һ���������ʵ��ֻ����һ����
 * ���ڣ������ļ���д��ʱ��Ϊ���������ֻ��һ������󣬷������
 * 
 * �ڴ��ͷź���û��������
 * 
 * //�������ģʽ������������������
 * ������������̴߳����������󣬵���ʵ���п����ж������ͬʱ����GetInstance()������������������
 * ���ʱ�����Ҫʹ�û���
 * 
 * 
 * //std::call_once��һ������ģ�壬��c++11����ĺ���
 * �ڶ���������һ���������֣�call_once�Ĺ����Ǳ�֤����ֻ�ᱻ����һ��
 * call_once���л�������������������Ч���ϣ���Ȼ���������ռ�õ���Դ����
 * call_once��Ҫ��һ����ǽ��ʹ�ã�������once_flag����ʵ��once_flagһ�ֽṹ
 * call_once����ͨ���������жϺ����Ƿ�ִ�У�ִ�й�������Ͱ������������Ϊ�Ѿ�����״̬
 * �����ٵ��õ��Ǳ�־�Ѿ�������Ϊ���Ѿ����á�״̬�ˣ��Ͳ�����ִ���������
 */

