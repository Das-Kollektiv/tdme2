// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::Class;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Comparator;
using java::util::List;
using java::util::Set;

using java::lang::ObjectArray;

struct default_init_tag;
class java::util::Arrays
	: public virtual Object
{

public:
	typedef Object super;

private:
	static constexpr int32_t INSERTIONSORT_THRESHOLD { 7 };

	/*void ctor(); (private) */

public:
	static List* asList(ObjectArray* arg0);
	static int32_t binarySearch(int64_tArray* arg0, int64_t arg1);
	static int32_t binarySearch(int32_tArray* arg0, int32_t arg1);
	static int32_t binarySearch(int16_tArray* arg0, int16_t arg1);
	static int32_t binarySearch(char16_tArray* arg0, char16_t arg1);
	static int32_t binarySearch(int8_tArray* arg0, int8_t arg1);
	static int32_t binarySearch(doubleArray* arg0, double arg1);
	static int32_t binarySearch(floatArray* arg0, float arg1);
	static int32_t binarySearch(ObjectArray* arg0, Object* arg1);
	static int32_t binarySearch(ObjectArray* arg0, Object* arg1, Comparator* arg2);
	static int32_t binarySearch(int64_tArray* arg0, int32_t arg1, int32_t arg2, int64_t arg3);
	static int32_t binarySearch(int32_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	static int32_t binarySearch(int16_tArray* arg0, int32_t arg1, int32_t arg2, int16_t arg3);
	static int32_t binarySearch(char16_tArray* arg0, int32_t arg1, int32_t arg2, char16_t arg3);
	static int32_t binarySearch(int8_tArray* arg0, int32_t arg1, int32_t arg2, int8_t arg3);
	static int32_t binarySearch(doubleArray* arg0, int32_t arg1, int32_t arg2, double arg3);
	static int32_t binarySearch(floatArray* arg0, int32_t arg1, int32_t arg2, float arg3);
	static int32_t binarySearch(ObjectArray* arg0, int32_t arg1, int32_t arg2, Object* arg3);
	static int32_t binarySearch(ObjectArray* arg0, int32_t arg1, int32_t arg2, Object* arg3, Comparator* arg4);
	/*static int32_t binarySearch0(int64_tArray* arg0, int32_t arg1, int32_t arg2, int64_t arg3); (private) */
	/*static int32_t binarySearch0(int32_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static int32_t binarySearch0(int16_tArray* arg0, int32_t arg1, int32_t arg2, int16_t arg3); (private) */
	/*static int32_t binarySearch0(char16_tArray* arg0, int32_t arg1, int32_t arg2, char16_t arg3); (private) */
	/*static int32_t binarySearch0(int8_tArray* arg0, int32_t arg1, int32_t arg2, int8_t arg3); (private) */
	/*static int32_t binarySearch0(doubleArray* arg0, int32_t arg1, int32_t arg2, double arg3); (private) */
	/*static int32_t binarySearch0(floatArray* arg0, int32_t arg1, int32_t arg2, float arg3); (private) */
	/*static int32_t binarySearch0(ObjectArray* arg0, int32_t arg1, int32_t arg2, Object* arg3); (private) */
	/*static int32_t binarySearch0(ObjectArray* arg0, int32_t arg1, int32_t arg2, Object* arg3, Comparator* arg4); (private) */
	static ObjectArray* copyOf(ObjectArray* arg0, int32_t arg1);
	static int8_tArray* copyOf(int8_tArray* arg0, int32_t arg1);
	static int16_tArray* copyOf(int16_tArray* arg0, int32_t arg1);
	static int32_tArray* copyOf(int32_tArray* arg0, int32_t arg1);
	static int64_tArray* copyOf(int64_tArray* arg0, int32_t arg1);
	static char16_tArray* copyOf(char16_tArray* arg0, int32_t arg1);
	static floatArray* copyOf(floatArray* arg0, int32_t arg1);
	static doubleArray* copyOf(doubleArray* arg0, int32_t arg1);
	static boolArray* copyOf(boolArray* arg0, int32_t arg1);
	static ObjectArray* copyOf(ObjectArray* arg0, int32_t arg1, Class* arg2);
	static ObjectArray* copyOfRange(ObjectArray* arg0, int32_t arg1, int32_t arg2);
	static int8_tArray* copyOfRange(int8_tArray* arg0, int32_t arg1, int32_t arg2);
	static int16_tArray* copyOfRange(int16_tArray* arg0, int32_t arg1, int32_t arg2);
	static int32_tArray* copyOfRange(int32_tArray* arg0, int32_t arg1, int32_t arg2);
	static int64_tArray* copyOfRange(int64_tArray* arg0, int32_t arg1, int32_t arg2);
	static char16_tArray* copyOfRange(char16_tArray* arg0, int32_t arg1, int32_t arg2);
	static floatArray* copyOfRange(floatArray* arg0, int32_t arg1, int32_t arg2);
	static doubleArray* copyOfRange(doubleArray* arg0, int32_t arg1, int32_t arg2);
	static boolArray* copyOfRange(boolArray* arg0, int32_t arg1, int32_t arg2);
	static ObjectArray* copyOfRange(ObjectArray* arg0, int32_t arg1, int32_t arg2, Class* arg3);
	static bool deepEquals(ObjectArray* arg0, ObjectArray* arg1);
	static int32_t deepHashCode(ObjectArray* arg0);
	static String* deepToString(ObjectArray* arg0);
	/*static void deepToString(ObjectArray* arg0, StringBuilder* arg1, Set* arg2); (private) */
	static bool equals(int64_tArray* arg0, int64_tArray* arg1);
	static bool equals(int32_tArray* arg0, int32_tArray* arg1);
	static bool equals(int16_tArray* arg0, int16_tArray* arg1);
	static bool equals(char16_tArray* arg0, char16_tArray* arg1);
	static bool equals(int8_tArray* arg0, int8_tArray* arg1);
	static bool equals(boolArray* arg0, boolArray* arg1);
	static bool equals(doubleArray* arg0, doubleArray* arg1);
	static bool equals(floatArray* arg0, floatArray* arg1);
	static bool equals(ObjectArray* arg0, ObjectArray* arg1);
	static void fill(int64_tArray* arg0, int64_t arg1);
	static void fill(int32_tArray* arg0, int32_t arg1);
	static void fill(int16_tArray* arg0, int16_t arg1);
	static void fill(char16_tArray* arg0, char16_t arg1);
	static void fill(int8_tArray* arg0, int8_t arg1);
	static void fill(boolArray* arg0, bool arg1);
	static void fill(doubleArray* arg0, double arg1);
	static void fill(floatArray* arg0, float arg1);
	static void fill(ObjectArray* arg0, Object* arg1);
	static void fill(int64_tArray* arg0, int32_t arg1, int32_t arg2, int64_t arg3);
	static void fill(int32_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	static void fill(int16_tArray* arg0, int32_t arg1, int32_t arg2, int16_t arg3);
	static void fill(char16_tArray* arg0, int32_t arg1, int32_t arg2, char16_t arg3);
	static void fill(int8_tArray* arg0, int32_t arg1, int32_t arg2, int8_t arg3);
	static void fill(boolArray* arg0, int32_t arg1, int32_t arg2, bool arg3);
	static void fill(doubleArray* arg0, int32_t arg1, int32_t arg2, double arg3);
	static void fill(floatArray* arg0, int32_t arg1, int32_t arg2, float arg3);
	static void fill(ObjectArray* arg0, int32_t arg1, int32_t arg2, Object* arg3);
	static int32_t hashCode(int64_tArray* arg0);
	static int32_t hashCode(int32_tArray* arg0);
	static int32_t hashCode(int16_tArray* arg0);
	static int32_t hashCode(char16_tArray* arg0);
	static int32_t hashCode(int8_tArray* arg0);
	static int32_t hashCode(boolArray* arg0);
	static int32_t hashCode(floatArray* arg0);
	static int32_t hashCode(doubleArray* arg0);
	static int32_t hashCode(ObjectArray* arg0);
	/*static int32_t med3(int64_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static int32_t med3(int32_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static int32_t med3(int16_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static int32_t med3(char16_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static int32_t med3(int8_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static int32_t med3(doubleArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static int32_t med3(floatArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static void mergeSort(ObjectArray* arg0, ObjectArray* arg1, int32_t arg2, int32_t arg3, int32_t arg4); (private) */
	/*static void mergeSort(ObjectArray* arg0, ObjectArray* arg1, int32_t arg2, int32_t arg3, int32_t arg4, Comparator* arg5); (private) */
	/*static void rangeCheck(int32_t arg0, int32_t arg1, int32_t arg2); (private) */
	static void sort(int64_tArray* arg0);
	static void sort(int32_tArray* arg0);
	static void sort(int16_tArray* arg0);
	static void sort(char16_tArray* arg0);
	static void sort(int8_tArray* arg0);
	static void sort(doubleArray* arg0);
	static void sort(floatArray* arg0);
	static void sort(ObjectArray* arg0);
	static void sort(ObjectArray* arg0, Comparator* arg1);
	static void sort(int64_tArray* arg0, int32_t arg1, int32_t arg2);
	static void sort(int32_tArray* arg0, int32_t arg1, int32_t arg2);
	static void sort(int16_tArray* arg0, int32_t arg1, int32_t arg2);
	static void sort(char16_tArray* arg0, int32_t arg1, int32_t arg2);
	static void sort(int8_tArray* arg0, int32_t arg1, int32_t arg2);
	static void sort(doubleArray* arg0, int32_t arg1, int32_t arg2);
	static void sort(floatArray* arg0, int32_t arg1, int32_t arg2);
	static void sort(ObjectArray* arg0, int32_t arg1, int32_t arg2);
	static void sort(ObjectArray* arg0, int32_t arg1, int32_t arg2, Comparator* arg3);
	/*static void sort1(int64_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void sort1(int32_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void sort1(int16_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void sort1(char16_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void sort1(int8_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void sort1(doubleArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void sort1(floatArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void sort2(doubleArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void sort2(floatArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void swap(int64_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void swap(int32_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void swap(int16_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void swap(char16_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void swap(int8_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void swap(doubleArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void swap(floatArray* arg0, int32_t arg1, int32_t arg2); (private) */
	/*static void swap(ObjectArray* arg0, int32_t arg1, int32_t arg2); (private) */
	static String* toString(int64_tArray* arg0);
	static String* toString(int32_tArray* arg0);
	static String* toString(int16_tArray* arg0);
	static String* toString(char16_tArray* arg0);
	static String* toString(int8_tArray* arg0);
	static String* toString(boolArray* arg0);
	static String* toString(floatArray* arg0);
	static String* toString(doubleArray* arg0);
	static String* toString(ObjectArray* arg0);
	/*static void vecswap(int64_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static void vecswap(int32_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static void vecswap(int16_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static void vecswap(char16_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static void vecswap(int8_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static void vecswap(doubleArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */
	/*static void vecswap(floatArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3); (private) */

	// Generated
	Arrays();
protected:
	Arrays(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
