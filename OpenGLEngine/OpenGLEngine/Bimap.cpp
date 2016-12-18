#include "Bimap.h"

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
  return m_ValueLookup[key];
}

template<typename Key, typename Value>
Key const& Bimap<Key, Value>::GetKey(const Value& value) const
{
  return m_KeyLookup[value];
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