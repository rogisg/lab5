#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;

class Book {
private:
    string author;
    string title;
    string publisher;
    int year;
    int pages;

public:
    // Конструкторы (как в ЛР4)
    Book() : author(""), title(""), publisher(""), year(0), pages(0) {}
    
    Book(const string& a, const string& t, const string& p, int y, int pg) 
        : author(a), title(t), publisher(p), year(y), pages(pg) {}
    
    // Геттеры
    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    string getPublisher() const { return publisher; }
    int getYear() const { return year; }
    int getPages() const { return pages; }
    
    // Перегрузка оператора вывода (как в ЛР4)
    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "Автор: " << book.author 
           << ", Название: " << book.title 
           << ", Издательство: " << book.publisher 
           << ", Год: " << book.year 
           << ", Страниц: " << book.pages;
        return os;
    }
    
    // Оператор сравнения для set (сортировка по ФИО автора)
    bool operator<(const Book& other) const {
        return author < other.author;
    }
    
    // Оператор равенства для unordered_set
    bool operator==(const Book& other) const {
        return author == other.author && 
               title == other.title && 
               publisher == other.publisher && 
               year == other.year && 
               pages == other.pages;
    }
};

// Хеш-функция для Book
namespace std {
    template<>
    struct hash<Book> {
        size_t operator()(const Book& book) const {
            return hash<string>()(book.getAuthor()) ^
                   hash<string>()(book.getTitle()) ^
                   hash<string>()(book.getPublisher()) ^
                   hash<int>()(book.getYear()) ^
                   hash<int>()(book.getPages());
        }
    };
}

int main() {
    // Чтение данных из файла (как в ЛР4)
    vector<Book> booksVector;
    ifstream input("input.txt");
    if (input.is_open()) {
        string author, title, publisher;
        int year, pages;
        
        while (getline(input, author) && 
               getline(input, title) && 
               getline(input, publisher) && 
               input >> year >> pages) {
            input.ignore(); // Пропустить символ новой строки
            booksVector.emplace_back(author, title, publisher, year, pages);
        }
        input.close();
    }

    // Создание и заполнение set (упорядоченное множество)
    set<Book> booksSet(booksVector.begin(), booksVector.end());
    
    // Создание и заполнение unordered_set (неупорядоченное множество)
    unordered_set<Book> booksUnorderedSet(booksVector.begin(), booksVector.end());
    
    // Вывод содержимого контейнеров
    ofstream output("output_lr5.txt");
    
    // Вывод set (отсортирован по автору)
    output << "Содержимое set (отсортировано по автору):\n";
    for (const auto& book : booksSet) {
        output << book << "\n";
    }
    
    // Вывод unordered_set
    output << "\nСодержимое unordered_set (произвольный порядок):\n";
    for (const auto& book : booksUnorderedSet) {
        output << book << "\n";
    }
    
    output.close();
    
    return 0;
}
