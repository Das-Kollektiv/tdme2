#pragma once

#include <string>
#include <vector>

#include <yannet/yannet.h>
#include <yannet/math/Math.h>
#include <yannet/utilities/fwd-yannet.h>
#include <yannet/utilities/Console.h>

using std::string;
using std::to_string;
using std::vector;

// name spaces
namespace yannet {
namespace utilities {
	using yannet::math::Math;
	using yannet::utilities::Console;
}
}

/**
 * UTF8 string character iterator
 */
class yannet::utilities::UTF8CharacterIterator {
public:
	/**
	 * UTF8 cache entry
	 */
	class UTF8PositionCache {
		friend class UTF8CharacterIterator;
	public:
		static constexpr int64_t CACHE_ENTRY_SIZE { 100 };

		/**
		 * Remove cache
		 */
		inline void removeCache() {
			binaryCache.clear();
			characterCache.clear();
		}

		/**
		 * Remove from cache by binary index
		 * @param idx binary index
		 */
		inline void removeCache(int64_t binaryIdx, int64_t characterIdx) {
			// Console::printLine("MutableString::removeCache(): binary: " + to_string(binaryIdx) + ", character: " + to_string(characterIdx));
			// remove succeeding entries from binary cache
			if (binaryIdx >= UTF8CharacterIterator::UTF8PositionCache::CACHE_ENTRY_SIZE) {
				auto& _cache = binaryCache;
				auto removeFromCacheEntryIdx = (binaryIdx / UTF8CharacterIterator::UTF8PositionCache::CACHE_ENTRY_SIZE) - 1;
				// Console::printLine("\tRemoving binary: " + to_string(removeFromCacheEntryIdx) + " / " + to_string(_cache.size() - 1) + " = " + to_string((removeFromCacheEntryIdx + 1) * UTF8CharacterIterator::UTF8PositionCache::CACHE_ENTRY_SIZE));
				if (removeFromCacheEntryIdx < _cache.size()) {
					_cache.erase(_cache.begin() + removeFromCacheEntryIdx, _cache.end());
				}
			} else {
				binaryCache.clear();
			}
			// remove succeeding entries from character position cache
			if (characterIdx >= UTF8CharacterIterator::UTF8PositionCache::CACHE_ENTRY_SIZE) {
				auto& _cache = characterCache;
				auto removeFromCacheEntryIdx = (characterIdx / UTF8CharacterIterator::UTF8PositionCache::CACHE_ENTRY_SIZE) - 1;
				// Console::printLine("\tRemoving character: " + to_string(removeFromCacheEntryIdx) + " / " + to_string(_cache.size() - 1) + " = " + to_string((removeFromCacheEntryIdx + 1) * UTF8CharacterIterator::UTF8PositionCache::CACHE_ENTRY_SIZE));
				if (removeFromCacheEntryIdx < _cache.size()) {
					_cache.erase(_cache.begin() + removeFromCacheEntryIdx, _cache.end());
				}
			} else {
				characterCache.clear();
			}
		}

	private:
		struct UTF8PositionCacheEntry {
			UTF8PositionCacheEntry(
				int64_t binaryPosition,
				int64_t characterPosition
			):
				binaryPosition(binaryPosition),
				characterPosition(characterPosition)
			{}
			int64_t binaryPosition;
			int64_t characterPosition;
		};
		vector<UTF8PositionCacheEntry> binaryCache;
		vector<UTF8PositionCacheEntry> characterCache;
	};

	// forbid class copy
	FORBID_CLASS_COPY(UTF8CharacterIterator)

	/**
	 * Public constructor
	 * @param stringView string view
	 * @param cache UTF8 position cache or nullptr if UTF8 positions should not be cached
	 */
	inline UTF8CharacterIterator(const string_view& stringView, UTF8PositionCache* cache = nullptr): stringView(stringView), cache(cache) {
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
	inline int64_t getBinaryPosition() const {
		return binaryPosition;
	}

	/**
	 * Set underlying binary buffer position
	 * @param position underlying buffer position
	 */
	inline void seekBinaryPosition(int64_t position) const {
		reset();
		// seeking in cache first
		if (position >= UTF8PositionCache::CACHE_ENTRY_SIZE && cache != nullptr && cache->binaryCache.empty() == false) {
			auto cacheIdx = Math::min((position / UTF8PositionCache::CACHE_ENTRY_SIZE) - 1, cache->binaryCache.size() - 1);
			const auto& cacheEntry = cache->binaryCache[cacheIdx];
			binaryPosition = cacheEntry.binaryPosition;
			characterPosition = cacheEntry.characterPosition;
		}
		//
		while (hasNext() == true && binaryPosition < position) {
			if (hasNext() == false) break;
			next();
		}
	}

	/**
	 * @return character position
	 */
 	inline int64_t getCharacterPosition() const {
		return characterPosition;
	}

	/**
	 * Seek character position
	 * @param position character position
	 */
	inline void seekCharacterPosition(int64_t position) const {
		reset();
		// seeking in cache first
		if (position >= UTF8PositionCache::CACHE_ENTRY_SIZE && cache != nullptr && cache->characterCache.empty() == false) {
			auto cacheIdx = Math::min((position / UTF8PositionCache::CACHE_ENTRY_SIZE) - 1, cache->characterCache.size() - 1);
			const auto& cacheEntry = cache->characterCache[cacheIdx];
			binaryPosition = cacheEntry.binaryPosition;
			characterPosition = cacheEntry.characterPosition;
		}
		//
		auto seekCount = position - characterPosition;
		for (int64_t i = 0; i < seekCount; i++) {
			if (hasNext() == false) break;
			next();
		}
	}

	/**
	 * @return next character available
	 */
	inline bool hasNext() const {
		return binaryPosition < stringView.size();
	}
	/**
	 * @return next character or -1 if an error occurred or no string left
	 */
	inline int next() const {
		// see: http://www.zedwood.com/article/cpp-utf8-char-to-codepoint
		int64_t l = stringView.size() - binaryPosition;
		if (l < 1) return -1;
		unsigned char u0 = stringView[binaryPosition + 0];
		if (u0 >= 0 && u0 <= 127) {
			addCacheEntry();
			binaryPosition++;
			characterPosition++;
			return u0;
		}
		if (l < 2) {
			addCacheEntry();
			binaryPosition++;
			characterPosition++;
			return -1;
		}
		unsigned char u1 = stringView[binaryPosition + 1];
		if (u0 >= 192 && u0 <= 223) {
			addCacheEntry();
			binaryPosition+= 2;
			characterPosition++;
			return (u0 - 192) * 64 + (u1 - 128);
		}
		if (u0 == 0xed && (u1 & 0xa0) == 0xa0) {
			addCacheEntry();
			binaryPosition+= 2;
			characterPosition++;
			return -1; // code points, 0xd800 to 0xdfff
		}
		if (l < 3) {
			addCacheEntry();
			binaryPosition+= 2;
			characterPosition++;
			return -1;
		}
		unsigned char u2 = stringView[binaryPosition + 2];
		if (u0 >= 224 && u0 <= 239) {
			addCacheEntry();
			binaryPosition+= 3;
			characterPosition++;
			return (u0 - 224) * 4096 + (u1 - 128) * 64 + (u2 - 128);
		}
		if (l < 4) {
			addCacheEntry();
			binaryPosition+= 3;
			characterPosition++;
			return -1;
		}
		unsigned char u3 = stringView[binaryPosition + 3];
		if (u0 >= 240 && u0 <= 247) {
			addCacheEntry();
			binaryPosition+= 4;
			characterPosition++;
			return (u0 - 240) * 262144 + (u1 - 128) * 4096 + (u2 - 128) * 64 + (u3 - 128);
		}
		//
		addCacheEntry();
		binaryPosition+= 4;
		characterPosition++;
		//
		return -1;
	}

private:
	const string_view stringView;
	mutable int64_t binaryPosition { 0 };
	mutable int64_t characterPosition { 0 };
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
				if (binaryPosition > 0 && (binaryPosition % UTF8PositionCache::CACHE_ENTRY_SIZE) == 0 && (_cache.empty() == true || _cache[_cache.size() - 1].binaryPosition < binaryPosition)) {
					_cache.emplace_back(
						binaryPosition,
						characterPosition
					);
					/*
					Console::printLine("UTF8CharacterIterator::addCacheEntry(): binary cache: binary: " + to_string(binaryPosition) + " / character: " + to_string(characterPosition));
					for (const auto& cacheEntry: _cache) {
						Console::printLine("\tbinary cache: binary: " + to_string(cacheEntry.binaryPosition) + " / character: " + to_string(cacheEntry.characterPosition));
					}
					*/
				}
			}
			// character cache
			{
				auto& _cache = cache->characterCache;
				if (characterPosition > 0 && (characterPosition % UTF8PositionCache::CACHE_ENTRY_SIZE) == 0 && (_cache.empty() == true || _cache[_cache.size() - 1].characterPosition < characterPosition)) {
					// Console::printLine("UTF8CharacterIterator::addCacheEntry(): character cache: binary: " + to_string(binaryPosition) + " / character: " + to_string(characterPosition));
					_cache.emplace_back(
						binaryPosition,
						characterPosition
					);
					/*
					for (const auto& cacheEntry: _cache) {
						Console::printLine("\tcharacter cache: binary: " + to_string(cacheEntry.binaryPosition) + " / character: " + to_string(cacheEntry.characterPosition));
					}
					*/
				}
			}
		}
	}

};
