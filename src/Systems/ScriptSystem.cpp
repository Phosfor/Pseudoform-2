#include "Systems/ScriptSystem.hpp"
template<> ScriptSystem* ISingleton<ScriptSystem>::mInstance = 0;

ScriptSystem::ScriptSystem() {}
ScriptSystem::~ScriptSystem()
{
    Py_Finalize();
}

void ScriptSystem::init()
{
    try {
        Py_Initialize();

        object main_module((
          handle<>(borrowed(PyImport_AddModule("__main__")))));

        main_namespace = main_module.attr("__dict__");

        handle<> ignored(( PyRun_String( "print \"Hello, World\"",
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
