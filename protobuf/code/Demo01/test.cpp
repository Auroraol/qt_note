#include <iostream>
#include "demo01.pb.h"
#include <string>

using namespace std;
int main(void)
{
	// 1.����persion���󣬲���ʼ��
	Preson p;

	p.set_id(1);

	//nameʹ��repeated�����vector
	//����һ���ڴ棬�洢����
	p.add_name();
	p.set_name(0, "С��");
	p.add_name();
	p.set_name(1, "С��");
	p.add_name();
	p.set_name(2, "Сˮ");

	//ö��
	p.set_color(Blue);

	p.set_sex("man");
	p.set_age(10);

	// ��һ��message
	Info* info = p.mutable_info();
	info->set_address("������ƽ��tdb����");
	info->set_number(911);

	// 2.��persion�������л�->�ַ���
	string output;
	p.SerializeToString(&output);
	cout << "����ǰ������: " << output << endl;

	// 3.���ݴ���
	// 4���������ݣ�������output��->����->ԭʼ����
	// 4.1����Persion����
	Preson pp;
	pp.ParseFromString(output);

	// ��Info�������ֵȡ��
	Info li = pp.info();
	cout << "\n�����е�����: " << endl;
	cout << "id: " << pp.id() << " name1: " << pp.name(0) << " name2: "
		<< pp.name(1) << " name3: " << pp.name(2) << " sex: " << pp.sex() << " age: " << pp.age()
		<< " ö��: " << pp.color()
		<< " adrees(Info): " << li.address()
		<< " number(Info): " << li.number() << endl;
	return 0;
}