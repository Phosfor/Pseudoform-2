#ifndef _GUI_SYSTEM_H_
#define _GUI_SYSTEM_H_

#include "System.hpp"
#include "PseudoformAdditional.hpp"
#include "PseudoformCore.hpp"

class GuiSystem : public ISystem, public singleton<GuiSystem>
{
    private:
        // MyGui ....

    public:
        GuiSystem();
        ~GuiSystem();

        // Inherited from ISystem
        void init();
        void update();
        std::string toString();
};

#endif
