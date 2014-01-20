#ifndef INCLUDED_RESSOURCESMANAGER_HPP
#define INCLUDED_RESSOURCESMANAGER_HPP

#include <map>
#include <string>

template <typename T, typename Key, typename ...Args>
class RessourcesManager
{
public:
  RessourcesManager ()
  {}

  ~RessourcesManager ()
  {}

  void createRessource (const Key & key, Args... args)
  {
    ressources[key] = std::make_shared<T>(args...);
  }

  std::shared_ptr<T> getRessource (const Key & key) const
  {
    auto it(ressources.find(key));
    return it == ressources.end() ? std::shared_ptr<T>(nullptr) : it->second;
  }

  void eraseRessource (const Key & key)
  {
    auto it(ressources.find(key));
    if (it != ressources.end())
      {
        ressources.erase(it);
      }
  }
  
private:
  std::map<Key, std::shared_ptr<T>> ressources;
};

#endif /* INCLUDED_RESSOURCESMANAGER_HPP */