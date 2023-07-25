#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

class Employee :public Worker
{
public:

	//构造函数
	Employee(int id, string name, int dId);

	//普通员工重写显示个人信息
	void showInfo();

	//获取岗位名称
	string  getDeptName();
};
