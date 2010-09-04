#include "Systems/ScriptSystem.hpp"
//===================PYTHON-BINDS==================
void _LOG(const string &str) //can't use LOG because it's a macro
{
    LOG("Python: "+str);
}

BOOST_PYTHON_MODULE(Pseudoform)
{
    def("LOG", _LOG);
}

//===================ScriptSystem==================

template<> ScriptSystem* ISingleton<ScriptSystem>::mInstance = 0;

ScriptSystem::ScriptSystem() {}
ScriptSystem::~ScriptSystem()
{
    //Py_Finalize();
}

void ScriptSystem::init()
{
    try {
        PyImport_AppendInittab( "Pseudoform", &initPseudoform );

        Py_Initialize();

        object main_module((
          handle<>(borrowed(PyImport_AddModule("__main__")))));

        main_namespace = main_module.attr("__dict__");

        //object pseudoform_module( (handle<>(PyImport_ImportModule("Pseudoform"))) );
        //main_namespace["pseudoform"] = pseudoform_module;

        handle<> ignored(( PyRun_String( "from Pseudoform import LOG\n"
                                         "LOG(\"Hello, World\")",
                                         Py_file_input,
                                         main_namespace.ptr(),
                                         main_namespace.ptr() ) ));
    } catch( error_already_set ) {
        PyErr_Print();
    }

}

/*object ScriptSystem::loadModule(const string &path, const string &name)
{
    try {
        // If path is /Users/whatever/blah/foo.py

    }
    catch( error_already_set )
    {
        LOG("ERROR: Couldn't load Python-module");
        PyErr_Print();
        return (object().attr("__dict__")["FAIL"] = 1);
    }
}*/


void ScriptSystem::update(float elapsed) {}
std::string ScriptSystem::toString() { return "ScriptSystem"; }
