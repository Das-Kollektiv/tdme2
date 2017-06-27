// Generated from /tdme/src/tdme/utils/QuickSort.java
#include <tdme/utils/QuickSort.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Object.h>
#include <java/util/Comparator.h>
#include <tdme/utils/_ArrayList.h>

using tdme::utils::QuickSort;
using java::lang::ClassCastException;
using java::lang::Comparable;
using java::lang::Object;
using java::util::Comparator;
using tdme::utils::_ArrayList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

QuickSort::QuickSort(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

QuickSort::QuickSort()
	: QuickSort(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void QuickSort::sort(_ArrayList* array)
{
	clinit();
	quickSort(array, 0, array->size() - 1);
}

void QuickSort::quickSort(_ArrayList* array, int32_t low, int32_t high)
{
	clinit();
	if (array == nullptr || array->size() == 0)
		return;

	if (low >= high)
		return;

	auto middle = low + (high - low) / 2;
	auto pivot = java_cast< Comparable* >(array->get(middle));
	int32_t i = low, j = high;
	while (i <= j) {
		while ((java_cast< Comparable* >(array->get(i)))->compareTo(pivot) < 0) {
			i++;
		}
		while ((java_cast< Comparable* >(array->get(j)))->compareTo(pivot) > 0) {
			j--;
		}
		if (i <= j) {
			auto temp = java_cast< Comparable* >(array->get(i));
			array->set(i, java_cast< Comparable* >(array->get(j)));
			array->set(j, temp);
			i++;
			j--;
		}
	}
	if (low < j)
		quickSort(array, low, j);

	if (high > i)
		quickSort(array, i, high);

}

void QuickSort::sort(_ArrayList* array, Comparator* comparator)
{
	clinit();
	quickSort(array, comparator, 0, array->size() - 1);
}

void QuickSort::quickSort(_ArrayList* array, Comparator* comparator, int32_t low, int32_t high)
{
	clinit();
	if (array == nullptr || array->size() == 0)
		return;

	if (low >= high)
		return;

	auto middle = low + (high - low) / 2;
	auto pivot = java_cast< Object* >(array->get(middle));
	int32_t i = low, j = high;
	while (i <= j) {
		while (comparator->compare(java_cast< Object* >(array->get(i)), pivot) < 0) {
			i++;
		}
		while (comparator->compare(java_cast< Object* >(array->get(j)), pivot) > 0) {
			j--;
		}
		if (i <= j) {
			auto temp = java_cast< Object* >(array->get(i));
			array->set(i, java_cast< Object* >(array->get(j)));
			array->set(j, temp);
			i++;
			j--;
		}
	}
	if (low < j)
		quickSort(array, comparator, low, j);

	if (high > i)
		quickSort(array, comparator, i, high);

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* QuickSort::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.utils.QuickSort", 20);
    return c;
}

java::lang::Class* QuickSort::getClass0()
{
	return class_();
}

