#include <iostream>
using  namespace std;
#include "WorkManager.h"

int main()
{
	WorkerManager wm;

	int choice = 0; //�����洢�û���ѡ��

	while (true)
	{
		//����չʾ�˵���Ա����
		wm.Show_Menu();

		cout << "����������ѡ�� " << endl;
		cin >> choice; // �����û���ѡ��

		switch (choice)
		{
		case 0:  //�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1:  //����ְ��
			wm.Add_Emp();
			break;
		case 2:  //��ʾְ��
			wm.Show_Emp();
			break;
		case 3:  //ɾ��ְ��
			wm.Del_Emp();
			break;
		case 4:  //�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5:  //����ְ��
			wm.Find_Emp();
			break;
		case 6:  //����ְ��
			wm.Sort_Emp();
			break;
		case 7:  //����ĵ�
			wm.Clean_File();
			break;
		default:
			system("cls"); //����
			break;
		}
	}

	system("pause");

	return 0;
}