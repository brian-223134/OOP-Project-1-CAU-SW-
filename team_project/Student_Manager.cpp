#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

void file_tracker(const string& f_name);
void add_student_data(vector<Student>& students);
void file_tracker(const string& f_name);
void display_menu();

class Student {
private:
	string name; //�л� �̸�
	int student_id; //�л� ID
	int Birth_year; //�л� ź���⵵
	string Department; //�л��� ���� �к�
	int Tel; //�л� ����ó

public:

	//��ü ������, Maual input�� ���� �׻� �ùٸ��ٴ� ���� �����ϰ� �����ڸ� ������
	Student() {}

	Student(string name, int student_id, int Birth_year, string Department, int Tel)
	{
		this->name = name;
		this->student_id = student_id;
		this->Birth_year = Birth_year;
		this->Department = Department;
		this->Tel = Tel;
	}

	//���Ͽ� insert�� �� ����� Getter
	string get_student_name() { return name; }
	int get_id() { return student_id; }
	int get_Birth_year() { return Birth_year; }
	string get_Departmet() { return Department; };
	int get_tel() { return Tel; };

	//insert �� �� �ӽ� class�� �Է� ���� �ֱ� ���� Mutator�� �ʿ�.
	void set_name(string& Name) { name = Name; }
	void set_id(int id) { student_id = id; }
	void set_Birth_year(int B_year) { Birth_year = B_year; }
	void set_Department(string& department) { Department = department; }
	void set_telephone(int telephone) { Tel = telephone; }

};


int main(void)
{
	const string f_name = "a.txt"; //txt ������ �̸��� a�����Ƿ� ���ϸ��� �����Ѵ�.
	ifstream(f_name);
	vector<Student> students; //�л����� ������ �Է� �޴� vector�� ����, vector�� ��� ������ ũ�� ��ȭ �����Ͽ� ���

	file_tracker(f_name); //���� ���� Ȯ�� �� ����

	while (1) //���� ȭ���� ������ ���� ������ ������ ����ؼ� ���������
	{
		display_menu();

		//��ü�� ���ο� �����͸� �ޱ� ���� �ӽ� ���� ����
		string n_name = NULL;
		int n_id = 0;
		int n_Birth_year = 0;
		string n_department = NULL;
		int n_tel = 0;

		int menu_choice;
		cin >> menu_choice;

		switch (menu_choice)
		{
		case 1:
			cout << "Enter student name, id, Birth year, department and telephone number (Enter seperate)" << endl;
			getline(cin, n_name, '\n');
			cin >> n_id;
			cin >> n_Birth_year;
			cin.ignore(); //cin�� ��� '\n'�� ���������Ƿ� getline ������ ignore ó���� �ʿ�
			getline(cin, n_department, '\n');
			cin >> n_tel;

			students.push_back({ n_name, n_id, n_Birth_year, n_department, n_tel });
			add_student_data(students);
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			exit(0);
			break;

		default:
			cout << "invalid input\n";
		}
	}
	return 0;
}

void file_tracker(const string& f_name)
{
	ifstream file(f_name); //f_name�� �̸��� ������ ã��
	if (!file) //������ Null�� ��ȯ�ϹǷ� if������ ����
	{
		ofstream student_data(f_name); //ofstream: ���� ���� (������ ���� ����)
		student_data.close(); //���� ������� ���� �� �ݾ��־�� �ٸ� ������ stream�� ���� �� �ִ�.
	}
}

void add_student_data(vector <Student>& students)
{
	Student temp_student;
	string temp_name;
	int temp_id;
	int temp_birth_year;
	string temp_department;
	int temp_tel;

	cout << "insert student name: ";
	cin >> temp_name;
	temp_student.set_name(temp_name);

	cout << "insert student id: ";
	cin >> temp_id;
	temp_student.set_id(temp_id);

	cout << "insert student birth year: ";
	cin >> temp_birth_year;
	temp_student.set_Birth_year(temp_birth_year);

	cout << "insert student's department: ";
	cin >> temp_department;
	temp_student.set_Department(temp_department);

	cout << "insert student's telephone number: ";
	cin >> temp_tel;
	temp_student.set_telephone(temp_tel);

	//������ �ߺ��Ǵ� �����Ͱ� �ִ��� �˻�
	for (auto& exist : students)
	{
		if (exist.get_id() == temp_student.get_id())
		{
			cout << "Error: already inserted\n";
			return;
		}
	}

	students.push_back(temp_student); //���� �Է� ���� �л��� ������ students vector�� �����ϱ�
	fstream file("a.txt", ios::app);
	if (file.is_open())
	{
		for (Student& temp : students)
		{
			string to_txt_data = temp.get_student_name();
			to_txt_data.resize(16, ' ');
			to_txt_data += to_string(temp.get_id());
			to_txt_data.resize(27, ' ');
			to_txt_data += to_string(temp.get_Birth_year());
			to_txt_data.resize(32, ' ');
			to_txt_data += temp.get_Departmet();
			to_txt_data.resize(48, ' ');
			to_txt_data += temp.get_tel();
			file << to_txt_data << endl;
		}
		//���� �Է��ϱ� �� ���缭 �Է��ϱ� ��� �����ϱ� 
	}
	file.close();
}

void display_menu()
{
	cout << "1. Insertion\n";
	cout << "2. Search\n";
	cout << "3. Sorting Option\n";
	cout << "4. Exit\n";
	cout << "_> ";
}
