#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<vector>
#include<algorithm>

using namespace std;

class Student {
private:
	string name; //�л� �̸�
	string student_id; //�л� ID
	string Birth_year; //�л� ź���⵵
	string Department; //�л��� ���� �к�
	string Tel;

public:
	//��ü ������, Maual input�� ���� �׻� �ùٸ��ٴ� ���� �����ϰ� �����ڸ� ������
	Student() {}

	Student(string name, string student_id, string Birth_year, string Department, string Tel)
	{
		this->name = name;
		this->student_id = student_id;
		this->Birth_year = Birth_year;
		this->Department = Department;
		this->Tel = Tel;
	}
	//���Ͽ� insert�� �� ����� Getter
	string get_student_name() { return name; }
	string get_id() { return student_id; }
	string get_Birth_year() { return Birth_year; }
	string get_Department() { return Department; };
	string get_tel() { return Tel; };
	//insert �� �� �ӽ� class�� �Է� ���� �ֱ� ���� Mutator�� �ʿ�.
	void set_name(string& Name) { name = Name; }
	void set_id(string id) { student_id = id; }
	void set_Birth_year(string B_year) { Birth_year = B_year; }
	void set_Department(string& department) { Department = department; }
	void set_telephone(string& telephone) { Tel = telephone; }
};

class Student_DB {
private:
	vector<Student> students;

public:
	void add_student_data(Student& student);
	void load_data(const Student& student)
	{
		students.push_back(student);
	}
	void show_all_data()
	{
		cout << setw(15) << left << "Student Name" << " " << setw(10) << "StudentID"
			<< " " << setw(20) << left << "Department" " " << setw(10)
			<< "Birth year" << "  " << setw(12) << "Tel" << endl;
		for (auto& s : students)
		{
			cout << setw(15) << left << s.get_student_name() << " "
				<< setw(10) << s.get_id() << " " << setw(19) << s.get_Department()
				<< " " << setw(10) << right << s.get_Birth_year()
				<< "  " << setw(12) << left << s.get_tel() << endl;
		}
		cout << "\n";
	}
};

// ���α׷��� ��ɿ� ���������� ������ �ִ� �Լ���
void file_tracker(const string& f_name);
Student get_input_student();
bool compare_birth_year(Student& a, Student& b);


// ���� �ɼ��� �����ִ� menu �Լ���
void display_menu();
void display_search_option();
void display_sorting_option();

int main(void)
{
	const string f_name = "file1.txt"; //txt ������ �̸��� a�����Ƿ� ���ϸ��� �����Ѵ�.
	ifstream file ("file1.txt");
	
	Student_DB students_db; //students�� DB ��ü�� �ҷ��Ա� ������ ��ü ���� Vector�� ����
	
	streampos begin, end; //������ �ۼ��� txt ���� �� ������ ������ �Ǵ��ϱ� ���� ô�� ����
	begin = file.tellg();
	file.seekg(0, ios::end);
	end = file.tellg();
	file.close();
	
	if ((end - begin != 0)) //txt���Ͽ� � ������ ������
	{
		ifstream file("file1.txt");
		string line;

		while (getline(file, line))
		{
			istringstream iss(line);
			string txt_name;
			string txt_student_id;
			string txt_birth_year;
			string txt_department;
			string txt_tel;

			getline(iss, txt_department, ',');

			if (iss >> txt_name >> txt_student_id >> txt_birth_year >> txt_tel)
			{
				students_db.load_data({ txt_name, txt_student_id,txt_birth_year, txt_department, txt_tel });
				//student_db ��ü ���� txt ���Ͽ� �ִ� ������ ���� �����´�.
			}
		}

		file.close();
	}

	file_tracker(f_name); //���� ���� Ȯ�� �� ����

	while (1) //���� ȭ���� ������ ���� ������ ������ ����ؼ� ���������
	{
		display_menu();
		Student input_student;
		int menu_choice;
		cin >> menu_choice;

		switch (menu_choice)
		{
		case 1:
			input_student = get_input_student();
			students_db.add_student_data(input_student);
			break;

		case 2:
			display_search_option();
			int op_choice;
			cin >> op_choice;
			switch (op_choice)
			{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;

				case 5:
					break;

				case 6:
					students_db.show_all_data();
					break;

				default:
					cout << "Invalid option" << endl;
					break;
			}
			break;
		case 3:
			break;

		case 4:
			exit(0);
			break;

		default:
			cout << "invalid input\n";
			break;
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

Student get_input_student()
{
	Student temp_student;
	string temp_name;
	string temp_id;
	string temp_birth_year;
	string temp_department;
	string temp_tel;

	cout << "Name ? ";
	cin >> temp_name;
	temp_student.set_name(temp_name);

	cout << "Student ID (10 digits) ? ";
	cin >> temp_id;
	temp_student.set_id(temp_id);

	cout << "Birth Year (4 digits) ? ";
	cin >> temp_birth_year;
	temp_student.set_Birth_year(temp_birth_year);

	cin.ignore(); //cin ���� getline�� �ϱ� ���ؼ� cin���� ���� ���� �������� �ʱ�ȭ�ؾ��Ѵ�.
	cout << "Department ? ";
	getline(cin, temp_department); //space�� �����ϴ� input�� ������ getline�� ����ؾ��Ѵ�.
	temp_student.set_Department(temp_department);

	cout << "Tel ? ";
	cin >> temp_tel;
	temp_student.set_telephone(temp_tel);
	cout << "\n";

	return temp_student;
}

void Student_DB :: add_student_data(Student& temp_student) {
	for (auto& exist : students){ //students vector ���� for���� ���鼭 id�� ������ ���� ����
		if (exist.get_id() == temp_student.get_id())
		{
			cout << "Error: already inserted\n";
					return;
		}
	}

	students.push_back(temp_student); //���� Ž�� �������� �ߺ��� ������ Ȯ�εǸ� push_back�� �Ѵ�.
	
	fstream file("file1.txt", ios::app); //txt ���Ͽ� input�ϱ� ���� fstream�� app ���·� ����.
	if (file.is_open())
	{
		string to_txt_data = temp_student.get_Department(); //Department�� ��� spacing�� �־� ���߿� ���� �� �޸��� string�� �и��ϱ����� �۾�
		to_txt_data += ",";
		to_txt_data += temp_student.get_student_name();
		to_txt_data += " ";
		to_txt_data += temp_student.get_id();
		to_txt_data += " ";
		to_txt_data += temp_student.get_Birth_year();
		to_txt_data += " ";
		to_txt_data += temp_student.get_tel();
		file << to_txt_data << endl;
	}
	file.close();
}

bool compare_birth_year(Student& a, Student& b)
{
	return a.get_Birth_year() < b.get_Birth_year();
}

void display_menu()
{
	cout << "1. Insertion\n";
	cout << "2. Search\n";
	cout << "3. Sorting Option\n";
	cout << "4. Exit\n";
	cout << "_> ";
}

void display_search_option()
{
	cout << "1. Search by name\n";
	cout << "2. Search by student ID\n";
	cout << "3. Search by admission year\n";
	cout << "4. Search by birth year\n";
	cout << "5. Search by department name\n";
	cout << "6. List All\n\n";
	cout << "> ";
}

void display_sorting_option()
{
	cout << "-Sorting Option\n";
	cout << "1. Sort by Name\n";
	cout << "2. Sort by Student ID\n";
	cout << "3. Sort by Birth Year\n";
	cout << "4. Sort by Department\n";
	cout << "> ";
}