#pragma once
using namespace std;
struct Date
{
	int day;
	int month;
	int year;
};
struct Sched
{
	int no;
	std::string ID;
	std::string name;
	std::string classroom;
	std::string lecuser;
	std::string lecturer;
	std::string deg;
	std::string gender;
	Date start;
	Date end;
	std::string weekday;
	int strhr;
	int strmin;
	int endhr;
	int endmin;
	std::string room;
};
struct Sem
{
	int startyear;
	int endtyear;
	std::string HK;
};
struct Nodesched
{
	Sched data;
	Nodesched* prev, * next;
};
struct list
{
	Nodesched* head;
	Nodesched* tail;
	list()
	{
		head = nullptr;
		tail = nullptr;
	}
};
struct Student
{
	int stdId;
	int pass;
	char lstn[101];
	char frsn[101];
	char gender[20];
	Date DoB;
	string Class;
	int status;
	Student* next;
};
struct Node
{
	Student data;
	struct Node* next;
	struct Node* prev;
};
struct LinkedList
{
	Node* head;
	Node* tail;
};
void initialList(LinkedList& lst);
Node* createNode(Student x);
void addStudentToLast(LinkedList& lst, Node* p);
void readDate(fstream& filein, Date& date);
void readOneStudent(fstream& filein, Student& std);
void readListStudent(fstream& filein, LinkedList& lst);
void outputStudent(Student std);
void outputList(LinkedList lst);
void addStudent(LinkedList& lst, Student std);
void addStudentToFile(fstream& myfile, LinkedList& lst, Student& std);
//void addOneStudent(Student std);
void inputStudentInfo(Student& std);
void updateStudent(LinkedList& lst, int id);
//void save(fstream& myfile, LinkedList lst);
void importCsvToTxt();
void save1(fstream& myfile, LinkedList lst);
void copyData(Node* k, Student& std);
void order(Node** head);
void ejacuList(Nodesched* head, string title, int op);
void interCourse(fstream& filein, Sched& sched);
void readList(fstream& filein, list& lst, bool op);
void readDateFromFile(fstream& filein, Date& date);
void add(Nodesched** head, Sched x);
void extractSemenster(fstream& file, Sched& sched);
void readSemenster(fstream& filein, list& lst);
string match(Sched sched);
int datefrom(int d, int m, int y);
void attendance(int d, int m, int y, int starthr);
void insertDate(Sched sched);
void CheckAttendance(Sched sched, Student x, fstream& file);
int CheckAttendanceElectricBoogaloo(int x, string y);
void getattendants(Sched sched, string title, string s);
void arcyear();
int* diffdate(int d1, int m1, int y1, int dif);
void clitorList(fstream& filein, Nodesched** head);
void AddtoTxt(Sched sched, string title);
void edit(Nodesched* head, string change, string title);
void eradicate(Nodesched** head, string eradicant, string title);
void kick(fstream& filein, fstream& fileout, bool op);
void addendant(string title, Sched sched);
void viewCourseInfo();