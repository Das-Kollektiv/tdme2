// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/Dictionary.h>
#include <java/util/Map.h>
#include <java/lang/Cloneable.h>
#include <java/io/Serializable.h>

using java::util::Dictionary;
using java::util::Map;
using java::lang::Cloneable;
using java::io::Serializable;
using java::io::ObjectInputStream;
using java::io::ObjectOutputStream;
using java::lang::Object;
using java::lang::String;
using java::util::Collection;
using java::util::Enumeration;
using java::util::Hashtable_Entry;
using java::util::Iterator;
using java::util::Map_Entry;
using java::util::Set;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace util {
typedef ::SubArray< ::java::util::Map_Entry, ::java::lang::ObjectArray > Map_EntryArray;
typedef ::SubArray< ::java::util::Hashtable_Entry, ::java::lang::ObjectArray, Map_EntryArray > Hashtable_EntryArray;
}  // namespace util
}  // namespace java

using java::lang::ObjectArray;
using java::util::Hashtable_EntryArray;
using java::util::Map_EntryArray;

struct default_init_tag;
class java::util::Hashtable
	: public Dictionary
	, public virtual Map
	, public virtual Cloneable
	, public virtual Serializable
{

public:
	typedef Dictionary super;

private:
	static constexpr int32_t ENTRIES { 2 };
	static constexpr int32_t KEYS { 0 };
	static constexpr int32_t VALUES { 1 };
	int32_t count {  };
	static Enumeration* emptyEnumerator;
	static Iterator* emptyIterator;
	std::atomic< Set* > entrySet_ {  };
	std::atomic< Set* > keySet_ {  };
	float loadFactor {  };
	int32_t modCount {  };
	static constexpr int64_t serialVersionUID { 1421746759512286392LL };
	Hashtable_EntryArray* table {  };
	int32_t threshold {  };
	std::atomic< Collection* > values_ {  };

protected:
	void ctor();
	void ctor(int32_t arg0);
	void ctor(Map* arg0);
	void ctor(int32_t arg0, float arg1);

public:
	void clear() override;
	Object* clone() override;
	virtual bool contains(Object* arg0);
	bool containsKey(Object* arg0) override;
	bool containsValue(Object* arg0) override;
	Enumeration* elements() override;
	Set* entrySet() override;
	bool equals(Object* arg0) override;
	Object* get(Object* arg0) override;
	/*Enumeration* getEnumeration(int32_t arg0); (private) */
	/*Iterator* getIterator(int32_t arg0); (private) */
	int32_t hashCode() override;
	bool isEmpty() override;
	Set* keySet() override;
	Enumeration* keys() override;
	Object* put(Object* arg0, Object* arg1) override;
	void putAll(Map* arg0) override;
	/*void readObject(ObjectInputStream* arg0); (private) */
	/*void reconstitutionPut(Hashtable_EntryArray* arg0, Object* arg1, Object* arg2); (private) */

public: /* protected */
	virtual void rehash();

public:
	Object* remove(Object* arg0) override;
	int32_t size() override;
	String* toString() override;
	Collection* values() override;
	/*void writeObject(ObjectOutputStream* arg0); (private) */

	// Generated
	Hashtable();
	Hashtable(int32_t arg0);
	Hashtable(Map* arg0);
	Hashtable(int32_t arg0, float arg1);
protected:
	Hashtable(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
