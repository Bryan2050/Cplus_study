#include "WorkManager.h"

WorkerManager::WorkerManager()
{
	//1���ļ�������

	ifstream ifs;
	ifs.open(FILENAME, ios::in); // ���ļ�

	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		//��ʼ������
		//��ʼ����¼����
		this->workerNum = 0;
		//��ʼ������ָ��
		this->workerArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2���ļ����� ����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		//cout << "�ļ�Ϊ�գ�" << endl;
		//��ʼ����¼����
		this->workerNum = 0;
		//��ʼ������ָ��
		this->workerArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3���ļ����ڣ����Ҽ�¼����
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ�� " << num << endl;
	this->workerNum = num;

	//���ٿռ䣬���Լ�¼���ǿ������������׵�ַ����С�������ֵȷ��
	this->workerArray = new Worker * [this->workerNum];
	//���ļ��е����� ���浽������
	this->init_Emp();

	//���Դ���
	//for (int i = 0; i < this->workerNum; i++)
	//{
	//	cout << "ְ����ţ� " << this->workerArray[i]->m_Id
	//		<< " ������ " << this->workerArray[i]->m_Name
	//		<< " ���ű�ţ� " << this->workerArray[i]->m_DeptId << endl;
	//}
}

//չʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0); // �˳�����
}

//����ְ��
void WorkerManager::Add_Emp()
{
	cout << "����������ְ�������� " << endl;

	int addNum = 0; //�����û�����������
	cin >> addNum;

	if (addNum > 0)
	{
		//����
		//���������¿ռ��С
		int newSize = this->workerNum + addNum; // �¿ռ����� = ԭ����¼���� + ��������

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ������ݣ��������¿ռ���
		if (this->workerArray != NULL)
		{
			for (int i = 0; i < this->workerNum; i++)
			{
				newSpace[i] = this->workerArray[i];
			}
		}

		//��������������
		for (int i = 0; i < addNum; i++)
		{
			int id; //ְ�����
			string name; //ְ������
			int dSelect; // ����ѡ��

			cout << "������� " << i + 1 << " ����ְ����ţ� " << endl;
			cin >> id;

			cout << "������� " << i + 1 << " ����ְ�������� " << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//������ְ��ְ�� �����浽�����У��������������
			newSpace[this->workerNum + i] = worker;
		}

		//�ͷ�ԭ�пռ�
		delete[] this->workerArray;

		//�����¿ռ��ָ��
		this->workerArray = newSpace;

		//�����µ�ְ������
		this->workerNum = newSize;

		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;

		//��ʾ���ӳɹ�
		cout << "�ɹ�����" << addNum << "����ְ��!" << endl;

		//�������ݵ��ļ���
		this->save();
	}
	else
	{
		cout << "������������" << endl;
	}

	//��������� �����ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//�����ļ�
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); // ������ķ�ʽ���ļ�  -- д�ļ�

	//��ÿ��������д�뵽�ļ���
	for (int i = 0; i < this->workerNum; i++)
	{
		ofs << this->workerArray[i]->m_Id << " "
			<< this->workerArray[i]->m_Name << " "
			<< this->workerArray[i]->m_DeptId << endl;
	}

	//�ر��ļ�
	ofs.close();
}

//ͳ���ļ�������
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //���ļ�  ��

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//ͳ����������
		num++;
	}

	return num;
}

//��ʼ��Ա��
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		if (dId == 1) //��ְͨ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) //����
		{
			worker = new Manager(id, name, dId);
		}
		else  //�ϰ�
		{
			worker = new Boss(id, name, dId);
		}
		this->workerArray[index] = worker;
		index++;
	}

	//�ر��ļ�
	ifs.close();
}

//��ʾְ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		for (int i = 0; i < workerNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->workerArray[i]->showInfo();
		}
	}
	//�������������
	system("pause");
	system("cls");
}

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//����ְ�����ɾ��
		cout << "��������Ҫɾ��ְ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1) //˵��ְ�����ڣ�����Ҫɾ����indexλ���ϵ�ְ��
		{
			for (int i = index; i < this->workerNum - 1; i++)
			{
				//����ǰ��
				this->workerArray[i] = this->workerArray[i + 1];
			}
			this->workerNum--; //���������м�¼��Ա����
			//����ͬ�����µ��ļ���
			this->save();

			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}

	//������� ����
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����  ������ڷ���ְ�����������е�λ�ã������ڷ���-1
int WorkerManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->workerNum; i++)
	{
		if (this->workerArray[i]->m_Id == id)
		{
			//�ҵ�ְ��
			index = i;

			break;
		}
	}

	return index;
}

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���ҵ���ŵ�ְ��

			delete this->workerArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽�� " << id << "��ְ������������ְ���ţ� " << endl;
			cin >> newId;

			cout << "�������������� " << endl;
			cin >> newName;

			cout << "�������λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//�������� ��������
			this->workerArray[ret] = worker;

			cout << "�޸ĳɹ���" << this->workerArray[ret]->m_DeptId << endl;

			//���浽�ļ���
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}

	//������� ����
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų��� " << endl;
		cout << "2����ְ���������� " << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//���ձ�Ų�
			int id;
			cout << "��������ҵ�ְ����ţ� " << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				//�ҵ�ְ��
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->workerArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2)
		{
			//����������
			string name;
			cout << "��������ҵ�������" << endl;
			cin >> name;

			//�����ж��Ƿ�鵽�ı�־
			bool flag = false; //Ĭ��δ�ҵ�ְ��

			for (int i = 0; i < workerNum; i++)
			{
				if (this->workerArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ�� "
						<< this->workerArray[i]->m_Id
						<< "��ְ����Ϣ���£�" << endl;

					flag = true;

					//������ʾ��Ϣ�ӿ�
					this->workerArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}

	//�����������
	system("pause");
	system("cls");
}

//���ձ������
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < workerNum; i++)
		{
			int minOrMax = i; //������Сֵ �� ���ֵ�±�
			for (int j = i + 1; j < this->workerNum; j++)
			{
				if (select == 1) //����
				{
					if (this->workerArray[minOrMax]->m_Id > this->workerArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else  //����
				{
					if (this->workerArray[minOrMax]->m_Id < this->workerArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			//�ж�һ��ʼ�϶� ��Сֵ�����ֵ �ǲ��� �������Сֵ�����ֵ��������� ��������
			if (i != minOrMax)
			{
				Worker* temp = this->workerArray[i];
				this->workerArray[i] = this->workerArray[minOrMax];
				this->workerArray[minOrMax] = temp;
			}
		}

		cout << "����ɹ��������Ľ��Ϊ�� " << endl;
		this->save(); //����������浽�ļ���
		this->Show_Emp();//չʾ����ְ��
	}
}

//����ļ�
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc); // ɾ���ļ������´���
		ofs.close();

		if (this->workerArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->workerNum; i++)
			{
				delete this->workerArray[i];
				this->workerArray[i] = NULL;
			}

			//ɾ����������ָ��
			delete[] this->workerArray;
			this->workerArray = NULL;
			this->workerNum = 0;
			this->m_FileIsEmpty = true;
		}

		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()
{
	if (this->workerArray != NULL)
	{
		for (int i = 0; i < this->workerNum; i++)
		{
			if (this->workerArray[i] != NULL)
			{
				delete this->workerArray[i];
			}
		}

		delete[] this->workerArray;
		this->workerArray = NULL;
	}
}