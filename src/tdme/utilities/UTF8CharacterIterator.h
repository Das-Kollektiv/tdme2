#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::math::Math;

using tdme::utilities::Console;

/**
 * UTF8 string character iterator
 */
class tdme::utilities::UTF8CharacterIterator {
public:

	/**
	 * UTF8 cache entry
	 */
	struct UTF8PositionCache {
		static constexpr int CACHE_ENTRY_SIZE { 100 };
		struct UTF8PositionCacheEntry {
			int binaryPosition;
			int characterPosition;
		};
		vector<UTF8PositionCacheEntry> binaryCache;
		vector<UTF8PositionCacheEntry> characterCache;
	};

	/**
	 * Public constructor
	 * @param stringReference string reference
	 * @param cache UTF8 position cache or nullptr if UTF8 positions should not be cached
	 */
	inline UTF8CharacterIterator(const string& stringReference, UTF8PositionCache* cache = nullptr): stringReference(stringReference), cache(cache) {
		//
	}

	/**
	 * Reset
	 */
	inline void reset() const {
		binaryPosition = 0;
		characterPosition = 0;
	}

	/**
	 * @return underlying binary buffer position
	 */
	inline int getBinaryPosition() const {
		return binaryPosition;
	}

	/**
	 * Set underlying binary buffer position
	 * @param position underlying buffer position
	 */
	inline void seekBinaryPosition(int position) const {
		reset();
		// seeking in cache first
		if (position >= UTF8PositionCache::CACHE_ENTRY_SIZE && cache != nullptr && cache->binaryCache.empty() == false) {
			auto cacheIdx = Math::min((position / UTF8PositionCache::CACHE_ENTRY_SIZE) - 1, cache->binaryCache.size() - 1);
			auto& cacheEntry = cache->binaryCache[cacheIdx];
			binaryPosition = cacheEntry.binaryPosition;
			characterPosition = cacheEntry.characterPosition;
		}
		//
		while (hasNext() == true && binaryPosition < position) {
			if (hasNext() == true) next();
		}
	}

	/**
	 * @return character position
	 */
 	inline int getCharacterPosition() const {
		return characterPosition;
	}

	/**
	 * Seek character position
	 * @param position character position
	 */
	inline void seekCharacterPosition(int position) const {
		reset();
		// seeking in cache first
		if (position >= UTF8PositionCache::CACHE_ENTRY_SIZE && cache != nullptr && cache->characterCache.empty() == false) {
			auto cacheIdx = Math::min((position / UTF8PositionCache::CACHE_ENTRY_SIZE) - 1, cache->characterCache.size() - 1);
			auto& cacheEntry = cache->characterCache[cacheIdx];
			binaryPosition = cacheEntry.binaryPosition;
			characterPosition = cacheEntry.characterPosition;
		}
		//
		auto seekCount = position - characterPosition;
		for (auto i = 0; i < seekCount; i++) {
			if (hasNext() == true) next();
		}
	}

	/**
	 * @return next character available
	 */
	inline bool hasNext() const {
		return binaryPosition < stringReference.size();
	}
	/**
	 * @return next character or -1 if an error occurred or no string left
	 */
	inline int next() const {
		// see: http://www.zedwood.com/article/cpp-utf8-char-to-codepoint
		int l = stringReference.size() - binaryPosition;
		if (l < 1) return -1;
		unsigned char u0 = stringReference[binaryPosition + 0];
		if (u0 >= 0 && u0 <= 127) {
			binaryPosition++;
			characterPosition++;
			addCacheEntry();
			return u0;
		}
		if (l < 2) {
			binaryPosition++;
			characterPosition++;
			addCacheEntry();
			return -1;
		}
		unsigned char u1 = stringReference[binaryPosition + 1];
		if (u0 >= 192 && u0 <= 223) {
			binaryPosition+= 2;
			characterPosition++;
			addCacheEntry();
			return (u0 - 192) * 64 + (u1 - 128);
		}
		if (u0 == 0xed && (u1 & 0xa0) == 0xa0) {
			binaryPosition+= 2;
			characterPosition++;
			addCacheEntry();
			return -1; // code points, 0xd800 to 0xdfff
		}
		if (l < 3) {
			binaryPosition+= 2;
			characterPosition++;
			addCacheEntry();
			return -1;
		}
		unsigned char u2 = stringReference[binaryPosition + 2];
		if (u0 >= 224 && u0 <= 239) {
			binaryPosition+= 3;
			characterPosition++;
			addCacheEntry();
			return (u0 - 224) * 4096 + (u1 - 128) * 64 + (u2 - 128);
		}
		if (l < 4) {
			binaryPosition+= 3;
			characterPosition++;
			addCacheEntry();
			return -1;
		}
		unsigned char u3 = stringReference[binaryPosition + 3];
		if (u0 >= 240 && u0 <= 247) {
			binaryPosition+= 4;
			characterPosition++;
			addCacheEntry();
			return (u0 - 240) * 262144 + (u1 - 128) * 4096 + (u2 - 128) * 64 + (u3 - 128);
		}
		//
		binaryPosition+= 4;
		characterPosition++;
		addCacheEntry();
		//
		return -1;
	}

private:
	const string& stringReference;
	mutable int binaryPosition { 0 };
	mutable int characterPosition { 0 };
	mutable UTF8PositionCache* cache;

	/**
	 * Add cache entry
	 */
	inline void addCacheEntry() const {
		// store every UTF8PositionCache::CACHE_ENTRY_SIZE character position, if not yet done
		if (cache != nullptr) {
			// binary cache
			{
				auto& _cache = cache->binaryCache;
				if ((binaryPosition % UTF8PositionCache::CACHE_ENTRY_SIZE) == 0 && (_cache.empty() == true || _cache[_cache.size() - 1].binaryPosition < binaryPosition)) {
					Console::println("UTF8CharacterIterator::addCacheEntry(): binary cache: binary: " + to_string(binaryPosition) + " / character: " + to_string(characterPosition));
					if (_cache.empty() == false) {
						Console::println("	was: binary cache: binary: " + to_string(_cache[_cache.size() - 1].binaryPosition) + " / character: " + to_string(_cache[_cache.size() - 1].characterPosition));
					}
					_cache.push_back(
						{
							.binaryPosition = binaryPosition,
							.characterPosition = characterPosition
						}
					);
				}
			}
			// character cache
			{
				auto& _cache = cache->characterCache;
				if ((characterPosition % UTF8PositionCache::CACHE_ENTRY_SIZE) == 0 && (_cache.empty() == true || _cache[_cache.size() - 1].characterPosition < characterPosition)) {
					Console::println("UTF8CharacterIterator::addCacheEntry(): character cache: binary: " + to_string(binaryPosition) + " / character: " + to_string(characterPosition));
					if (_cache.empty() == false) {
						Console::println("	was: binary cache: binary: " + to_string(_cache[_cache.size() - 1].binaryPosition) + " / character: " + to_string(_cache[_cache.size() - 1].characterPosition));
					}
					_cache.push_back(
						{
							.binaryPosition = binaryPosition,
							.characterPosition = characterPosition
						}
					);
				}
			}
		}
	}

};
