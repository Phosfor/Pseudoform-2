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
        PyImport_AppendInittab( (char *)"Pseudoform", &initPseudoform ); //I cast it to make the compiler happe -> no warnings

        Py_Initialize();
        LOG("Python-interpreter inizialized");

        object main_module((
          handle<>(borrowed(PyImport_AddModule("__main__")))));

        main_namespace = main_module.attr("__dict__");

        exec(  ("import sys\n"
                "sys.path.append(\""+
                CONFIG("script.path", string, "media/Scripts")+"\")").c_str(),
                main_namespace,
                main_namespace );
        LOG("Added script path to sys.path");


        //You can use this or the python-version ("import testIt")
        main_namespace["testIt"] = loadModule("testIt");

        exec(   "from Pseudoform import LOG\n"
                //"import testIt\n"
                "LOG(testIt.returnSTH())",
                main_namespace,
                main_namespace );
    } catch( error_already_set ) {
        LOG("A Python-error accured while initialising ScriptSystem");
        PyErr_Print();
    }

}

object ScriptSystem::loadModule(const string &name)
{
    try {
        return import(str::str(name));
    }
    catch( error_already_set )
    {
        LOG("ERROR: Couldn't load Python-module "+name);
        PyErr_Print();
        return object();
    }
}


void ScriptSystem::update(float elapsed) {}
std::string ScriptSystem::toString() { return "ScriptSystem"; }
