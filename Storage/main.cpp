#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Header.h"
using namespace std;
int main()
{
	fstream file("Semester.txt", ios::in);
	if (file.fail())
		arcyear();
	Sched sem;
	while (file.good())
		extractSemenster(file, sem);
	ostringstream ss;
	ss << sem.strhr << "-" << sem.endhr << "-" << sem.room;
	file.close();
	int n = 1;
	cout << "Commands:\n1: Import csv\n2: Add\n3: Edit\n4: Export student list\n5: Delete\n";
	while (n != 0)
	{
		cout << "Input operation: ";
		cin >> n;
		switch (n)
		{
		case 1:
		{
			list lst;
			cout << "Input class: ";
			string classroom;
			cin >> classroom;
			string title;
			title.append(ss.str()).append("-").append(classroom).append("-Schedule.csv");
			string title2;
			title2.append("Course.txt");
			fstream file2(title, ios::in);
			readList(file2, lst, true);
			Nodesched* p = lst.head;
			while (p != nullptr)
			{
				AddtoTxt(p->data, title2);
				p = p->next;
			}
			file2.close();
			break;
		}
		case 2:
		{
			list lst;
			Nodesched* p = lst.head;
			string title;
			title.append("Course.txt");
			Sched blah;
			cout << "ID: ";
			cin >> blah.ID;
			cin.ignore();
			cout << "Name: ";
			getline(cin, blah.name);
			cout << "Class: ";
			cin >> blah.classroom;
			cout << "Lecturer's username: ";
			cin >> blah.lecuser;
			cin.ignore();
			cout << "Lecturer's name: ";
			getline(cin, blah.lecturer);
			cout << "Lecturer's degree: ";
			cin >> blah.deg;
			cout << "Lecturer's gender: ";
			cin >> blah.gender;
			cout << "Starting date(d m y): ";
			cin >> blah.start.day;
			cin >> blah.start.month;
			cin >> blah.start.year;
			cout << "Ending date(d m y): ";
			cin >> blah.end.day;
			cin >> blah.end.month;
			cin >> blah.end.year;
			cout << "Weekday: ";
			cin >> blah.weekday;
			cout << "Starting time(hr min): ";
			cin >> blah.strhr >> blah.strmin;
			cout << "Ending time (hr min): ";
			cin >> blah.endhr >> blah.endmin;
			cout << "Room: ";
			cin >> blah.room;
			AddtoTxt(blah, title);
			break;
		}
		case 3:
		{
			list lst;
			Nodesched* p = lst.head;
			string title;
			title.append("Course.txt");
			fstream file(title, ios::in);
			readList(file, lst, false);
			file.close();
			cout << lst.head->data.classroom;
			cout << "Search: ";
			string search;
			cin >> search;
			edit(lst.head, search, title);
			break;
		}
		case 4:
		{
			list lst;
			cout << "Input course ID: ";
			string id;
			cin >> id;
			string title;
			title.append("Course.txt");
			fstream file(title, ios::in);
			readList(file, lst, false);
			file.close();
			Nodesched* p = lst.head;
			while (p != nullptr)
			{
				if (id.compare(p->data.ID) == 0)
					getattendants(p->data, ss.str(), p->data.classroom);
				p = p->next;
			}
			break;
		}
		case 5:
		{
			list lst;
			string title;
			title.append("Course.txt");
			fstream file(title, ios::in);
			readList(file, lst, false);
			file.close();
			cout << "Search: ";
			string search;
			cin >> search;
			eradicate(&lst.head, search, title);
			break;
		}
		case 6:
		{
			list lst;
			fstream file("Course.txt", ios::in);
			readList(file, lst, false);
			cout << "Input course ID: ";
			string title;
			string id;
			cin >> id;
			Nodesched* p = lst.head;
			while (p != nullptr)
			{
				if (id.compare(p->data.ID) == 0)
				{
					title.append("2019-2020-HK2-").append(p->data.classroom).append("-").append(p->data.ID).append(".txt");
					break;
				}
				p = p->next;
			}
			fstream out("temp.txt", ios::out);
			fstream in(title, ios::in);
			kick(in, out, true);
			out.close();
			in.close();
			remove(title.c_str());
			rename("temp.txt", title.c_str());
			break;
		}
		case 7:
		{
			list lst;
			fstream file("Course.txt", ios::in);
			readList(file, lst, false);
			cout << "Input course ID: ";
			string title;
			string id;
			cin >> id;
			Nodesched* p = lst.head;
			while (p != nullptr)
			{
				if (id.compare(p->data.ID) == 0)
				{
					title.append("2019-2020-HK2-").append(p->data.classroom).append("-").append(p->data.ID).append(".txt");
					break;
				}
				p = p->next;
			}
			addendant(title, p->data);
			break;
		}
		case 8:
			viewCourseInfo();
			break;
		default:
			n = 0;
			break;
		}
	}
	return 0;
}	