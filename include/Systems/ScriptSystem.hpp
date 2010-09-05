#ifndef _SCRIPT_SYSTEM_HPP_
#define _SCRIPT_SYSTEM_HPP_

#include "System.hpp"
#include "Engine.hpp"
#include <boost/python.hpp>

#define scriptSystem (ScriptSystem::get_mutable_instance())
#define scriptSystemConst (ScriptSystem::get_const_instance())

using namespace boost::python;

class ScriptSystem : public ISystem, public ISingleton<ScriptSystem>
{
    private:
        object main_namespace;
    public:
        ScriptSystem();
        ~ScriptSystem();

        object loadModule(const string &name);

        void init();
        void update(float elapsed);
        std::string toString();
};

#endif
