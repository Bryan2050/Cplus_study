#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

class Employee :public Worker
{
public:

	//���캯��
	Employee(int id, string name, int dId);

	//��ͨԱ����д��ʾ������Ϣ
	void showInfo();

	//��ȡ��λ����
	string  getDeptName();
};
