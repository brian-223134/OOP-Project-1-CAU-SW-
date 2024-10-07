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
	string birth_year; //�л� ź���⵵
	string department; //�л��� ���� �к�
	string tel; //�л��� ����ó

public:
	//============= Constructor =============
	//��ü ������, Maual input�� ���� �׻� �ùٸ��ٴ� ���� �����ϰ� �����ڸ� ������
	Student() {}

	Student(string name, string student_id, string Birth_year, string Department, string Tel)
	{
		this->name = name;
		this->student_id = student_id;
		this->birth_year = Birth_year;
		this->department = Department;
		this->tel = Tel;
	}

	//============= Getter Setter =============
	//���Ͽ� insert�� �� ����� Getter
	string get_student_name() { return name; }
	string get_id() { return student_id; }
	string get_birth_year() { return birth_year; }
	string get_department() { return department; };
	string get_tel() { return tel; };
	//insert �� �� �ӽ� class�� �Է� ���� �ֱ� ���� Mutator�� �ʿ�.
	void set_name(string& Name) { this->name = Name; }
	void set_id(string& id) { this->student_id = id; }
	void set_birth_year(string& B_year) { this->birth_year = B_year; }
	void set_department(string& department) { this->department = department; }
	void set_telephone(string& telephone) { this->tel = telephone; }
};

class Student_DB {
private:
	vector<Student> students;
	vector<Student> _selected;
	int sort_option = 1;

public:
	//============= Getter Setter =============
	void set_sort_option(int sort_option) { this->sort_option = sort_option; };
	int get_sort_option() { return this->sort_option; };
	//============= member function =============
	void add_student_data(Student& student);
	void load_data(const Student& student)
	{
		students.push_back(student);
	}
	void sort_student_data(int sort_option);
	void show_all_data()
	{ 
		cout << setw(15) << left << "Student Name" << " " << setw(10) << "StudentID"
			<< " " << setw(25) << left << "Department" " " << setw(10)
			<< "Birth year" << "  " << setw(12) << "Tel" << endl;
		for (auto& s : students)
		{
			cout << setw(15) << left << s.get_student_name() << " "
				<< setw(10) << s.get_id() << " " << setw(24) << s.get_department()
				<< " " << setw(10) << right << s.get_birth_year()
				<< "  " << setw(12) << left << s.get_tel() << endl;
		}
		cout << "\n";
	}
	//Seach function
	void search_student_data(int select_option);
	void sort_selected_data(int sort_option);
	void show_selected_data();
};

void file_tracker(const string& f_name);
Student get_input_student();

// ���� �ɼ��� �����ִ� menu �Լ���
void display_menu();
void display_search_option();
void display_sorting_option();

int main(void)
{
	const string f_name = "file1.txt"; //txt ������ �̸��� file1�����Ƿ� ���ϸ��� �����Ѵ�.
	ifstream file("file1.txt");
	
	Student_DB students_db; //students�� DB ��ü�� �ҷ��Ա� ������ ��ü ���� Vector�� ����

	streampos begin, end; //������ �ۼ��� txt ���� �� ������ ������ �Ǵ��ϱ� ���� ô�� ����
	begin = file.tellg();
	file.seekg(0, ios::end);
	end = file.tellg();
	file.close();

	//Synchronize file to students
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
			getline(iss, txt_name, ',');

			if (iss >> txt_student_id >> txt_birth_year >> txt_tel)
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
		int search_choice;
		int sort_option;

		switch (menu_choice)
		{
		case 1: //Insertion
			input_student = get_input_student();
			students_db.add_student_data(input_student);
			break;

		case 2: //Search
			display_search_option();
			cin >> search_choice;

			students_db.search_student_data(search_choice);
			break;

		case 3: //Sorting Option
			display_sorting_option();
			cin >> sort_option;

			students_db.set_sort_option(sort_option);
			break;

		case 4: //Exit
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

	//���Ⱑ ���Ե� ���ڿ��� ���� �� getline
	cin.ignore();
	cout << "Name ? ";
	getline(cin, temp_name);
	temp_student.set_name(temp_name);

	cout << "Student ID (10 digits) ? ";
	cin >> temp_id;
	temp_student.set_id(temp_id);


	cout << "Birth Year (4 digits) ? ";
	cin >> temp_birth_year;
	temp_student.set_birth_year(temp_birth_year);

	cin.ignore(); //cin ���� getline�� �ϱ� ���ؼ� cin���� ���� ���� �������� �ʱ�ȭ�ؾ��Ѵ�.
	cout << "Department ? ";
	getline(cin, temp_department); //space�� �����ϴ� input�� ������ getline�� ����ؾ��Ѵ�.
	temp_student.set_department(temp_department);

	cout << "Tel ? ";
	cin >> temp_tel;
	temp_student.set_telephone(temp_tel);
	cout << "\n";

	return temp_student;
}

void Student_DB::add_student_data(Student& temp_student) {
	for (auto& exist : students) { //students vector ���� for���� ���鼭 id�� ������ ���� ����
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
		string to_txt_data = temp_student.get_department(); //Department�� ��� spacing�� �־� ���߿� ���� �� �޸��� string�� �и��ϱ����� �۾�
		to_txt_data += ",";
		to_txt_data += temp_student.get_student_name();
		to_txt_data += ",";
		to_txt_data += temp_student.get_id();
		to_txt_data += " ";
		to_txt_data += temp_student.get_birth_year();
		to_txt_data += " ";
		to_txt_data += temp_student.get_tel();
		file << to_txt_data << endl;
	}
	file.close();
}

void Student_DB::sort_student_data(int sort_option) //now not be used
{
	//<algorithm> sort, ���� �Լ� ���
	switch (sort_option)
	{
	case 1: //sort by name
		sort(students.begin(), students.end(), [](Student& a, Student& b) {
			return a.get_student_name() < b.get_student_name();
			});
		break;

	case 2: //sort by student ID
		sort(students.begin(), students.end(), [](Student& a, Student& b) {
			return a.get_id() < b.get_id();
			});
		break;

	case 3: //sort by birth year
		sort(students.begin(), students.end(), [](Student& a, Student& b) {
			return a.get_birth_year() < b.get_birth_year();
			});
		break;

	case 4: //sort by department name
		sort(students.begin(), students.end(), [](Student& a, Student& b) {
			return a.get_department() < b.get_department();
			});
		break;

	default:
		break;
	}
}

void Student_DB::show_selected_data() //- for Student_DB::search_student_data()
{
	cout << setw(15) << left << "Student Name" << " " << setw(10) << "StudentID"
		<< " " << setw(25) << left << "Department" " " << setw(10)
		<< "Birth year" << "  " << setw(12) << "Tel" << endl;
	for (auto& s : _selected)
	{
		cout << setw(15) << left << s.get_student_name() << " "
			<< setw(10) << s.get_id() << " " << setw(24) << s.get_department()
			<< " " << setw(10) << right << s.get_birth_year()
			<< "  " << setw(12) << left << s.get_tel() << endl;
	}
	cout << "\n";
}

void Student_DB::search_student_data(int select_option) //search and print
{
	//flow :: select -> _selected.push -> _selected print -> _selected.clear
	//.compare() :: string equal -> 0

	string keyword; //Search keyword
	string addmission_year; //�й� �� 4�ڸ�
	string last_name; //�ʼ� �˻��� string

	//============= select process =============
	switch (select_option)
	{
	case 1: //Search by name
		cout << "Name keyword ? "; //get key word
		cin.ignore();
		getline(cin, keyword); //�̸��� space�� �����ϹǷ� getline���� �޴´�.
		for (auto& s : students) //check each student and select (same with under code)
		{
			if (s.get_student_name().compare(keyword) == 0)
				_selected.push_back(s);
		}
		break;

	case 2: //Search by Student ID
		cout << "Student ID keyword ? ";
		cin >> keyword;
		for (auto& s : students)
		{
			if (s.get_id().compare(keyword) == 0)
				_selected.push_back(s);
		}
		break;

	case 3: //Search by Addmission year
		cout << "Addmission year keyword ? ";
		cin >> keyword;
		for (auto& s : students)
		{
			addmission_year = (s.get_id()).substr(0, 4); //�й� �� 4�ڸ� ����
			if (addmission_year.compare(keyword) == 0)
				_selected.push_back(s);
		}
		break;

	case 4: //Search by birth year
		cout << "birh year keyword ? ";
		cin >> keyword;
		for (auto& s : students)
		{
			if (s.get_birth_year().compare(keyword) == 0)
				_selected.push_back(s);
		}
		break;

	case 5: //Search by Department name
		cout << "Department name keyword ? ";
		cin.ignore();
		getline(cin, keyword); //department�� space�� ����ϱ⿡ getline���� �޴´�.
		for (auto& s : students)
		{
			if (s.get_department().compare(keyword) == 0)
				_selected.push_back(s);
		}
		break;

	case 6:
		cout << "Last name ? ";
		cin >> keyword;
		for (auto& s : students)
		{
			last_name = (s.get_student_name()).substr(0, keyword.length());
			if (last_name.compare(keyword) == 0)
				_selected.push_back(s);
		}
		break;

	case 7: 
		cout << "Substring keyword ? ";
		cin.ignore();
		getline(cin, keyword);
		for (auto& s : students)
		{
			if (s.get_student_name().find(keyword) != string::npos)
				_selected.push_back(s);
		}
		break;

	case 8: //idea :: List All : select all == students
		_selected = students;
		break;

	default:
		cout << "Invalid option\n";
		break;
	}

	//============= sort -> print -> clear =============
	sort_selected_data(sort_option);
	show_selected_data();
	_selected.clear();
}

void Student_DB::sort_selected_data(int sort_option) //���� sort_students_data()���� students->_selected�θ� ����
{
	//<algorithm> sort, ���� �Լ� ���
	switch (sort_option)
	{
	case 1: //sort by name
		sort(_selected.begin(), _selected.end(), [](Student& a, Student& b) {
			return a.get_student_name() < b.get_student_name();
			});
		break;

	case 2: //sort by student ID
		sort(_selected.begin(), _selected.end(), [](Student& a, Student& b) {
			return a.get_id() < b.get_id();
			});
		break;

	case 3: //sort by birth year
		sort(_selected.begin(), _selected.end(), [](Student& a, Student& b) {
			return a.get_birth_year() < b.get_birth_year();
			});
		break;

	case 4: //sort by department name
		sort(_selected.begin(), _selected.end(), [](Student& a, Student& b) {
			return a.get_department() < b.get_department();
			});
		break;

	default:
		break;
	}
}

void display_menu()
{
	cout << "1. Insertion\n";
	cout << "2. Search\n";
	cout << "3. Sorting Option\n";
	cout << "4. Exit\n";
	cout << "> ";
}

void display_search_option()
{
	cout << "1. Search by name\n";
	cout << "2. Search by student ID\n";
	cout << "3. Search by admission year\n";
	cout << "4. Search by birth year\n";
	cout << "5. Search by department name\n";
	cout << "6. Search by Last name\n";
	cout << "7. Search by Substring\n";
	cout << "8. List All\n\n";
	cout << "> ";
}

void display_sorting_option()
{
	cout << "- Sorting Option\n";
	cout << "1. Sort by Name\n";
	cout << "2. Sort by Student ID\n";
	cout << "3. Sort by Birth Year\n";
	cout << "4. Sort by Department\n";
	cout << "> ";
}