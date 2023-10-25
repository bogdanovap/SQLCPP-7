#include <pqxx/pqxx>
#include <iostream>
#include <windows.h>

int main () {
    std::cout << "connecting to database" << std::endl;
    setlocale(LC_ALL, "ru_RU.UTF-8");
    try {
        pqxx::connection c(
                "host=192.168.11.126 "
                "port=5432 "
                "dbname=postgres "
                "user=postgres "
                "password=postgres");

        pqxx::work tx{c};

        for (auto [id, title, author]: tx.query<int, std::string, std::string>(
                "SELECT id, title, author FROM books;")) {
            std::cout << id << ": " << title << " by " << author << std::endl;
        }

        auto title = tx.query_value<std::string>("SELECT title FROM books where id=1;");
        std::cout << title << std::endl;

        tx.exec_params("INSERT INTO books (title, author) VALUES ($1, $2);", "The C++ Programming Language",
                       "Bjarne Stroustrup");
        tx.commit();

        tx.exec_params("Delete from books where title=$1;", "The C++ Programming Language");
        tx.commit();
    }
    catch (const std::exception &e) {
        std::cout << "Error connecting to database" << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}