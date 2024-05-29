#include "mainwindow.hpp"
#include <boost/thread.hpp>

#include <QApplication>
#include <iostream>

void FreeFunction()
{
    std::cout << "hello from free function" << std::endl;
}

struct SomeClass
{
    void MemberFunction() { std::cout << "hello from member function" << std::endl; }

    static void StaticFunction() { std::cout << "hello from static member function" << std::endl; }
};

int main(int argc, char *argv[])
{
    SomeClass someClass;

    // this free function will be used internally as is
    boost::thread t1(&FreeFunction);
    t1.join();

    // this static member function will be used internally as is
    boost::thread t2(&SomeClass::StaticFunction);
    t2.join();

    // boost::bind will be called on this member function internally
    boost::thread t3(&SomeClass::MemberFunction, someClass);
    t3.join();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
