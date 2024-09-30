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
	string name; //학생 이름
	int student_id; //학생 ID
	int Birth_year; //학생 탄생년도
	string Department; //학생이 속한 학부
	int Tel; //학생 연락처

public:

	//객체 생성자, Maual input의 값이 항상 올바르다는 것을 가정하고 생성자를 구성함
	Student() {}

	Student(string name, int student_id, int Birth_year, string Department, int Tel)
	{
		this->name = name;
		this->student_id = student_id;
		this->Birth_year = Birth_year;
		this->Department = Department;
		this->Tel = Tel;
	}

	//파일에 insert할 때 사용할 Getter
	string get_student_name() { return name; }
	int get_id() { return student_id; }
	int get_Birth_year() { return Birth_year; }
	string get_Departmet() { return Department; };
	int get_tel() { return Tel; };

	//insert 할 때 임시 class에 입력 값을 주기 위핸 Mutator이 필요.
	void set_name(string& Name) { name = Name; }
	void set_id(int id) { student_id = id; }
	void set_Birth_year(int B_year) { Birth_year = B_year; }
	void set_Department(string& department) { Department = department; }
	void set_telephone(int telephone) { Tel = telephone; }

};


int main(void)
{
	const string f_name = "a.txt"; //txt 파일의 이름이 a였으므로 파일명을 고정한다.
	ifstream(f_name);
	vector<Student> students; //학생들의 정보를 입력 받는 vector을 생성, vector의 경우 유연한 크기 변화 가능하여 사용

	file_tracker(f_name); //파일 유무 확인 및 생성

	while (1) //메인 화면은 유저가 직접 종료할 때까지 계속해서 보여줘야함
	{
		display_menu();

		//객체의 새로운 데이터를 받기 위해 임시 변수 선언
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
			cin.ignore(); //cin의 경우 '\n'가 남아있으므로 getline 이전에 ignore 처리가 필요
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
	ifstream file(f_name); //f_name의 이름의 파일을 찾기
	if (!file) //없으면 Null을 반환하므로 if문으로 진입
	{
		ofstream student_data(f_name); //ofstream: 파일 쓰기 (없으면 파일 생성)
		student_data.close(); //파일 입출력이 끝난 후 닫아주어야 다른 종류의 stream을 받을 수 있다.
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

	//기존에 중복되는 데이터가 있는지 검사
	for (auto& exist : students)
	{
		if (exist.get_id() == temp_student.get_id())
		{
			cout << "Error: already inserted\n";
			return;
		}
	}

	students.push_back(temp_student); //새로 입력 받은 학생의 정보를 students vector에 저장하기
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
		//파일 입력하기 줄 맞춰서 입력하기 방법 생각하기 
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
