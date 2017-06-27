// Generated from /tdme/src/tdme/utils/QuickSort.java

#pragma once

#include <fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::util::Comparator;
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * Quick sort
 * based on http://www.programcreek.com/2012/11/quicksort-array-in-java/
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::QuickSort final
	: public Object
{

public:
	typedef Object super;

	/** 
	 * Quick sort
	 * @param array
	 */
	static void sort(_ArrayList* array);

private:

	/** 
	 * Quick sort
	 * @param array list
	 * @param low
	 * @param high
	 */
	static void quickSort(_ArrayList* array, int32_t low, int32_t high);

public:

	/** 
	 * Quick sort
	 * @param array
	 * @param comparator
	 */
	static void sort(_ArrayList* array, Comparator* comparator);

private:

	/** 
	 * Quick sort
	 * @param array list
	 * @param low
	 * @param high
	 * @param comparator
	 */
	static void quickSort(_ArrayList* array, Comparator* comparator, int32_t low, int32_t high);

	// Generated

public:
	QuickSort();
protected:
	QuickSort(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
