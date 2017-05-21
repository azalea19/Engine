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

template<typename Key, typename Value>
void Bimap<Key, Value>::Add(const Key& key, const Value& value)
{
	m_ValueLookup.emplace(key, value);
	m_KeyLookup.emplace(value, key);
}

template<typename Key, typename Value>
bool Bimap<Key, Value>::HasValue(const Value& value) const
{
	return m_KeyLookup.find(value) != m_KeyLookup.end();
}

template<typename Key, typename Value>
bool Bimap<Key, Value>::HasKey(const Key& key) const
{
	return m_ValueLookup.find(key) != m_ValueLookup.end();
}

template<typename Key, typename Value>
Value const& Bimap<Key, Value>::GetValue(const Key& key) const
{
	return m_ValueLookup.at(key);
}

template<typename Key, typename Value>
Key const& Bimap<Key, Value>::GetKey(const Value& value) const
{
	return m_KeyLookup.at(value);
}

template<typename Key, typename Value>
Value& Bimap<Key, Value>::GetValue(const Key& key)
{
	return m_ValueLookup[key];
}

template<typename Key, typename Value>
Key& Bimap<Key, Value>::GetKey(const Value& value)
{
	return m_KeyLookup[value];
}

template<typename Key, typename Value>
int Bimap<Key, Value>::Count() const
{
	return m_ValueLookup.size();
}

#endif // Bimap_h__
