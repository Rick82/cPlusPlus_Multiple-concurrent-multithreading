#include <iostream>
#include <string>
#include<thread>
#include <memory>

using namespace std;



void MyPrint2(unique_ptr<int>pn)

{
	//cout << "thread is:" << this_thread::get_id() << endl;
	;
}


int main(void)
{


	unique_ptr<int> Myp(new int(100));
	//����ָ��ת��ʹ��move
	thread mythread(MyPrint2, std::move(Myp));
	mythread.join();
	//mythread.detach();

	system("pause");
	return 0;
}

/*
 *û�б���ͨ��,��gcc����������ȷ
 *��ϰ����ָ�룬move()*/