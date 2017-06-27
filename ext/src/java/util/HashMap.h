// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/AbstractMap.h>
#include <java/util/Map.h>
#include <java/lang/Cloneable.h>
#include <java/io/Serializable.h>

using java::util::AbstractMap;
using java::util::Map;
using java::lang::Cloneable;
using java::io::Serializable;
using java::io::ObjectInputStream;
using java::io::ObjectOutputStream;
using java::lang::Object;
using java::util::Collection;
using java::util::HashMap_Entry;
using java::util::Iterator;
using java::util::Map_Entry;
using java::util::Set;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace util {
typedef ::SubArray< ::java::util::Map_Entry, ::java::lang::ObjectArray > Map_EntryArray;
typedef ::SubArray< ::java::util::HashMap_Entry, ::java::lang::ObjectArray, Map_EntryArray > HashMap_EntryArray;
}  // namespace util
}  // namespace java

using java::lang::ObjectArray;
using java::util::HashMap_EntryArray;
using java::util::Map_EntryArray;

struct default_init_tag;
class java::util::HashMap
	: public AbstractMap
	, public virtual Map
	, public virtual Cloneable
	, public virtual Serializable
{

public:
	typedef AbstractMap super;

public: /* package */
	static constexpr int32_t DEFAULT_INITIAL_CAPACITY { 16 };
	static constexpr float DEFAULT_LOAD_FACTOR { 0.75f };
	static constexpr int32_t MAXIMUM_CAPACITY { 1073741824 };

private:
	Set* entrySet_ {  };

public: /* package */
	float loadFactor_ {  };
	std::atomic< int32_t > modCount {  };

private:
	static constexpr int64_t serialVersionUID { 362498820763181265LL };

public: /* package */
	int32_t size_ {  };
	HashMap_EntryArray* table {  };
	int32_t threshold {  };

protected:
	void ctor();
	void ctor(int32_t arg0);
	void ctor(Map* arg0);
	void ctor(int32_t arg0, float arg1);

public: /* package */
	virtual void addEntry(int32_t arg0, Object* arg1, Object* arg2, int32_t arg3);
	virtual int32_t capacity();

public:
	void clear() override;
	Object* clone() override;
	bool containsKey(Object* arg0) override;
	/*bool containsNullValue(); (private) */
	bool containsValue(Object* arg0) override;

public: /* package */
	virtual void createEntry(int32_t arg0, Object* arg1, Object* arg2, int32_t arg3);

public:
	Set* entrySet() override;
	/*Set* entrySet0(); (private) */
	Object* get(Object* arg0) override;

public: /* package */
	HashMap_Entry* getEntry(Object* arg0);
	/*Object* getForNullKey(); (private) */
	static int32_t hash(int32_t arg0);
	static int32_t indexFor(int32_t arg0, int32_t arg1);
	virtual void init_();

public:
	bool isEmpty() override;
	Set* keySet() override;

public: /* package */
	virtual float loadFactor();
	virtual Iterator* newEntryIterator();
	virtual Iterator* newKeyIterator();
	virtual Iterator* newValueIterator();

public:
	Object* put(Object* arg0, Object* arg1) override;
	void putAll(Map* arg0) override;
	/*void putAllForCreate(Map* arg0); (private) */
	/*void putForCreate(Object* arg0, Object* arg1); (private) */
	/*Object* putForNullKey(Object* arg0); (private) */
	/*void readObject(ObjectInputStream* arg0); (private) */
	Object* remove(Object* arg0) override;

public: /* package */
	HashMap_Entry* removeEntryForKey(Object* arg0);
	HashMap_Entry* removeMapping(Object* arg0);
	virtual void resize(int32_t arg0);

public:
	int32_t size() override;

public: /* package */
	virtual void transfer(HashMap_EntryArray* arg0);

public:
	Collection* values() override;
	/*void writeObject(ObjectOutputStream* arg0); (private) */

	// Generated
	HashMap();
	HashMap(int32_t arg0);
	HashMap(Map* arg0);
	HashMap(int32_t arg0, float arg1);
protected:
	HashMap(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual bool equals(Object* arg0);
	virtual int32_t hashCode();

private:
	virtual ::java::lang::Class* getClass0();
};
