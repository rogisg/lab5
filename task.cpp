#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Student {
    string Name;
    string GroupId;
    vector<unsigned> Ratings;
    vector<string> Subjects;
};

struct Group {
    string Id;
    vector<Student> Students;
};

// Сортировка студентов по имени
void SortByName(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.Name < b.Name;
    });
}

// Сортировка студентов по средней оценке
void SortByRating(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        double a_avg = accumulate(a.Ratings.begin(), a.Ratings.end(), 0.0) / a.Ratings.size();
        double b_avg = accumulate(b.Ratings.begin(), b.Ratings.end(), 0.0) / b.Ratings.size();
        return a_avg > b_avg;
    });
}

// Количество студентов с хотя бы одной неудовлетворительной оценкой (2)
size_t CountTwoness(const vector<Student>& students) {
    size_t count = 0;
    for (const auto& student : students) {
        for (unsigned rating : student.Ratings) {
            if (rating == 2) {
                count++;
                break;
            }
        }
    }
    return count;
}

// Количество студентов, сдавших все экзамены на 5
size_t CountExcellent(const vector<Student>& students) {
    size_t count = 0;
    for (const auto& student : students) {
        bool all_excellent = true;
        for (unsigned rating : student.Ratings) {
            if (rating != 5) {
                all_excellent = false;
                break;
            }
        }
        if (all_excellent) count++;
    }
    return count;
}

// Студенты, имеющие 5 по предмету "Math"
vector<Student> VectorMathExcellent(const vector<Student>& students) {
    vector<Student> result;
    for (const auto& student : students) {
        for (size_t i = 0; i < student.Subjects.size(); i++) {
            if (student.Subjects[i] == "Math" && student.Ratings[i] == 5) {
                result.push_back(student);
                break;
            }
        }
    }
    return result;
}

// Уникальные названия групп
vector<string> GroupsId(const vector<Student>& students) {
    vector<string> groups;
    for (const auto& student : students) {
        if (find(groups.begin(), groups.end(), student.GroupId) == groups.end()) {
            groups.push_back(student.GroupId);
        }
    }
    return groups;
}

// Список групп с их студентами
vector<Group> Groups(const vector<Student>& students) {
    vector<Group> result;
    vector<string> groupIds = GroupsId(students);
    
    for (const auto& groupId : groupIds) {
        Group group;
        group.Id = groupId;
        
        for (const auto& student : students) {
            if (student.GroupId == groupId) {
                group.Students.push_back(student);
            }
        }
        
        result.push_back(group);
    }
    
    return result;
}

int main() {
    // Пример использования
    vector<Student> students = {
        {"Ivan", "101", {5, 4, 5}, {"Math", "Physics", "Chemistry"}},
        {"Anna", "102", {5, 5, 5}, {"Math", "Biology", "History"}},
        {"Petr", "101", {3, 2, 4}, {"Physics", "Chemistry", "Math"}},
        {"Maria", "102", {5, 4, 3}, {"Math", "Literature", "Art"}}
    };
    
    // Тестирование функций
    SortByName(students);
    SortByRating(students);
    
    cout << "Students with at least one 2: " << CountTwoness(students) << endl;
    cout << "Excellent students: " << CountExcellent(students) << endl;
    
    vector<Student> mathExcellent = VectorMathExcellent(students);
    cout << "Students with 5 in Math: " << mathExcellent.size() << endl;
    
    vector<string> groups = GroupsId(students);
    cout << "Unique groups: ";
    for (const auto& group : groups) cout << group << " ";
    cout << endl;
    
    vector<Group> groupedStudents = Groups(students);
    cout << "Groups count: " << groupedStudents.size() << endl;
    
    return 0;
}
