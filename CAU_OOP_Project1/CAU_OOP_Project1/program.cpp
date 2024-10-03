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
	string name; //학생 이름
	string student_id; //학생 ID
	string Birth_year; //학생 탄생년도
	string Department; //학생이 속한 학부
	string Tel;

public:
	//객체 생성자, Maual input의 값이 항상 올바르다는 것을 가정하고 생성자를 구성함
	Student() {}

	Student(string name, string student_id, string Birth_year, string Department, string Tel)
	{
		this->name = name;
		this->student_id = student_id;
		this->Birth_year = Birth_year;
		this->Department = Department;
		this->Tel = Tel;
	}
	//파일에 insert할 때 사용할 Getter
	string get_student_name() { return name; }
	string get_id() { return student_id; }
	string get_Birth_year() { return Birth_year; }
	string get_Department() { return Department; };
	string get_tel() { return Tel; };
	//insert 할 때 임시 class에 입력 값을 주기 위핸 Mutator이 필요.
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

// 프로그램의 기능에 직접적으로 영향을 주는 함수들
void file_tracker(const string& f_name);
Student get_input_student();
bool compare_birth_year(Student& a, Student& b);


// 선택 옵션을 보여주는 menu 함수들
void display_menu();
void display_search_option();
void display_sorting_option();

int main(void)
{
	const string f_name = "file1.txt"; //txt 파일의 이름이 a였으므로 파일명을 고정한다.
	ifstream file ("file1.txt");
	
	Student_DB students_db; //students를 DB 객체로 불러왔기 때문에 객체 속의 Vector가 생성
	
	streampos begin, end; //이전에 작성된 txt 파일 속 내용의 유무를 판단하기 위한 척도 변수
	begin = file.tellg();
	file.seekg(0, ios::end);
	end = file.tellg();
	file.close();
	
	if ((end - begin != 0)) //txt파일에 어떤 정보가 들어가있음
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
				//student_db 객체 내로 txt 파일에 있는 내용을 전부 가져온다.
			}
		}

		file.close();
	}

	file_tracker(f_name); //파일 유무 확인 및 생성

	while (1) //메인 화면은 유저가 직접 종료할 때까지 계속해서 보여줘야함
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
	ifstream file(f_name); //f_name의 이름의 파일을 찾기
	if (!file) //없으면 Null을 반환하므로 if문으로 진입
	{
		ofstream student_data(f_name); //ofstream: 파일 쓰기 (없으면 파일 생성)
		student_data.close(); //파일 입출력이 끝난 후 닫아주어야 다른 종류의 stream을 받을 수 있다.
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

	cin.ignore(); //cin 이후 getline을 하기 위해선 cin으로 인한 버퍼 움직임을 초기화해야한다.
	cout << "Department ? ";
	getline(cin, temp_department); //space도 포함하는 input일 때에는 getline을 사용해야한다.
	temp_student.set_Department(temp_department);

	cout << "Tel ? ";
	cin >> temp_tel;
	temp_student.set_telephone(temp_tel);
	cout << "\n";

	return temp_student;
}

void Student_DB :: add_student_data(Student& temp_student) {
	for (auto& exist : students){ //students vector 내를 for문을 돌면서 id가 같은지 보는 과정
		if (exist.get_id() == temp_student.get_id())
		{
			cout << "Error: already inserted\n";
					return;
		}
	}

	students.push_back(temp_student); //위의 탐지 과정에서 중복이 없음이 확인되면 push_back을 한다.
	
	fstream file("file1.txt", ios::app); //txt 파일에 input하기 위해 fstream을 app 상태로 연다.
	if (file.is_open())
	{
		string to_txt_data = temp_student.get_Department(); //Department의 경우 spacing이 있어 나중에 꺼낼 때 콤마로 string을 분리하기위한 작업
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