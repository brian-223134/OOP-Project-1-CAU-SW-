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
	string birth_year; //학생 탄생년도
	string department; //학생이 속한 학부
	string tel; //학생의 연락처

public:
	//============= Constructor =============
	//객체 생성자, Maual input의 값이 항상 올바르다는 것을 가정하고 생성자를 구성함
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
	//파일에 insert할 때 사용할 Getter
	string get_student_name() { return name; }
	string get_id() { return student_id; }
	string get_birth_year() { return birth_year; }
	string get_department() { return department; };
	string get_tel() { return tel; };
	//insert 할 때 임시 class에 입력 값을 주기 위핸 Mutator이 필요.
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

// 선택 옵션을 보여주는 menu 함수들
void display_menu();
void display_search_option();
void display_sorting_option();

int main(void)
{
	const string f_name = "file1.txt"; //txt 파일의 이름이 file1였으므로 파일명을 고정한다.
	ifstream file("file1.txt");
	
	Student_DB students_db; //students를 DB 객체로 불러왔기 때문에 객체 속의 Vector가 생성

	streampos begin, end; //이전에 작성된 txt 파일 속 내용의 유무를 판단하기 위한 척도 변수
	begin = file.tellg();
	file.seekg(0, ios::end);
	end = file.tellg();
	file.close();

	//Synchronize file to students
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
			getline(iss, txt_name, ',');

			if (iss >> txt_student_id >> txt_birth_year >> txt_tel)
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

	//띄어쓰기가 포함된 문자열을 받을 때 getline
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

	cin.ignore(); //cin 이후 getline을 하기 위해선 cin으로 인한 버퍼 움직임을 초기화해야한다.
	cout << "Department ? ";
	getline(cin, temp_department); //space도 포함하는 input일 때에는 getline을 사용해야한다.
	temp_student.set_department(temp_department);

	cout << "Tel ? ";
	cin >> temp_tel;
	temp_student.set_telephone(temp_tel);
	cout << "\n";

	return temp_student;
}

void Student_DB::add_student_data(Student& temp_student) {
	for (auto& exist : students) { //students vector 내를 for문을 돌면서 id가 같은지 보는 과정
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
		string to_txt_data = temp_student.get_department(); //Department의 경우 spacing이 있어 나중에 꺼낼 때 콤마로 string을 분리하기위한 작업
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
	//<algorithm> sort, 람다 함수 사용
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
	string addmission_year; //학번 앞 4자리
	string last_name; //초성 검색용 string

	//============= select process =============
	switch (select_option)
	{
	case 1: //Search by name
		cout << "Name keyword ? "; //get key word
		cin.ignore();
		getline(cin, keyword); //이름은 space가 존재하므로 getline으로 받는다.
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
			addmission_year = (s.get_id()).substr(0, 4); //학번 앞 4자리 추출
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
		getline(cin, keyword); //department도 space를 허용하기에 getline으로 받는다.
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

void Student_DB::sort_selected_data(int sort_option) //기존 sort_students_data()에서 students->_selected로만 변경
{
	//<algorithm> sort, 람다 함수 사용
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