#ifndef INCLUDED_RESOURCEMANAGER_HPP
#define INCLUDED_RESOURCEMANAGER_HPP

#include <map>
#include <string>

/**
 * \class ResourceManager
 * \brief Manage ressources of type T.
 * Resources are strored into std::shared_ptr.
 */
template <typename T, typename Key>
class ResourceManager
{
public:
  ResourceManager ()
  {}

  ~ResourceManager ()
  {}

  template <typename ...Args>
  void createResource (const Key & key, Args... args)
  {
	resources[key] = std::make_shared<T>(args...);
  }

  std::shared_ptr<T> getResource (const Key & key) const
  {
	auto it(resources.find(key));
	return it == resources.end() ? std::shared_ptr<T>(nullptr) : it->second;
  }

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
