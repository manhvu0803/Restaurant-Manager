#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include"Header.h"
#include <sstream>
using namespace std;
void add(Nodesched** head, Sched x)
{
	Nodesched* p = new Nodesched();
	p->data = x;
	p->next = *head;
	p->prev = nullptr;
	if (*head != nullptr)
	{
		(*head)->prev = p;
	}
	*head = p;
}
void eradicate(Nodesched** head, string eradicant, string title)
{
	Nodesched* p = *head;
	ostringstream ss;
	while (ss << p->data.ID << p->data.name << p->data.classroom << p->data.lecuser << p->data.lecturer << p->data.deg << p->data.room << p->data.gender, ss.str().find(eradicant) != string::npos)
	{
		cout << p->data.ID << "\nConfirm?(0/1) ";
		int n;
		cin >> n;
		if (n == 0)
			break;
		*head = p->next;
		delete p;
		p = *head;
		ejacuList(*head, title, 1);
		return;
	}	
	while (p->next != nullptr)
	{
		ss << p->next->data.ID << p->next->data.name << p->next->data.classroom << p->next->data.lecuser << p->next->data.lecturer << p->next->data.deg << p->next->data.room << p->next->data.gender;
		if (ss.str().find(eradicant) != string::npos)
		{
			cout << p->next->data.ID << "\nConfirm?(0/1) ";
			int n;
			cin >> n;
			if (n == 0)
				p = p->next;
			else
			{
				Nodesched* temp = p->next;
				p->next = temp->next;
				delete temp;
				ejacuList(*head, title, 1);
				return;
			}
		}
		else p = p->next;
	}
}
void AddtoTxt(Sched sched, string title)
{
	Nodesched* p = new Nodesched();
	p->data = sched;
	ejacuList(p, title, 0);
	delete p;
}
void edit(Nodesched* head, string change, string title)
{
	cout << "Operator:\nChange ID: 1\nChange name: 2\nChange lecturer's username: 3\nChange lecturer: 4\nChange starting date: 5\nChange ending date: 6\nChange weekday: 7\nChange starting time: 8\nChange ending time: 9\nChange room: 10\nCancel operation or select new item: Any sodding number\n";
	Nodesched* p = head;
	while (p != nullptr)
	{
		ostringstream ss;
		ss << p->data.ID << p->data.name << p->data.classroom << p->data.lecuser << p->data.lecturer << p->data.deg << p->data.room << p->data.gender;
		if (ss.str().find(change) != string::npos)
		{
			cout << p->data.ID << "\n";
			int n = 1;
			while (n != 0)
			{
			cout << "Input operation: ";
			cin >> n;
			switch (n)
			{
			case 1:
				cout << "New ID: ";
				cin >> p->data.ID;
				break;
			case 2:
				cout << "New name: ";
				cin >> p->data.name;
				break;
			case 3:
				cout << "New lecturer's username: ";
				cin >> p->data.lecuser;
				break;
			case 4:
				cout << "New lecturer's name: ";
				cin >> p->data.lecturer;
				cout << "New lecturer's degree: ";
				cin >> p->data.deg;
				cout << "New lecturer's gender: ";
				cin >> p->data.gender;
				break;
			case 5:
				cout << "New starting date: ";
				cin >> p->data.start.day;
				cin >> p->data.start.month;
				cin >> p->data.start.year;
				break;
			case 6:
				cout << "New ending date: ";
				cin >> p->data.end.day;
				cin >> p->data.end.month;
				cin >> p->data.end.year;
				break;
			case 7:
				cout << "New weekday: ";
				cin >> p->data.weekday;
				break;
			case 8:
				cout << "New starting time: ";
				cin >> p->data.strhr >> p->data.strmin;
				break;
			case 9:
				cout << "New ending time: ";
				cin >> p->data.endhr >> p->data.endmin;
				break;
			case 10:
				cout << "New room: ";
				cin >> p->data.room;
				break;
			default:
				n = 0;
			}
			}
		}
		p = p->next;
	}
	ejacuList(head, title, 1);
}
void ejacuList(Nodesched* head, string title, int op)
{
	fstream file;
	if (op == 0)
		file.open(title, ios::app);
	else if (op == 1)
		file.open(title, ios::out);
	Nodesched* p = head;
	while (p != nullptr)
	{
		Sched sched = p->data;
		file << sched.ID << "\n";
		file << sched.name << "\n";
		file << sched.classroom << "\n";
		file << sched.lecuser << "\n";
		file << sched.lecturer << "\n";
		file << sched.deg << "\n";
		file << sched.gender << "\n";
		file << sched.start.day << "/" << sched.start.month << "/" << sched.start.year << "-" << sched.end.day << "/" << sched.end.month << "/" << sched.end.year << "\n";
		if (sched.weekday == "Monday")
			file << 2 << "\n";
		else if (sched.weekday == "Tuesday")
			file << 3 << "\n";
		else if (sched.weekday == "Wednesday")
			file << 4 << "\n";
		else if (sched.weekday == "Thursday")
			file << 5 << "\n";
		else if (sched.weekday == "Friday")
			file << 6 << "\n";
		else if (sched.weekday == "Saturday")
			file << 7 << "\n";
		else if (sched.weekday == "Sunday")
			file << 8 << "\n";
		file << sched.strhr << ":" << sched.strmin << "-" << sched.endhr << ":" << sched.endmin << "\n";
		file << sched.room << "\n";
		p = p->next;
	}
	file.close();
}
void clitorList(fstream& filein, Nodesched** head)
{
		Sched sched;
		getline(filein, sched.ID, '\n');
		getline(filein, sched.name, '\n');
		getline(filein, sched.classroom, '\n');
		getline(filein, sched.lecuser, '\n');
		getline(filein, sched.lecturer, '\n');
		getline(filein, sched.deg, '\n');
		getline(filein, sched.gender, '\n');
		readDateFromFile(filein, sched.start);
		readDateFromFile(filein, sched.end);
		int wd;
		filein >> wd;
		if (wd == 2)
			sched.weekday = "Monday";
		if (wd == 3)
			sched.weekday = "Tuesday";
		if (wd == 4)
			sched.weekday = "Wednesday";
		if (wd == 5)
			sched.weekday = "Thursday";
		if (wd == 6)
			sched.weekday = "Friday";
		if (wd == 7)
			sched.weekday = "Saturday";
		if (wd == 8)
			sched.weekday = "Sunday";
		filein.seekg(1, filein.cur);
		filein >> sched.strhr;
		filein.seekg(1, filein.cur);
		filein >> sched.strmin;
		filein.seekg(1, filein.cur);
		filein >> sched.endhr;
		filein.seekg(1, filein.cur);
		filein >> sched.endmin;
		filein.seekg(1, filein.cur);
		filein.seekg(1, filein.cur);
		getline(filein, sched.room, '\n');
		filein.seekg(1, filein.cur);
		add(head, sched);
		if (filein.peek() == EOF)
			return;
		filein.seekg(-1, filein.cur);
}
void interCourse(fstream& filein, Sched& sched)
{
	string line;
	filein >> sched.no;
	filein.seekg(1, filein.cur);
	getline(filein, sched.ID,';');
	getline(filein, sched.name, ';');
	getline(filein, sched.classroom, ';');
	getline(filein, sched.lecuser, ';');
	getline(filein, sched.lecturer, ';');
	getline(filein, sched.deg, ';');
	getline(filein, sched.gender, ';');
	readDateFromFile(filein, sched.start);
	readDateFromFile(filein, sched.end);
	getline(filein, sched.weekday, ';');
	filein >> sched.strhr;
	filein.seekg(1, filein.cur);
	filein >> sched.strmin;
	filein.seekg(1, filein.cur);
	filein >> sched.endhr;
	filein.seekg(1, filein.cur);
	filein >> sched.endmin;
	filein.seekg(1, filein.cur);
	getline(filein, sched.room,'\n');
	if (filein.peek() == EOF)
		return;
	filein.seekg(-1, filein.cur);
}
void readList(fstream& filein, list& lst, bool op)
{
	int i = 0;
	while (filein.good() && op)
	{
		filein.ignore(SIZE_MAX, '\n');
		if (filein.peek() == EOF)
			return;
		Sched sched;
		interCourse(filein, sched);
		add(&lst.head, sched);
	}
	while (filein.good() && op == false)
	{
		if (filein.peek() == EOF)
			return;
		clitorList(filein, &lst.head);
	}
}
void readDate(fstream& filein, Date& date)
{
	filein >> date.day;
	filein.seekg(1, filein.cur);
	filein >> date.month;
	filein.seekg(1, filein.cur);
	filein >> date.year;
	filein.seekg(1, filein.cur);
}
void arcyear()
{
	fstream file("Semester.txt", ios::out);
	int startyear;
	int endyear;
	string semester;
	string classroom;
	cout << "Input starting year: ";
	cin >> startyear;
	cout << "Input ending year: ";
	cin >> endyear;
	cout << "Input semester: ";
	cin >> semester;
	file << startyear << "-" << endyear << "-" << semester<<"\n";
	file.close();
}
void extractSemenster(fstream& file, Sched& sched)
{
	file >> sched.strhr;
	file.seekg(1, file.cur);
	file >> sched.endhr;
	file.seekg(1, file.cur);
	getline(file, sched.room, '\n');
	if (file.peek() == EOF)
		return;
	file.seekg(-1, file.cur);
}
void readSemenster(fstream& filein, list& lst)
{
	int i = 0;
	while (filein.good())
	{
		if (filein.peek() == EOF)
			return;
		Sched sched;
		extractSemenster(filein, sched);
		add(&lst.head, sched);
	}
}
string match(Sched sched)
{
	fstream file("Semester.txt", ios::in);
	list sem;
	readSemenster(file, sem);
	file.close();
	Nodesched* p2 = sem.head;
		while (p2 != nullptr)
		{
			if (sched.start.year == p2->data.strhr || sched.start.year == p2->data.endhr)
			{
				ostringstream ss;
				ss << p2->data.strhr << "-" << p2->data.endhr << "-" << p2->data.room << "-"<<sched.classroom;
				return ss.str();
				p2 = p2->next;
			}
			else p2 = p2->next;
		}
}
void initialList(LinkedList& lst)
{
	lst.head = nullptr;
	lst.tail = nullptr;
}
Node* createNode(Student x)
{
	Node* p = new Node;
	if (p == nullptr)
	{
		cout << "Update failed!";
		return nullptr;
	}
	p->data = x;
	p->next = nullptr;
	return p;
}
void addStudentToLast(LinkedList& lst, Node* p)
{
	if (lst.head == nullptr)
	{
		lst.head = lst.tail = p;
	}
	else
	{
		lst.tail->next = p;
		lst.tail = p;
	}
}
void readDateFromFile(fstream& filein, Date& date)
{
	filein >> date.day;
	filein.seekg(1, filein.cur);
	filein >> date.month;
	filein.seekg(1, filein.cur);
	filein >> date.year;
	filein.seekg(1, filein.cur);
}
void readOneStudentFromFile(fstream& filein, Student& std)
{
	string line;
	filein.seekg(1, 1);
	filein.seekg(1, 1);
	filein >> std.stdId;
	filein.seekg(1, 1);
	filein.getline(std.lstn, 101, ';');
	filein.getline(std.frsn, 101, ';');
	filein.getline(std.gender, 20, ';');
	readDateFromFile(filein, std.DoB);
	getline(filein, line);
}
void readOneStudent(fstream& filein, Student& std)
{
	string line;
	filein >> std.stdId;
	getline(filein, line);
	filein >> std.pass;
	getline(filein, line);
	filein.getline(std.lstn, 101, '\n');
	filein.getline(std.frsn, 101, '\n');
	filein.getline(std.gender, 20, '\n');
	readDateFromFile(filein, std.DoB);
	getline(filein, line);
	getline(filein, std.Class, '\n');
	filein >> std.status;
	getline(filein, line);
	getline(filein, line);
}
void readListStudentFromFile(fstream& filein, LinkedList& lst)
{
	char line[101];
	if (filein.good())
	{
		filein.getline(line, 101, '\n');
	}
	while (filein.good())
	{
		Student std;
		readOneStudentFromFile(filein, std);
		Node* p = createNode(std);
		addStudentToLast(lst, p);
	}
}
void readListStudent(fstream& filein, LinkedList& lst)
{
	int i = 0;
	while (filein.good())
	{
		Student std;
		readOneStudent(filein, std);
		Node* p = createNode(std);
		addStudentToLast(lst, p);
	}
}
void outputStudent(Student std)
{
	cout << "Student ID: " << std.stdId << endl;
	cout << "Name: " << std.lstn << " " << std.frsn << endl;
	cout << "Gender: " << std.gender << endl;
	cout << "Date of birth: " << std.DoB.day << "/" << std.DoB.month << "/" << std.DoB.year << endl;
	cout << "Class: " << std.Class << endl;
	cout << "-------------------" << '\n';
}
void outputList(LinkedList lst)
{
	int count = 0;
	cout << "List of student" << endl;
	Node* k = lst.head;
	do
	{
		count++;
		cout << "No: " << count << endl;
		outputStudent(k->data);
		k = k->next;
	} while (k != nullptr);
}
int setPass(int year, int month, int day)
{
	return 10000 * year + 100 * month + day;
}
void addStudent(LinkedList& lst, Student std)
{
	string filename, filename1, file1;
	cin.ignore();
	cout << "Input class you want to import: ";
	getline(cin, filename);
	filename1 = filename;
	file1 = filename.append(".txt");
	fstream filein(file1, ios::app);
	inputStudentInfo(std);
	std.Class = filename1;
	addStudentToFile(filein, lst, std);
}
void addStudentToFile(fstream& myfile, LinkedList& lst, Student& std)
{
	if (myfile.is_open())
	{
		myfile << std.stdId << "\n";
		myfile << std.pass << "\n";
		myfile << std.lstn << "\n";
		myfile << std.frsn << "\n";
		myfile << std.gender << "\n";
		myfile << std.DoB.day << "/";
		myfile << std.DoB.month << "/";
		myfile << std.DoB.year << "\n";
		myfile << std.Class << "\n";
		myfile << std.status << "\n";
		myfile << endl;
		myfile.close();
		Node* p = createNode(std);
		addStudentToLast(lst, p);
	}
	myfile.close();
}
void inputStudentInfo(Student& std)
{
	cout << "Enter student ID: ";
	cin >> std.stdId;
	cin.ignore();
	cout << "Enter lastname: ";
	cin.getline(std.lstn, 101);
	cout << "Enter firstname: ";
	cin.getline(std.frsn, 101);
	cout << "Enter gender: ";
	cin.getline(std.gender, 20);
	cout << "Enter day month year: ";
	cin >> std.DoB.day;
	cin >> std.DoB.month;
	cin >> std.DoB.year;
	std.pass = setPass(std.DoB.year, std.DoB.month, std.DoB.day);
	std.status = 1;
}
//void addOneStudent(Student std)
//{
//	fstream myfile("19CLC7.txt", ios::app);
//	string line;
//	if (myfile.is_open())
//	{
//		myfile << std.stdId << "\n";
//		myfile << std.lstn << "\n";
//		myfile << std.frsn << "\n";
//		myfile << std.gender << "\n";
//		myfile << std.DoB.day << "/";
//		myfile << std.DoB.month << "/";
//		myfile << std.DoB.year;
//		myfile << endl;
//		myfile.close();
//	}
//}
void copyData(Node* k, Student& std)
{
	k->data.stdId = std.stdId;
	strcpy_s(k->data.lstn, std.lstn);
	strcpy_s(k->data.frsn, std.frsn);
	strcpy_s(k->data.gender, std.gender);
	k->data.DoB.day = std.DoB.day;
	k->data.DoB.month = std.DoB.month;
	k->data.DoB.year = std.DoB.year;
	k->data.pass = setPass(std.DoB.year, std.DoB.month, std.DoB.day);
	k->data.status = std.status;
	k->data.Class = std.Class;
}
void updateStudent(LinkedList& lst, int id)
{
	Student std;
	LinkedList lst1 = lst;
	string filename, filename1, file1;
	cin.ignore();
	cout << "Input class you want to import: ";
	getline(cin, filename);
	filename1 = filename;
	file1 = filename.append(".txt");
	cout << file1 << endl;
	fstream filein(file1, ios::in);
	fstream filein1("temp.txt", ios::out);
	if (filein.is_open())
	{
		for (Node* k = lst1.head; k->next != nullptr; k = k->next)
		{
			if (id == k->data.stdId)
			{
				outputStudent(k->data);
				inputStudentInfo(std);
				std.Class = filename1;
				copyData(k, std);
			}
		}
	}
	save1(filein1, lst1);
	filein1.close();
	filein.close();
	filein.open(file1, ios::out);
	filein1.open("temp.txt", ios::in);
	save1(filein, lst);
	filein1.close();
	filein.close();
	remove("temp.txt");
}
void importCsvToTxt()
{
	LinkedList lst1;
	Student std;
	string filename, filename1, filename2, file1, file2;
	fstream filein;
	fstream filein1;
	cin.ignore();
	cout << "Input name of the csv file you want to import: ";
	getline(cin, filename);
	filename2 = filename1 = filename;
	file1 = filename.append(".txt");
	file2 = filename1.append(".csv");
	filein.open(file1, ios::app);
	filein1.open(file2, ios::in);
	initialList(lst1);
	readListStudentFromFile(filein1, lst1);
	for (Node* i = lst1.head; i != nullptr; i = i->next)
	{
		i->data.Class = filename2;
		i->data.status = 1;
	}
	save1(filein, lst1);
	filein1.close();
	filein.close();
	fstream classtxt("Class.txt", ios::app);
	classtxt << filename2 << endl;
	classtxt.close();
}
//void delList(LinkedList& lst, fstream& filein)
//{
//	Node* current = lst.head;
//	Node* next;
//	if (filein.is_open())
//	{
//		while (current != NULL)
//		{
//			next = current->next;
//			free(current);
//			current = next;
//		}
//		lst.head = NULL;
//	}
//	save(filein, lst);
//}
//void save(fstream& myfile,LinkedList lst)
//{
//	Node* std = lst.head;
//	while (std->next != nullptr)
//	{
//			myfile << std->data.stdId << ";";
//			myfile << std->data.lstn << ";";
//			myfile << std->data.frsn << ";";
//			myfile << std->data.gender << ";";
//			myfile << std->data.DoB.day << "/";
//			myfile << std->data.DoB.month << "/";
//			myfile << std->data.DoB.year;
//			myfile << endl;
//			std = std->next;
//	}
//}
void save1(fstream& myfile, LinkedList lst)
{
	if (lst.head == nullptr)
	{
		cout << "Error Open File" << endl;
		return;
	}
	Node* std = lst.head;
	while (std->next != nullptr)
	{
		myfile << std->data.stdId << "\n";
		myfile << setPass(std->data.DoB.year, std->data.DoB.month, std->data.DoB.day) << "\n";
		myfile << std->data.lstn << "\n";
		myfile << std->data.frsn << "\n";
		myfile << std->data.gender << "\n";
		myfile << std->data.DoB.day << "/";
		myfile << std->data.DoB.month << "/";
		myfile << std->data.DoB.year << "\n";
		myfile << std->data.Class << "\n";
		myfile << std->data.status << "\n";
		myfile << endl;
		std = std->next;
	}
}
void order(Node** head)
{
	Node* p = *head;
	Node* lptr = nullptr;
	int i;
	while (*head == nullptr)
		return;
	do
	{
		p = *head;
		i = 0;
		while (p->next != lptr)
		{
			if (p->next->data.stdId < p->data.stdId)
			{
				Node* temp = new Node();
				temp->data = p->data;
				p->data = p->next->data;
				p->next->data = temp->data;
				i = 1;
				delete temp;
			}
			p = p->next;
		}
		lptr = p;
	} while (i);
}
int datefrom(int d, int m, int y)
{
	int leap, day = 0, i;
	if (m > 2)
	{
		day += 58;
		leap = y / 4 - y / 100 + y / 400;
		for (i = 3; i < m; ++i)
		{
			if (i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
				day += 31;
			else
				day += 30;
		}
	}
	else
	{
		leap = (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
		if (m == 2)
			day += 31;
	}
	day += y * 365 + leap + d;
	return day;
}
int* diffdate(int d1, int m1, int y1, int dif)
{
	int d2, m2, y2, from, n, rem, i;
	int month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	from = datefrom(d1, m1, y1);
	n = from + dif;
	y2 = n / 365.25;
	rem = n - datefrom(0, 0, y2);
	if ((y2 % 4 == 0 && y2 % 100 != 0) || y2 % 400 == 0)
		month[2] = 29;
	for (i = 1; i <= 12; ++i)
	{
		if (rem <= month[i])
			break;
		rem = rem - month[i];
	}
	d2 = rem;
	m2 = i;
	if (m2 == 13)
	{
		m2 = 1;
		y2 += 1;
	}
	int date[3] = { d2, m2, y2 };
	return date;
}
void insertDate(Sched sched)
{
	ostringstream ss;
	ss << sched.name << "-" << sched.classroom << "-Periods.txt";
	fstream file(ss.str(), ios::app);
	int d;
	do
	{
		cout << "Insert day: ";
		cin >> d;
		if (d == 0)
			return;
		cout << "Insert month: ";
		int m;
		cin >> m;
		cout << "Insert year: ";
		int y;
		cin >> y;
		cout << "Start hour: ";
		int starthr;
		cin >> starthr;
		cout << "Start minute: ";
		int startmin;
		cin >> startmin;
		cout << "End hour: ";
		int endhr;
		cin >> endhr;
		cout << "End minute: ";
		int endmin;
		cin >> endmin;
		file << y << " " << m << " " << d << " " << starthr << " " << startmin << " " << endhr << " " << endmin << "\n";
		attendance(d, m, y, starthr);
	} while (d != 0);
	file.close();
}
void attendance(int d, int m, int y, int starthr)
{
	ostringstream ss;
	ss << y << m << d << starthr << ".txt";
	fstream file(ss.str(), ios::out);
	cout << "Insert absentees' IDs (insert 0 to stop):  ";
	int x;
	do
	{
		cin >> x;
		file << x << "\n";
		cin.clear();
	} while (x != 0);
	file.close();
}
void CheckAttendance(Sched sched, Student x, fstream& file)
{
	ostringstream period;
	period << sched.name << "-" << sched.classroom << "-Periods.txt";
	fstream periods(period.str(), ios::in);
	while (periods.good())
	{
		int sthr, stmin, endhr, endmin;
		Date y;
		periods >> y.year;
		periods >> y.month;
		periods >> y.day;
		periods >> sthr;
		periods >> stmin;
		periods >> endhr;
		periods >> endmin;
		ostringstream ss;
		ss << y.year << y.month << y.day << sthr<<".txt";
		if (periods.peek() == EOF)
			break;
		file << y.year << " " << y.month << " " << y.day << " " << sthr << " " << stmin << " " << endhr << " " << endmin << " " << 0 << "\n";
	}
	periods.close();
}
int CheckAttendanceElectricBoogaloo(int x, string y)
{
	fstream file(y, ios::in);
	int z;
	while (file.good())
	{
		file >> z;
		if (z == x)
			return -1;
	}
	return 1;
}
void getattendants(Sched sched, string title, string s)
{
	string blah;
	blah.append(s).append(".txt");
	fstream stud(blah, ios::in);
	LinkedList lst;
	initialList(lst);
	readListStudent(stud, lst);
	stud.close();
	title.append("-");
	title.append(s);
	title.append("-");
	title.append(sched.ID);
	title.append(".txt");
	fstream file(title, ios::out);
	int count = 1;
	Node* p = lst.head;
	while (p != nullptr)
	{
		file << p->data.stdId << "\n";
		file << p->data.frsn << " " << p->data.lstn << "\n";
		file << 1 << "\n" << -1 << "\n" << -1 << "\n" << -1 << "\n" << -1 << "\n" << 1 << "\n";
		for (int i = 0; i < 9; i++)
		{
			int* date = diffdate(sched.start.day + 1, sched.start.month, sched.start.year, i * 7);
			file << date[2] << " " << date[1] << " " << date[0] << " " << sched.strhr << " " << sched.strmin << " " << sched.endhr << " " << sched.endmin << " " << 0 << "\n";
		}
		file << "\n";
		p = p->next;
		count++;
	}
	file.close();
}
void ejacuList2(Node* head, string title, Sched sched)
{
	fstream file(title, ios::app);
	int count = 1;
	Node* p = head;
	while (p != nullptr)
	{
		file << p->data.stdId << "\n";
		file << p->data.frsn << " " << p->data.lstn << "\n";
		file << 1 << "\n" << -1 << "\n" << -1 << "\n" << -1 << "\n" << -1 << "\n" << 1 << "\n";
		for (int i = 0; i < 9; i++)
		{
			int* date = diffdate(sched.start.day, sched.start.month, sched.start.year, i * 7);
			file << date[2] << " " << date[1] << " " << date[0] << " " << sched.strhr << " " << sched.strmin << " " << sched.endhr << " " << sched.endmin << " " << 0 << "\n";
		}
		file << "\n";
		p = p->next;
		count++;
	}
	file.close();
}
void kick(fstream& filein, fstream& fileout, bool op)
{
	string out;
	if (op)
	{
		cout << "Input ID: ";
		cin.ignore();
		cin >> out;
	}
	string line;
	while (filein.good())
	{
		if (filein.peek() == EOF)
			return;
		int x = filein.tellg();
		getline(filein, line, '\n');
		if (line.compare(out) == 0 && op)
		{
			filein.seekg(x, filein.beg);
			for (int i = 0; i < 18; i++)
			filein.ignore(SIZE_MAX, '\n');
			getline(filein, line, '\n');
			op = false;
		}
		fileout << line <<"\n";
	}
}
void addendant(string title, Sched sched)
{
	string id;
	cout << "Input student's ID: ";
	cin >> id;
	cin.ignore();
	string name;
	cout << "Input student's name: ";
	getline(cin, name, '\n');
	fstream file(title, ios::app);
	file << id << "\n";
	file << name << "\n";
	file << 1 << "\n" << -1 << "\n" << -1 << "\n" << -1 << "\n" << -1 << "\n" << 1 << "\n";
	for (int i = 0; i < 9; i++)
	{
		int* date = diffdate(sched.start.day + 1, sched.start.month, sched.start.year, i * 7);
		file << date[2] << " " << date[1] << " " << date[0] << " " << sched.strhr << " " << sched.strmin << " " << sched.endhr << " " << sched.endmin << " " << 0 << "\n";
	}
	file << "\n";
	file.close();
}
void outputCourseInfo(Sched sched)
{
	cout << "\nCourse ID: " << sched.ID << endl;
	cout << "Course Name: " << sched.name << endl;
	cout << "Class: " << sched.classroom << endl;
	cout << "Lecterer's user: " << sched.lecuser << endl;
	cout << "Lecturer's Name: " << sched.lecturer << endl;
	cout << "Degree: " << sched.deg << endl;
	cout << "Gender: " << sched.gender << endl;
	cout << "Period: " << sched.start.day << "/" << sched.start.month << "/" << sched.start.year << " - " << sched.end.day << "/" << sched.end.month << "/" << sched.end.year << endl;
	cout << "Day of week: " << sched.weekday << endl;
	cout << "Hour: " << sched.strhr << ":" << sched.strmin << " - " << sched.endhr << ":" << sched.endmin << endl;
	cout << "Room: " << sched.room << endl;
}
void outputListCourseInfo(list lst)
{
	if (lst.head == nullptr)
	{
		cout << "Error Open File" << endl;
		return;
	}
	int count = 0;
	Nodesched* k;
	k = lst.head;
	do
	{
		outputCourseInfo(k->data);
		k = k->next;
	} while (k != nullptr);
	cout << "------------------" << endl;
}
void viewCourseInfo()
{
	list lst1;
	string course;
	course = "Course";
	course.append(".txt");
	fstream file(course, ios::in);
	readList(file, lst1, false);
	file.close();
	outputListCourseInfo(lst1);
}