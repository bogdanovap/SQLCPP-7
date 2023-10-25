#include <pqxx/pqxx>
#include <iostream>
#include <windows.h>


//Создайте программу для управления клиентами на C++.
//
//Нужно хранить персональную информацию о клиентах:
//
//имя,
//фамилия,
//email,
//телефон.
//Сложность в том, что телефон у клиента может быть не один, а два, три и даже больше. А может и не быть — например, если он не захотел его оставлять.
//
//Вам нужно разработать структуру БД для хранения информации и написать класс на С++ для управления данными со следующими методами:
//


struct search_fields {
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;
};

class DBClient {
public:
    DBClient(const std::string& connectionString) : db_connection(connectionString) {
        if (!db_connection.is_open()) {
            throw std::runtime_error("Failed to connect to the database.");
        }
    }

    void executeQuery(const std::string& query) {
        pqxx::work work(db_connection);
        work.exec(query);
        work.commit();
    }

    void executeQuery(const std::string& query, const std::vector<std::string>& params_vec) {
        pqxx::work work(db_connection);
        pqxx::params params;
        for (const auto& param : params_vec) {
            params.append(param);
        }
        work.exec_params(query, params);
        work.commit();
    }

    // собираем запросы в одну транзакцию
    void executeQuery(const std::vector<std::string>& queries) {
        pqxx::work work(db_connection);
        for (const auto& query : queries) {
            work.exec(query);
        }
        work.commit();
    }
    // запросы в одной транзакции с параметрами
    void executeQuery(const std::vector<std::string>& queries, const std::vector<std::string>& params_vec) {
        pqxx::work work(db_connection);
        pqxx::params params;
        for (const auto& param : params_vec) {
            params.append(param);
        }
        for (const auto &query: queries)
            work.exec_params(query, params);

        work.commit();
    }

    //Метод, удаляющий структуру БД (таблицы).
    void dropTables() {
        std::vector<std::string> queries = {
            "DROP TABLE IF EXISTS phones;",
            "DROP TABLE IF EXISTS clients;"
        };
        executeQuery(queries);
    }

    //Метод, создающий структуру БД (таблицы).
    void createTables() {
        std::vector<std::string> queries = {
            "CREATE TABLE IF NOT EXISTS clients ("
                "id SERIAL PRIMARY KEY,"
                "first_name VARCHAR(50) NOT NULL,"
                "last_name VARCHAR(50) NOT NULL,"
                "email VARCHAR(50) NOT NULL"
            ");",
            "CREATE TABLE IF NOT EXISTS phones ("
                "id SERIAL PRIMARY KEY,"
                "client_id INTEGER REFERENCES clients(id),"
                "phone VARCHAR(50) NOT NULL"
            ");"
        };
        executeQuery(queries);
    }

    //Метод, позволяющий добавить нового клиента.
    void addClient(const std::string& firstName, const std::string& lastName, const std::string& email) {
        std::vector<std::string> params = {firstName, lastName, email};
        executeQuery("INSERT INTO clients (first_name, last_name, email) VALUES ($1, $2, $3);", params);
    }

    //Метод, позволяющий найти клиента по его данным — имени, фамилии, email или телефону.
    void findClient(const search_fields& fields) {
        pqxx::work work(db_connection);
        pqxx::params params;
        params.append(fields.firstName);
        params.append(fields.lastName);
        params.append(fields.email);
        params.append(fields.phone);
        auto res = work.exec_params(""
                                    "SELECT * "
                                    "FROM clients "
                                    "WHERE first_name=$1 OR last_name=$2 OR email=$3 "
                                    "or id in (select client_id from phones where phone=$4);", params);
        if (res.empty()) {
            std::cout << "No clients found" << std::endl;
            return;
        }
        for (auto row: res) {
            std::cout << row[0].as<int>() << ": " << row[1].as<std::string>() << " " << row[2].as<std::string>() << ", " << row[3].as<std::string>() << std::endl;
        }
    }

    //Метод, позволяющий добавить телефон для существующего клиента.
    void addPhone(const int client_id, const std::string& phone) {
        std::vector<std::string> params = {std::to_string(client_id), phone};
        executeQuery("INSERT INTO phones (client_id, phone) VALUES ($1, $2);", params);
    }

    //Метод, позволяющий изменить данные о клиенте.
    void updateClient(const int client_id, const std::string& firstName, const std::string& lastName, const std::string& email) {
        std::vector<std::string> params = {firstName, lastName, email, std::to_string(client_id)};
        executeQuery("UPDATE clients SET first_name=$1, last_name=$2, email=$3 WHERE id=$4;", params);
    }

    //Метод, позволяющий удалить телефон у существующего клиента.
    void deletePhone(const int client_id, const std::string& phone) {
        std::vector<std::string> params = {std::to_string(client_id), phone};
        executeQuery("DELETE FROM phones WHERE client_id=$1 AND phone=$2;", params);
    }

    //Метод, позволяющий удалить существующего клиента.
    void deleteClient(const int client_id) {
        std::vector<std::string> queries = {
            "DELETE FROM phones WHERE client_id=$1;",
            "DELETE FROM clients WHERE id=$1;"
        };
        std::vector<std::string> params = {std::to_string(client_id)};

        executeQuery(queries, params);
    }

    ~DBClient() {
        db_connection.close();
    }

private:
    pqxx::connection db_connection;
};


int main() {
    auto db = DBClient("host=192.168.11.126 "
                                       "port=5432 "
                                       "dbname=contacts "
                                       "user=postgres "
                                       "password=postgres");
    //удаляем таблицы
    db.dropTables();
    //создаем таблицы
    db.createTables();
    // добавляем клиента
    db.addClient("Aleks", "Bogdanov", "ab@email.com");
    // провреяем что клиент найден
    db.findClient({.lastName="Bogdanov"});
    // обновляем данные клиента
    db.updateClient(1, "Aleksandr", "Bogdanov", "ab@gmail.com");
    // проверяет что данные поменялись
    db.findClient({.lastName="Bogdanov"});
    // добавляем телефоны
    db.addPhone(1, "+7(999)999-99-99");
    db.addPhone(1, "+7(999)999-99-98");
    // проверяем что телефоны добавились и мы можем найти клиента по телефону
    db.findClient({.phone="+7(999)999-99-98"});
    // удаляем номер телефона
    db.deletePhone(1, "+7(999)999-99-98");
    // проверяем что клиент с таким номером не найден
    db.findClient({.phone="+7(999)999-99-98"});
    // удаляем клиента
    db.deleteClient(1);
    // провреяем что клиента нет
    db.findClient({.lastName="Bogdanov"});



    return 0;
}
