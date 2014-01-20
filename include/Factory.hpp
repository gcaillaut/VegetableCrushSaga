#ifndef INCLUDED_FACTORY_HPP
#define INCLUDED_FACTORY_HPP

#include <functional>
#include <map>
#include <memory>
#include <string>

template <typename T, typename Key=std::string>
class Factory
{
public:
  Factory ()
  {}

  ~Factory ()
  {}
  
  void registerObject (const Key key, std::function<T*()> func)
  {
    if (registered_objects.find(key) == registered_objects.end())
      registered_objects[key] = func;
  }

  std::unique_ptr<T> createObject (const Key key) const
  {
    auto it(registered_objects.find(key));
    return it == registered_objects.end() ? std::unique_ptr<T>(nullptr) : std::unique_ptr<T>(it->second());
  }


private:
    std::map<Key, std::function<T*()> > registered_objects;
};

#endif /* INCLUDED_FACTORY_HPP */
