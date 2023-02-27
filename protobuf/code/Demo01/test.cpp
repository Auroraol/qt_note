#include <iostream>
#include "demo01.pb.h"
#include <string>

using namespace std;
int main(void)
{
	// 1.创建persion对象，并初始化
	Preson p;

	p.set_id(1);

	//name使用repeated相对于vector
	//申请一块内存，存储名字
	p.add_name();
	p.set_name(0, "小明");
	p.add_name();
	p.set_name(1, "小红");
	p.add_name();
	p.set_name(2, "小水");

	//枚举
	p.set_color(Blue);

	p.set_sex("man");
	p.set_age(10);

	// 另一个message
	Info* info = p.mutable_info();
	info->set_address("北京昌平区tdb大厦");
	info->set_number(911);

	// 2.将persion对象序列化->字符串
	string output;
	p.SerializeToString(&output);
	cout << "序列前的数据: " << output << endl;

	// 3.数据传输
	// 4，接收数据，解析（output）->解码->原始数据
	// 4.1创建Persion对象
	Preson pp;
	pp.ParseFromString(output);

	// 将Info对象里的值取出
	Info li = pp.info();
	cout << "\n反序列的数据: " << endl;
	cout << "id: " << pp.id() << " name1: " << pp.name(0) << " name2: "
		<< pp.name(1) << " name3: " << pp.name(2) << " sex: " << pp.sex() << " age: " << pp.age()
		<< " 枚举: " << pp.color()
		<< " adrees(Info): " << li.address()
		<< " number(Info): " << li.number() << endl;
	return 0;
}