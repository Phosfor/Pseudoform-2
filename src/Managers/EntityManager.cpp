#include "Managers/EntityManager.hpp"

Object *EntityManager::MakeObject(const string& entityName)
{
    return this->MakeEntity<Object>(entityName);
}

Object *EntityManager::GetObject(const string& entityName)
{
    return this->GetEntity<Object>(entityName);
}

Light *EntityManager::MakeLight(const string& entityName)
{
    return this->MakeEntity<Light>(entityName);
}

Light *EntityManager::GetLight(const string& entityName)
{
    return this->GetEntity<Light>(entityName);
}

bool EntityManager::DeleteEntity(const string& entityName)
{
    if (mEntityList.count(entityName) == 0)
    {
        LOG(FORMAT("Can`t delete entity '%1%', because it doesn`t exsist!", entityName));
        return false;
    }
    mEntityList.erase(entityName);
    return true;
}
