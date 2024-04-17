mkdir out

g++ -std=c++20 -c -Wall -Werror -I .\inl\ -I .\inc\ .\src\base_container.cpp -o .\out\base_container.o
g++ -std=c++20 -c -Wall -Werror -I .\inl\ -I .\inc\ .\src\base_exception.cpp -o .\out\base_exception.o
g++ -std=c++20 -c -Wall -Werror -I .\inl\ -I .\inc\ .\src\base_iterator.cpp -o .\out\base_iterator.o
g++ -std=c++20 -c -Wall -Werror -I .\inl\ -I .\inc\ .\main.cpp -o .\out\main.o

g++ -std=c++20 -lgtest -lgtest_main -lpthread -Wall -Werror -I .\inl\ -I .\inc\ .\out\main.o .\out\base_container.o .\out\base_exception.o .\out\base_iterator.o -o .\out\app.exe