#include <array>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/UniquePtrSequenceIterator.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::array;
using std::make_unique;
using std::string;
using std::to_string;
using std::vector;
using std::unique_ptr;
using std::unordered_map;

using tdme::utilities::Console;
using tdme::utilities::UniquePtrSequenceIterator;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

int main(int argc, char** argv)
{
	// custom iterator test
	{
		struct PtrTest {
			int v { -1 };
			int a { 1 };
			int b { 2 };
			int c { 3 };
			PtrTest(int v): v(v) {
				// Console::printLine("PtrTest(): " + to_string(v));
			}
			~PtrTest() {
				// Console::printLine("~PtrTest(): " + to_string(v));
			}
		};
		// array
		array<unique_ptr<PtrTest>, 3> array {
			make_unique<PtrTest>(1),
			make_unique<PtrTest>(2),
			make_unique<PtrTest>(3)
		};
		Console::printLine("array: iterating entries 1, 2, 3 via SequenceContainerIterator");
		for (auto v: UniquePtrSequenceIterator<PtrTest>(&(*array.begin()), &(*array.end()))) {
			Console::printLine(to_string(v->v));
		}
		// vector
		vector<unique_ptr<PtrTest>> vector;
		vector.push_back(make_unique<PtrTest>(4));
		vector.push_back(make_unique<PtrTest>(5));
		vector.push_back(make_unique<PtrTest>(6));
		Console::printLine("vector: iterating entries 4, 5, 6 via SequenceContainerIterator");
		for (auto v: UniquePtrSequenceIterator<PtrTest>(&(*vector.begin()), &(*vector.end()))) {
			Console::printLine(to_string(v->v));
		}
	}
	// vector tests
	{
		vector<int> vector = { 1, 2, 3, 4, 5 };
		Console::printLine("vector = { 1, 2, 3, 4, 5 }, capacity = " + to_string(vector.capacity()));
		vector.clear();
		Console::printLine("vector.clear(), capacity = " + to_string(vector.capacity()));
		vector = { 1, 2, 3 };
		Console::printLine("vector = { 1, 2, 3 }, capacity = " + to_string(vector.capacity()));
		vector.resize(2);
		Console::printLine("vector.resize(2), capacity = " + to_string(vector.capacity()));
		vector.resize(6);
		Console::printLine("vector.resize(6), capacity = " + to_string(vector.capacity()));
		vector.resize(12);
		Console::printLine("vector.resize(12), capacity = " + to_string(vector.capacity()));
		vector.resize(3);
		Console::printLine("vector.resize(3), capacity = " + to_string(vector.capacity()));
	}
	// unique_ptr
	Console::printLine("unique_ptr: sizeof: " + to_string(sizeof(unique_ptr<void*>)));
	// map tests
	{
		//
		unordered_map<string, string> map {
			{"0", "a"},
			{"1", "b"},
			{"2", "c"}
		};
		for (auto& [key, value]: map) {
			Console::printLine(key + " -> " + value);
		}
	}
	// testing performance of unique_ptr with vector and map containers
	{
		struct PtrTest {
			int v { -1 };
			int a { 1 };
			int b { 2 };
			int c { 3 };
			PtrTest(int v): v(v) {
				// Console::printLine("PtrTest(): " + to_string(v));
			}
			~PtrTest() {
				// Console::printLine("~PtrTest(): " + to_string(v));
			}
		};
		{
			// testing performance of map with string key and raw pointer
			unordered_map<string, PtrTest*> map1;
			{
				Console::printLine("map1: inserting entries: init");
				auto startTime = Time::getCurrentMillis();
				for (auto i = 0; i < 10000000; i++) {
					map1[to_string(i)] = new PtrTest(i);
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("map1: inserting entries: done in " + to_string(endTime - startTime) + " ms");
			}
			{
				Console::printLine("map1: getting entries: init");
				auto startTime = Time::getCurrentMillis();
				auto x = 0ll;
				for (auto i = 0; i < 10000000; i++) {
					auto it = map1.find(to_string(i));
					if (it == map1.end()) continue;
					x+= it->second->v;
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("map1: getting entries: done in " + to_string(endTime - startTime) + " ms");
				Console::printLine(to_string(x));
			}
			{
				Console::printLine("map1: deleting entries: init");
				auto startTime = Time::getCurrentMillis();
				for (auto i = 0; i < 10000000; i++) {
					delete map1[to_string(i)];
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("map1: deleting entries: done in " + to_string(endTime - startTime) + " ms");
			}
		}
		{
			// testing performance of map with string key and smart pointer
			unordered_map<string, unique_ptr<PtrTest>> map2;
			{
				Console::printLine("map2: inserting entries: init");
				auto startTime = Time::getCurrentMillis();
				for (auto i = 0; i < 10000000; i++) {
					map2[to_string(i)] = make_unique<PtrTest>(i);
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("map2: inserting entries: done in " + to_string(endTime - startTime) + " ms");
			}
			{
				Console::printLine("map2: getting entries: init");
				auto startTime = Time::getCurrentMillis();
				auto x = 0ll;
				for (auto i = 0; i < 10000000; i++) {
					auto it = map2.find(to_string(i));
					if (it == map2.end()) continue;
					x+= it->second->v;
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("map2: getting entries: done in " + to_string(endTime - startTime) + " ms");
				Console::printLine(to_string(x));
			}
		}
		//
		{
			unique_ptr<PtrTest> nullPtr;
			if (nullPtr == nullptr) {
				Console::printLine("Yarrrr: nullPtr == nullptr");
			} else {
				Console::printLine("Damn: nullPtr != nullptr");
			}
		}
		{
			unique_ptr<PtrTest> onePtr = make_unique<PtrTest>(1);
			if (onePtr == nullptr) {
				Console::printLine("Damn: onePtr == nullptr");
			} else {
				Console::printLine("Yarrrr: onePtr != nullptr");
			}
		}
		// ok: conclusion: on Windows with MSC/MINGW smart pointers here come with a 10%-25% performance penalty
		//	so we might not want to have this at performance critical code
		// testing performance of vector with raw pointer vs. smart pointer
		{
			vector<PtrTest*> vector1;
			{
				Console::printLine("vector1: inserting entries: init");
				auto startTime = Time::getCurrentMillis();
				vector1.resize(10000000);
				for (auto i = 0; i < 10000000; i++) {
					vector1[i] = new PtrTest(i);
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("vector1: inserting entries: done in " + to_string(endTime - startTime) + " ms");
			}
			{
				Console::printLine("vector1: getting entries: init");
				auto startTime = Time::getCurrentMillis();
				auto x = 0ll;
				for (auto i = 0; i < 10000000; i++) {
					x+= vector1[i]->v;
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("vector1: getting entries: done in " + to_string(endTime - startTime) + " ms");
				Console::printLine(to_string(x));
			}
			{
				Console::printLine("vector1: iterator: getting entries: init");
				auto startTime = Time::getCurrentMillis();
				auto x = 0ll;
				for (auto v: vector1) {
					x+= v->v;
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("vector1: iterator: getting entries: done in " + to_string(endTime - startTime) + " ms");
				Console::printLine(to_string(x));
			}
			{
				Console::printLine("vector1: deleting entries: init");
				auto startTime = Time::getCurrentMillis();
				vector1.resize(10000000);
				for (auto i = 0; i < 10000000; i++) {
					delete vector1[i];
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("vector1: deleting entries: done in " + to_string(endTime - startTime) + " ms");
			}
		}
		//
		{
			vector<unique_ptr<PtrTest>> vector2;
			{
				Console::printLine("vector2: inserting entries: init");
				auto startTime = Time::getCurrentMillis();
				vector2.resize(10000000);
				for (auto i = 0; i < 10000000; i++) {
					vector2[i] = make_unique<PtrTest>(i);
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("vector2: inserting entries: done in " + to_string(endTime - startTime) + " ms");
			}
			{
				Console::printLine("vector2: getting entries: init");
				auto startTime = Time::getCurrentMillis();
				auto x = 0ll;
				for (auto i = 0; i < 10000000; i++) {
					x+= vector2[i]->v;
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("vector2: getting entries: done in " + to_string(endTime - startTime) + " ms");
				Console::printLine(to_string(x));
			}
			{
				Console::printLine("vector2: iterator: getting entries: init");
				auto startTime = Time::getCurrentMillis();
				auto x = 0ll;
				for (const auto& v: vector2) {
					x+= v->v;
				}
				auto endTime = Time::getCurrentMillis();
				Console::printLine("vector2: iterator: getting entries: done in " + to_string(endTime - startTime) + " ms");
				Console::printLine(to_string(x));
			}
		}
	}
	//
	Console::shutdown();
	return 0;
}
