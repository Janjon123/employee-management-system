#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

struct Date
{
    int day;
    int month;
    int year;
};

struct Employee
{
    int id;
    char name[50];
    float salary;
    char address[100];
    char mobileNumber[20];
    char email[100];
    Date DOB; // date of birth
    Date DOE; // date of enrollment
};

int flag = 0;
Employee employees[200];
int numberOfEmployees = 0;

Date *createDate(int day, int month, int year)
{
    Date *dt = new Date;
    dt->day = day;
    dt->month = month;
    dt->year = year;
    return dt;
}

Employee *createEmployee(int id, char *name, char *address, char *mobileNumber, char *email, float salary, int dBirth, int mBirth, int yBirth, int dEnroll, int mEnroll, int yEnroll)
{
    Employee *emp = new Employee;
    emp->id = id;
    strcpy(emp->name, name);
    strcpy(emp->address, address);
    strcpy(emp->mobileNumber, mobileNumber);
    strcpy(emp->email, email);
    emp->salary = salary;
    emp->DOB = *createDate(dBirth, mBirth, yBirth);
    emp->DOE = *createDate(dEnroll, mEnroll, yEnroll);
    return emp;
}

void printEmployeeInfo(Employee emp)
{
    cout << "-------------------------------------------------------" << endl;
    cout << "Employee ID: " << emp.id << endl;
    cout << "Name: " << emp.name << endl;
    cout << "Salary: " << emp.salary << endl;
    cout << "Address: " << emp.address << endl;
    cout << "Mobile Number: " << emp.mobileNumber << endl;
    cout << "Email: " << emp.email << endl;
    cout << "Date of Birth: " << emp.DOB.day << "/" << emp.DOB.month << "/" << emp.DOB.year << endl;
    cout << "Date of Enrollment: " << emp.DOE.day << "/" << emp.DOE.month << "/" << emp.DOE.year << endl;
    cout << "-------------------------------------------------------" << endl;
}

Employee *deserialize(char *str)
{
    int i = 0, id = 0;
    char *name = NULL, *address = NULL, *mobileNumber = NULL, *email = NULL;
    float salary = 0;
    int dBirth = 0, mBirth = 0, yBirth = 0, dEnroll = 0, mEnroll = 0, yEnroll = 0;
    char *token = strtok(str, ",-");
    while (token)
    {
        if (token[strlen(token) - 1] == '\n')
            token[strlen(token) - 1] = '\0';
        if (i == 0)
        {
            id = atoi(token);
        }
        else if (i == 1)
        {
            name = token;
        }
        else if (i == 2)
        {
            salary = atof(token);
        }
        else if (i == 3)
        {
            dBirth = atoi(token);
        }
        else if (i == 4)
        {
            mBirth = atoi(token);
        }
        else if (i == 5)
        {
            yBirth = atoi(token);
        }
        else if (i == 6)
        {
            address = token;
        }
        else if (i == 7)
        {
            mobileNumber = token;
        }
        else if (i == 8)
        {
            dEnroll = atoi(token);
        }
        else if (i == 9)
        {
            mEnroll = atoi(token);
        }
        else if (i == 10)
        {
            yEnroll = atoi(token);
        }
        else if (i == 11)
        {
            email = token;
        }
        i++;
        token = strtok(NULL, ",-");
    }
    Employee *emp = createEmployee(id, name, address, mobileNumber, email, salary, dBirth, mBirth, yBirth, dEnroll, mEnroll, yEnroll);
    return emp;
}

void load()
{
    ifstream file("Company.txt");
    if (!file.is_open())
    {
        cout << "The file is not opened. The program will now exit." << endl;
        exit(1);
    }
    char line[200];
    while (file.getline(line, 200))
    {
        Employee *emp = deserialize(line);
        employees[numberOfEmployees] = *emp;
        numberOfEmployees++;
        delete emp;
    }
    file.close();
}

int isValidId(int id)
{
    if (id == 0)
        return 0;
    for (int i = 0; i < numberOfEmployees; i++)
    {
        if (employees[i].id == id)
            return 0;
    }
    return 1;
}

int isValidEmail(char *email)
{
    int atFound = 0, endFound = 0;
    int len = strlen(email);

    for (int i = 0; i < len; i++)
    {
        if (email[i] == '@')
        {
            atFound = 1;
        }
        else if (atFound && i >= len - 4 && strcmp(&email[i], ".com") == 0)
        {
            endFound = 1;
            break;
        }
    }
    return atFound && endFound;
}

int isValidDigits(char *s)
{
    int i = 0;
    if (s[0] == '0')
        return 0;
    while (s[i])
    {
        char c = s[i];
        if (c < '0' || c > '9')
            return 0;
        i++;
    }
    return 1;
}

int isValidNumber(char *mobileNumber)
{
    int i;
    for (i = 0; i < strlen(mobileNumber); i++)
    {
        if (!(mobileNumber[i] >= '0' && mobileNumber[i] <= '9'))
            return 0;
    }
    if (i != 11)
        return 0;
    return 1;
}

int isLeapYear(int year)
{
    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
        return 1;
    else
        return 0;
}

int isValidDate(Date *o)
{
    if (o->month < 1 || o->month > 12)
        return 0;
    if (o->day < 1 || o->day > 31)
        return 0;
    if (o->month == 2)
    {
        if (isLeapYear((int)o->year))
        {
            if (o->day > 29)
                return 0;
        }
        else if (o->day > 28)
            return 0;
    }
    if ((o->month == 4 || o->month == 6 || o->month == 9 || o->month == 11) && o->day == 31)
        return 0;
    return 1;
}

void add()
{
    flag = 1;
    char salary[50], id[5], name[100], address[100], mobileNumber[20], email[50], dBirth[10], mBirth[20], yBirth[20];
    int dayEmp, monthEmp, yearEmp;
    Date *temp;

    cout << "Please enter the employee id : ";
    cin >> id;
    while (!isValidId(atoi(id)))
    {
        cout << "Invalid ID !" << endl;
        cout << "Please enter a valid ID : ";
        cin >> id;
    }
    cout << "Please enter the employee name : ";
    cin.ignore();
    cin.getline(name, 100);
    cout << "Please enter the employee address : ";
    cin.getline(address, 100);
    cout << "Please enter the employee mobile number : ";
    cin.getline(mobileNumber, 20);
    while (!isValidNumber(mobileNumber))
    {
        cout << "Invalid Mobile Number !" << endl;
        cout << "Please enter a valid Mobile Number : ";
        cin.getline(mobileNumber, 20);
    }
    cout << "Please enter email address : ";
    cin.getline(email, 50);
    while (!isValidEmail(email))
    {
        cout << "Invalid Email !" << endl;
        cout << "Please enter a valid Email : ";
        cin.getline(email, 50);
    }
    cout << "Enter birth date" << endl;
    cout << "Enter Day : ";
    cin >> dBirth;
    cout << "Enter Month : ";
    cin >> mBirth;
    cout << "Enter Year : ";
    cin >> yBirth;
    temp = createDate(atoi(dBirth), atoi(mBirth), atoi(yBirth));
    while (!(isValidDate(temp) && isValidDigits(dBirth) && isValidDigits(mBirth) && isValidDigits(yBirth)))
    {
        cout << "Invalid date of birth" << endl;
        cout << "Enter Day : ";
        cin >> dBirth;
        cout << "Enter Month : ";
        cin >> mBirth;
        cout << "Enter Year : ";
        cin >> yBirth;
        temp = createDate(atoi(dBirth), atoi(mBirth), atoi(yBirth));
    }
    delete temp;
    cout << "Enter salary : ";
    cin >> salary;
    while (atof(salary) == 0)
    {
        cout << "Invalid Salary" << endl;
        cout << "Enter salary : ";
        cin >> salary;
    }

    time_t current_time;
    time(&current_time);
    struct tm *local_time = localtime(&current_time);
    dayEmp = local_time->tm_mday;
    monthEmp = local_time->tm_mon + 1;
    yearEmp = local_time->tm_year + 1900;

    Employee *emp = createEmployee(atoi(id), name, address, mobileNumber, email, atof(salary), atoi(dBirth), atoi(mBirth), atoi(yBirth), dayEmp, monthEmp, yearEmp);
    employees[numberOfEmployees++] = *emp;
    delete emp;
}

void search()
{
    char name[100];
    int i, found = 0;
    cout << "Enter name you would like to search for : ";
    cin.ignore();
    cin.getline(name, 100);
    for (i = 0; i < numberOfEmployees; i++)
    {
        if (strstr(employees[i].name, name))
        {
            printEmployeeInfo(employees[i]);
            found = 1;
        }
    }
    if (!found)
        cout << "No matches found !" << endl;
}

void deleteEmployee()
{
    flag = 1;
    char id[10];
    int i, found = 0;
    cout << "Enter the ID of the employee you would like to delete : ";
    cin >> id;
    for (i = 0; i < numberOfEmployees; i++)
    {
        if (employees[i].id == atoi(id))
        {
            found = 1;
            for (int j = i; j < numberOfEmployees - 1; j++)
            {
                employees[j] = employees[j + 1];
            }
            numberOfEmployees--;
            cout << "Employee with ID : " << atoi(id) << " has been deleted" << endl;
            break;
        }
    }
    if (found == 0)
    {
        cout << "No ID matches this ID" << endl;
    }
}

void modify()
{
    flag = 1;
    char id[10], choice[10];
    int i, found = 0;
    while (!found)
    {
        cout << "Enter the ID of the employee you would like to modify : ";
        cin >> id;
        for (i = 0; i < numberOfEmployees; i++)
        {
            if (employees[i].id == atoi(id))
            {
                found = 1;
                break;
            }
        }
        if (!found)
            cout << "User not Found !" << endl;
    }

    cout << "what would you like to modify : " << endl;
    cout << "--------------------------------" << endl;
    cout << "1-Name" << endl;
    cout << "2-Salary" << endl;
    cout << "3-Mobile number" << endl;
    cout << "4-Address" << endl;
    cout << "5-Email Address" << endl;
    cout << "--------------------------------" << endl;
    cout << "Enter your choice : ";
    cin >> choice;

    if (strcmp(choice, "1") == 0)
    {
        char name[100];
        cout << "Enter the new name : ";
        cin >> name;
        strcpy(employees[i].name, name);
    }
    else if (strcmp(choice, "2") == 0)
    {
        char salary[100];
        cout << "Enter the new salary : ";
        cin >> salary;
        while (atof(salary) == 0)
        {
            cout << "Invalid Salary" << endl;
            cout << "Enter the new salary : ";
            cin >> salary;
        }
        employees[i].salary = atof(salary);
    }
    else if (strcmp(choice, "3") == 0)
    {
        char mobileNumber[100];
        cout << "Enter the new mobile number : ";
        cin >> mobileNumber;
        while (!isValidNumber(mobileNumber))
        {
            cout << "Invalid Mobile Number" << endl;
            cout << "Enter the new mobile number : ";
            cin >> mobileNumber;
        }
        strcpy(employees[i].mobileNumber, mobileNumber);
    }
    else if (strcmp(choice, "4") == 0)
    {
        char address[100];
        cout << "Enter the new address : ";
        cin >> address;
        strcpy(employees[i].address, address);
    }
    else if (strcmp(choice, "5") == 0)
    {
        char email[100];
        cout << "Enter the new email address : ";
        cin >> email;
        while (!isValidEmail(email))
        {
            cout << "Invalid Email Address!" << endl;
            cout << "Enter the new email address : ";
            cin >> email;
        }
        strcpy(employees[i].email, email);
    }
    else
    {
        cout << "Invalid Input!" << endl;
    }
}

void SortBySalary()
{
    flag = 1;
    int i, j;
    cout << "Sort employees by salary" << endl << endl;
    Employee temp[numberOfEmployees];
    for (i = 0; i < numberOfEmployees; i++)
    {
        for (j = 0; j < numberOfEmployees - 1 - i; j++)
        {
            if (employees[j].salary > employees[j + 1].salary)
            {
                temp[j] = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp[j];
            }
        }
    }
}

void sortByName()
{
    flag = 1;
    int i, j;
    cout << "Sort employees by last name" << endl;
    Employee temp[numberOfEmployees];
    for (i = 0; i < numberOfEmployees; i++)
    {
        for (j = 0; j < numberOfEmployees - 1 - i; j++)
        {
            if (strcasecmp(employees[j].name, employees[j + 1].name) > 0)
            {
                temp[j] = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp[j];
            }
        }
    }
}

void printAllEmployees()
{
    for (int i = 0; i < numberOfEmployees; i++)
    {
        cout << "Employee #" << i + 1 << ":" << endl;
        printEmployeeInfo(employees[i]);
        cout << endl;
    }
}

void SortByDOB()
{
    flag = 1;
    int i, j;
    cout << "Sort employees by date of birth" << endl << endl;
    Employee temp[numberOfEmployees];
    for (i = 0; i < numberOfEmployees; i++)
    {
        for (j = 0; j < numberOfEmployees - 1 - i; j++)
        {
            if (employees[j].DOB.year > employees[j + 1].DOB.year)
            {
                temp[j] = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp[j];
            }
            else if (employees[j].DOB.year == employees[j + 1].DOB.year && employees[j].DOB.month > employees[j + 1].DOB.month)
            {
                temp[j] = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp[j];
            }
            else if (employees[j].DOB.year == employees[j + 1].DOB.year && employees[j].DOB.month == employees[j + 1].DOB.month && employees[j].DOB.day > employees[j + 1].DOB.day)
            {
                temp[j] = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp[j];
            }
            else
                continue;
        }
    }
}

void print()
{
    char choice[10];
    cout << "Which type of Sort would you like to do : " << endl;
    cout << "------------------------------------------" << endl;
    cout << "1-Sort By Name" << endl;
    cout << "2-Sort By Salary" << endl;
    cout << "3-Sort By DOB" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Choice : ";
    cin >> choice;

    if (strcmp(choice, "1") == 0)
    {
        sortByName();
        printAllEmployees();
    }
    else if (strcmp(choice, "2") == 0)
    {
        SortBySalary();
        printAllEmployees();
    }
    else if (strcmp(choice, "3") == 0)
    {
        SortByDOB();
        printAllEmployees();
    }
    else
    {
        cout << "Invalid Input" << endl;
    }
}

void saveFile()
{
    flag = 0;
    ofstream f("Company.txt");
    if (!f.is_open())
    {
        cout << "ERROR CREATING FILE Company.txt" << endl;
        exit(0);
    }
    int i;
    char st[400];
    for (i = 0; i < numberOfEmployees; i++)
    {
        sprintf(st, "%d,%s,%.2f,%2d-%2d-%d,%s,%s,%2d-%2d-%d,%s", employees[i].id, employees[i].name, employees[i].salary, employees[i].DOB.day, employees[i].DOB.month, employees[i].DOB.year, employees[i].address, employees[i].mobileNumber, employees[i].DOE.day, employees[i].DOE.month, employees[i].DOE.year, employees[i].email);
        if (strlen(st) > 0 && st[strlen(st) - 1] == '\n')
            st[strlen(st) - 1] = '\0';
        f << st << endl;
    }
    f.close();
    cout << "File Company.txt is saved" << endl;
}

void quit()
{
    char choice[10];
    if (flag == 1)
    {
        cout << "Are you sure you want to quit without saving ?" << endl;
        cout << "1-Yes" << endl;
        cout << "2-No" << endl;
        cin >> choice;
        if (strcmp(choice, "1") == 0)
            exit(0);
        else if (strcmp(choice, "2") == 0)
            return;
        else
            cout << "Invalid Input" << endl;
    }
    exit(0);
}

int main()
{
    cout << "--------------------------Welcome to our company Management System--------------------------" << endl;
    load();
    while (1)
    {
        int valid = 0;
        char choice[10];
        cout << "-------------------------------------------" << endl;
        cout << "Choose the operation you would like to do:" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "1-Add" << endl;
        cout << "2-Delete" << endl;
        cout << "3-Modify" << endl;
        cout << "4-Search" << endl;
        cout << "5-Print" << endl;
        cout << "6-Save" << endl;
        cout << "7-Quit" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "The Option : ";
        cin >> choice;
        cout << "-------------------------------------------" << endl;

        while (!valid)
        {
            if (strcmp(choice, "1") == 0)
            {
                valid = 1;
                add();
            }
            else if (strcmp(choice, "2") == 0)
            {
                valid = 1;
                deleteEmployee();
            }
            else if (strcmp(choice, "3") == 0)
            {
                valid = 1;
                modify();
            }
            else if (strcmp(choice, "4") == 0)
            {
                valid = 1;
                search();
            }
            else if (strcmp(choice, "5") == 0)
            {
                valid = 1;
                print();
            }
            else if (strcmp(choice, "6") == 0)
            {
                valid = 1;
                saveFile();
            }
            else if (strcmp(choice, "7") == 0)
            {
                valid = 1;
                quit();
            }
            if (!valid)
            {
                cout << "Invalid Option !" << endl;
                cout << "The Option : ";
                cin >> choice;
            }
        }
    }
    return 0;
}
