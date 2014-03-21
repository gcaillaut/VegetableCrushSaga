#ifndef INCLUDED_FACTORY_HPP
#define INCLUDED_FACTORY_HPP

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

///
/// \brief Pattern Factory
///
template <typename T, typename Key=std::string>
class Factory
{
public:
  Factory () {}
  ~Factory () {}
  
  ///
  /// \brief Enregistre un objet
  /// \param key  Identifiant
  /// \param func Fonction de création
  ///
  void registerObject (const Key & key, std::function<T*()> func)
  {
    if (registered_objects.find(key) == registered_objects.end())
      {
        registered_objects[key] = func;
      }
  }

  ///
  /// \brief Crée un objet
  /// \param key  Identifiant
  /// \return Objet de type T
  ///
  std::unique_ptr<T> createObject (const Key & key) const
  {
    auto it(registered_objects.find(key));
    std::unique_ptr<T> ptr(it == registered_objects.end() ? std::unique_ptr<T>(nullptr) : std::unique_ptr<T>(it->second()));

    return ptr;
  }

  ///
  /// \brief Retourne les identifiants existants
  /// \return Les identifiants existants
  ///
  std::vector<Key> getAvailableKeys () const
  {
    std::vector<Key> v;
    v.reserve(registered_objects.size());

    std::for_each(registered_objects.cbegin(), 
                  registered_objects.cend(), 
                  [&v](std::pair<Key, std::function<T*()> > e) {
                    v.push_back(e.first);
                  });

    return v;
  }

private:
  std::unordered_map<Key, std::function<T*()>> registered_objects;
};

#endif /* INCLUDED_FACTORY_HPP */
