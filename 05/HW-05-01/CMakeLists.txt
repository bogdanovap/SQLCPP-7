# to make libpq run in clion env, had to use this workaround
# https://github.com/jtv/libpqxx/issues/711
# 1. comment #define #PQXX_HAVE_SLEEP_FOR
# 2. copy dlls from postgres/version/bin to debug dir (next to .exe)
cmake_minimum_required(VERSION 3.2)
project(HW_05_01)
add_executable(HW_05_01 main.cpp)

#set(PostgreSQL_ADDITIONAL_VERSIONS "14.1")
#set(PostgreSQL_ROOT "C:\\Program Files\\PostgreSQL\\14")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("F:\\Storage\\Documents_Aleks\\Study\\Netology\\CPP\\05_sqlcpp\\libpqxx-7.8.1" libpqxx-build)
#add_subdirectory("F:\\Storage\\Documents_Aleks\\Study\\Netology\\CPP\\05_sqlcpp\\libpqxx-7.7.5" libpqxx-build)


target_compile_features(HW_05_01 PRIVATE cxx_std_17)

target_link_libraries(HW_05_01 pqxx)
