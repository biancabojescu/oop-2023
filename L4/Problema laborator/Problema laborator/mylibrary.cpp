#define _CRT_SECURE_NO_WARNINGS
#include "MyLibrary.h"
#include <stdarg.h>

MyLibrary::MyLibrary(std::ostream& output_stream) : output_stream(output_stream) {
    books_count = 0;
    books       = nullptr;
}

MyLibrary::MyLibrary(std::ostream& output_stream, unsigned books_count, int* books) : output_stream(output_stream) {
    this->books_count = books_count;
    this->books       = new int[books_count];
    for (int i = 0; i < books_count; ++i) {
        this->books[i] = books[i];
    }
}

MyLibrary::MyLibrary(std::ostream& output_stream, unsigned books_count, int min, int max)
    : output_stream(output_stream) {
    this->books_count = books_count;
    this->books       = new int[books_count];
    srand(time(NULL));
    for (int i = 0; i < books_count; ++i) {
        this->books[i] = rand() % max + min;
    }
}

MyLibrary::MyLibrary(std::ostream& output_stream, const char* books_values) : output_stream(output_stream) {
    int nr    = 1;
    int index = 0;
    for (int i = 0; i < strlen(books_values); ++i) {
        if (books_values[i] == ';') {
            ++nr;
        }
    }
    books_count = nr;
    books       = new int(nr);
    char* sir   = new char[strlen(books_values) + 1];
    strcpy(sir, books_values);
    char* p = strtok(sir, ";");
    while (p != nullptr) {
        int aux      = atoi(p);
        books[index] = aux;
        index++;
        p = strtok(nullptr, ";");
    }
    delete[] sir;
}

MyLibrary::MyLibrary(std::ostream& output_stream, unsigned books_count, ...) : output_stream(output_stream) {
    va_list args;
    va_start(args, books_count);
    books             = new int[books_count];
    this->books_count = books_count;
    for (int index = 0; index < books_count; ++index) {
        this->books[index] = va_arg(args, int);
    }
    va_end(args);
}

MyLibrary::~MyLibrary() {
    delete[] books;
}

void MyLibrary::print_books() {
    if (books_count > 0) {
        output_stream << books_count << "\n";
        for (int i = 0; i < books_count; ++i) {
            output_stream << books[i] << ' ';
        }
    } 
    else
        output_stream << "-1";
    output_stream << "\n";
}

void MyLibrary::update_book_id_by_index(unsigned book_index, int book_id) {
    if (book_index < books_count) 
        books[book_index] = book_id;
}

int MyLibrary::get_books_count() const {
    if (books_count > 0) {
        return books_count;
    } 
    else 
        return -1;
}

int MyLibrary::get_book_id_by_index(int index) const {
    if (index < books_count) {
        int x = books[index];
        return x;
    } 
    else 
        return -1;
}
