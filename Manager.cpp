#include "Manager.h"

Manager::Manager(int id, string name, int Did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = Did;
}

void Manager::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ�𣺼ƻ�������"
		<< endl;
}

string Manager::getDeptName()
{
	return string("����");
}