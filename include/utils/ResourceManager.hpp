#ifndef INCLUDED_RESOURCEMANAGER_HPP
#define INCLUDED_RESOURCEMANAGER_HPP

#include <map>
#include <string>

///
/// \brief Gère les ressources de type T
/// Les ressources sont stockés dans des std::unique_ptr
///
template <typename T, typename Key>
class ResourceManager
{
public:
  ResourceManager () {}
  ~ResourceManager () {}

  ///
  /// \brief Crée la ressource
  /// \param key  Identifiant
  /// \param args Arguments pour le constructeur de l'objet
  ///
  template <typename ...Args>
  void createResource (const Key & key, Args... args)
  {
	resources[key] = std::make_shared<T>(args...);
  }

  ///
  /// \brief Retourne la ressource identifiée par 'key'
  /// \param key  Identifiant
  /// \return La ressource correspondante
  ///
  std::shared_ptr<T> getResource (const Key & key) const
  {
	auto it(resources.find(key));
	return it == resources.end() ? std::shared_ptr<T>(nullptr) : it->second;
  }

  ///
  /// \brief Supprime la ressource identifiée par 'key'
  /// \param key  Identifiant
  ///
  void eraseResource (const Key & key)
  {
	auto it(resources.find(key));
	if (it != resources.end())
      {
		resources.erase(it);
      }
  }

private:
  std::map<Key, std::shared_ptr<T>> resources;
};

#endif /* INCLUDED_RESOURCEMANAGER_HPP */
