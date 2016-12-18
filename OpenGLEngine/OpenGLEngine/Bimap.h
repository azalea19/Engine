#ifndef Bimap_h__
#define Bimap_h__

#include <unordered_map>

template<typename Key, typename Value>
class Bimap
{
public:

  Key& GetKey(const Value& value);
  Value& GetValue(const Key& key);

  Key const& GetKey(const Value& value) const;
  Value const& GetValue(const Key& key) const;

  bool HasKey(const Key& key) const;
  bool HasValue(const Value& value) const;

  void Add(const Key& key, const Value& value);

  int Count() const;

private:
  std::unordered_map<Key, Value> m_ValueLookup;
  std::unordered_map<Value, Key> m_KeyLookup;
};



#endif // Bimap_h__
