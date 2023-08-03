#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::make_unique;
using std::string;
using std::to_string;
using std::vector;
using std::unique_ptr;
using std::unordered_map;

using tdme::utilities::Console;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

int main(int argc, char** argv)
{
	// vector tests
	{
		vector<int> vector = { 1, 2, 3, 4, 5 };
		Console::println("vector = { 1, 2, 3, 4, 5 }, capacity = " + to_string(vector.capacity()));
		vector.clear();
		Console::println("vector.clear(), capacity = " + to_string(vector.capacity()));
		vector = { 1, 2, 3 };
		Console::println("vector = { 1, 2, 3 }, capacity = " + to_string(vector.capacity()));
		vector.resize(2);
		Console::println("vector.resize(2), capacity = " + to_string(vector.capacity()));
		vector.resize(6);
		Console::println("vector.resize(6), capacity = " + to_string(vector.capacity()));
		vector.resize(12);
		Console::println("vector.resize(12), capacity = " + to_string(vector.capacity()));
		vector.resize(3);
		Console::println("vector.resize(3), capacity = " + to_string(vector.capacity()));
	}
	// map tests
	{
		unordered_map<string, string> map {
			{"0", "a"},
			{"1", "b"},
			{"2", "c"}
		};
		for (auto& [key, value]: map) {
			Console::println(key + " -> " + value);
		}
		struct PtrTest {
			int v { -1 };
			int a { 1 };
			int b { 2 };
			int c { 3 };
			PtrTest(int v): v(v) {
				// Console::println("PtrTest(): " + to_string(v));
			}
			~PtrTest() {
				// Console::println("~PtrTest(): " + to_string(v));
			}
		};
		// testing performance of map with string key and raw pointer
		unordered_map<string, PtrTest*> map2;
		{
			Console::println("map2: inserting entries: init");
			auto startTime = Time::getCurrentMillis();
			for (auto i = 0; i < 10000000; i++) {
				map2[to_string(i)] = new PtrTest(i);
			}
			auto endTime = Time::getCurrentMillis();
			Console::println("map2: inserting entries: done in " + to_string(endTime - startTime) + " ms");
		}
		{
			Console::println("map2: getting entries: init");
			auto startTime = Time::getCurrentMillis();
			auto x = 0ll;
			for (auto i = 0; i < 10000000; i++) {
				auto it = map2.find(to_string(i));
				if (it == map2.end()) continue;
				x+= it->second->v;
			}
			auto endTime = Time::getCurrentMillis();
			Console::println("map2: getting entries: done in " + to_string(endTime - startTime) + " ms");
			Console::println(to_string(x));
		}
		// testing performance of map with string key and smart pointer
		unordered_map<string, unique_ptr<PtrTest>> map3;
		{
			Console::println("map3: inserting entries: init");
			auto startTime = Time::getCurrentMillis();
			for (auto i = 0; i < 10000000; i++) {
				map3[to_string(i)] = make_unique<PtrTest>(i);
			}
			auto endTime = Time::getCurrentMillis();
			Console::println("map3: inserting entries: done in " + to_string(endTime - startTime) + " ms");
		}
		{
			Console::println("map3: getting entries: init");
			auto startTime = Time::getCurrentMillis();
			auto x = 0ll;
			for (auto i = 0; i < 10000000; i++) {
				auto it = map3.find(to_string(i));
				if (it == map3.end()) continue;
				x+= it->second->v;
			}
			auto endTime = Time::getCurrentMillis();
			Console::println("map3: getting entries: done in " + to_string(endTime - startTime) + " ms");
			Console::println(to_string(x));
		}
		//
		{
			unique_ptr<PtrTest> nullPtr;
			if (nullPtr == nullptr) {
				Console::println("Yarrrr: nullPtr == nullptr");
			} else {
				Console::println("Damn: nullPtr != nullptr");
			}
		}
		{
			unique_ptr<PtrTest> onePtr = make_unique<PtrTest>(1);
			if (onePtr == nullptr) {
				Console::println("Damn: onePtr == nullptr");
			} else {
				Console::println("Yarrrr: onePtr != nullptr");
			}
		}
		// ok: conclusion: on Windows with MSC/MINGW smart pointers here come with a 10%-25% performance penalty
		//	so we might not want to have this at performance critical code
	}
	//
    return 0;
}
