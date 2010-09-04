#include "Engine.hpp"
#include <boost/python.hpp>
#include <iostream>
using namespace boost::python;
using namespace std;
using namespace Engine;

string LOG_(const string &str)
{
    //LOG(str);
    return "THIS IS A TEST";
}

string getVersion()
{
    return "0.0.1";
}

BOOST_PYTHON_MODULE(Pyform)
{
    //def("LOG", LOG_);
    def("getVersion", getVersion);
}
