#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<numeric>
#include<vector>

using namespace std;

struct Course
{
    string name;
    int credits;
    float grade;
};

vector<Course> courses;

void displayCourses()
{
    cout << "COURSES TAKEN: " << endl;
    for (int i = 0; i < courses.size(); i++)
        cout << courses[i].name << " - " << courses[i].credits << " credits, grade " << courses[i].grade << endl;
    cout << endl;
}

void addCourse()
{
    Course new_courses;
    cout << "Enter course name: "; getline(cin, new_courses.name);
    cout << "Enter credits: "; cin >> new_courses.credits;
    cout << "Enter grade: "; cin >> new_courses.grade;
    courses.push_back(new_courses);
    cout << endl << new_courses.name << " has been added." << endl << endl; 
}

void calculateSemestrGpa()
{
    vector<float> grade_points;
    vector<int> credit_hours;
    for (int i = 0; i < courses.size(); i++)
    {
        grade_points.push_back(courses[i].grade * courses[i].credits);
        credit_hours.push_back(courses[i].credits);
    }
    float total_grade_points = accumulate(grade_points.begin(), grade_points.end(), 0);
    int total_credit_hours = accumulate(credit_hours.begin(), credit_hours.end(), 0);
    float semester_gpa = total_grade_points / total_credit_hours;
    cout << "SEMESTER GPA: " << semester_gpa << endl << endl;
}

void calculateCgpa()
{
    float total_grade_points = 0; int total_credits = 0;    
    for (int i = 0; i < courses.size(); i++)
    {
        total_grade_points += courses[i].grade * courses[i].credits;
        total_credits += courses[i].credits; 
    }
    float cgpa = total_grade_points / total_credits;
}

void saveData()
{
    ofstream file;
    file.open("data.txt");
    for (int i = 0; i < courses.size(); i++)
        file << courses[i].name << "," << courses[i].credits << "," << courses[i].grade << endl;    
    file.close();
    cout << "Data saved to file." << endl << endl;
}

void loadData()
{
    ifstream file;
    file.open("data.txt");
    string line;
    while (getline(file, line))
    {
        Course c; 
        int comma_pos =  line.find(",");
        c.name = line.substr(0, comma_pos);
        line.erase(0, comma_pos + 1);
        comma_pos = line.find(",");
        c.credits = stoi(line.substr(0, comma_pos));
        line.erase(0, comma_pos + 1);
        c.grade = stof(line);
        courses.push_back(c);
    }
    file.close();
    cout << "Data load from file." << endl << endl;
}

int main()
{
    int choose = 0;
    while (choose != 7)
    {
        cout << "CGPA Calculator\n1. Display courses\n2. Add course\n3. Calculate semester GPA\n4. Calculate CGPA\n5. Save data to file\n6. Load data from file \n7. Quit\n";
        cout << "Enter your choice: "; cin >> choose; cin.ignore();
        switch (choose)
        {
        case 1:
            displayCourses();
            break;
        case 2:
            addCourse();
            break;
        case 3:
            calculateSemestrGpa();
            break;
        case 4:
            calculateCgpa();
            break;
        case 5:
            saveData();
            break;
        case 6:
            loadData();
            break;
        case 7:
            cout << "Goodbye" << endl; break;
        default:
            cout << "Invalid code" << endl; 
            break;
        }
    }
    return 0;
}