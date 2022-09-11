#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
using namespace std;
class student
{
    int addm_no;
    char name[20];
    char gender;
    int enroll_no, sem, year;
    float SGPA, CGPA;

public:
    void getdata();
    void showdata();
    int getAddm_no() { return addm_no; }
} s;
void student::getdata()
{
    cout << "enter student required information" << endl;
    cout << "student addmission no.";
    cin >> addm_no;
    cout << "student full name :";
    cin.getline(name, 20);
    cout << "student gender:";
    cin >> gender;
    cout << "student studying year:";
    cin >> year;
    cout << "student semester:";
    cin >> sem;
    cout << "student enrollment no.";
    cin >> enroll_no;
    cout << "student semester performance:";
    cin >> SGPA;
    cout << "student overall performance:";
    cin >> CGPA;
}
void student::showdata()
{
    cout << " student details " << endl;
    cout << " addmission no.:" << addm_no << endl;
    cout << " student full name: " << name << endl;
    cout << "  student gender " << gender << endl;
    cout << "student studying year:" << year << endl;
    cout << " student semester:" << sem << endl;
    cout << " student enrollment no.:" << enroll_no << endl;
    cout << " student semester performance:" << SGPA << endl;
    cout << " student overall performance:" << CGPA << endl;
}

void addData()
{
    ofstream fout;
    fout.open("Students.dat", ios::binary | ios::out | ios::app);
    s.getdata();
    fout.write((char *)&s, sizeof(s));
    fout.close();
    cout << "\n\nData Successfully Saved to File....\n";
}

void displayData()
{
    ifstream fin;
    fin.open("Students.dat", ios::in | ios::binary);
    while (fin.read((char *)&s, sizeof(s)))
    {
        s.showdata();
    }
    fin.close();
    cout << "\n\nData Reading from File Successfully Done....\n";
}

void searchData()
{
    int n, flag = 0;
    ifstream fin;
    fin.open("Students.dat", ios::in | ios::binary);
    cout << "Enter Admission Number you want to search : ";
    cin >> n;

    while (fin.read((char *)&s, sizeof(s)))
    {
        if (n == s.getAddm_no())
        {
            cout << "The Details of Admission No. " << n << " shown herewith:\n";
            s.showdata();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "The Admission No. " << n << " not found....\n\n";
    cout << "\n\nData Reading from File Successfully Done....\n";
}

void deleteData()
{
    int n, flag = 0;
    ifstream fin;
    ofstream fout, tout;

    fin.open("Students.dat", ios::in | ios::binary);
    fout.open("TempStud.dat", ios::out | ios::app | ios::binary);
    tout.open("TrashStud.dat", ios::out | ios::app | ios::binary);
    cout << "Enter Admission Number you want to move to Trash : ";
    cin >> n;

    while (fin.read((char *)&s, sizeof(s)))
    {
        if (n == s.getAddm_no())
        {
            cout << "The Following Admission No. " << n << " has been moved to Trash:\n";
            s.showdata();
            tout.write((char *)&s, sizeof(s));
            flag++;
        }
        else
        {
            fout.write((char *)&s, sizeof(s));
        }
    }
    fout.close();
    tout.close();
    fin.close();
    if (flag == 0)
        cout << "The Admission No. " << n << " not found....\n\n";
    remove("Students.dat");
    rename("tempStud.dat", "Students.dat");
}

void getTrash()
{
    ifstream fin;
    fin.open("TrashStud.dat", ios::in | ios::binary);
    while (fin.read((char *)&s, sizeof(s)))
    {
        s.showdata();
    }
    fin.close();
    cout << "\n\nData Reading from Trash File Successfully Done....\n";
}

void modifyData()
{
    int n, flag = 0, pos;
    fstream fio;

    fio.open("Students.dat", ios::in | ios::out | ios::binary);

    cout << "Enter Admission Number you want to Modify : ";
    cin >> n;

    while (fio.read((char *)&s, sizeof(s)))
    {
        pos = fio.tellg();
        if (n == s.getAddm_no())
        {
            cout << "The Following Admission No. " << n << " will be modified with new data:\n";
            s.showdata();
            cout << "\n\nNow Enter the New Details....\n";
            s.getdata();
            fio.seekg(pos - sizeof(s));
            fio.write((char *)&s, sizeof(s));
            flag++;
        }
    }
    fio.close();

    if (flag == 0)
        cout << "The Admission No. " << n << " not found....\n\n";
}

void project()
{
    int ch;
    do
    {
        system("cls");
        cout << "...............STUDENT MANAGEMENT SYSTEM..............\n";
        cout << "======================================================\n";
        cout << "0. Exit from Program\n";
        cout << "1. Write Data to File\n";
        cout << "2. Read Data From File\n";
        cout << "3. Search Data From File\n";
        cout << "4. Delete Data From File\n";
        cout << "5. Get Deleted Records from Trash file\n";
        cout << "6. Modify Data in File\n";
        cout << "Enter your choice  : ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case 1:
            addData();
            break;
        case 2:
            displayData();
            break;
        case 3:
            searchData();
            break;
        case 4:
            deleteData();
            break;
        case 5:
            getTrash();
            break;
        case 6:
            modifyData();
            break;
        }
        system("pause");
    } while (ch);
}

int main()
{
    project();
}
