#pragma once
// edit from https://github.com/DarthTon/Blackbone/blob/master/src/BlackBone/Patterns

#define REBASE(pRVA, baseOld, baseNew)       ((ptr_t)pRVA - (ptr_t)baseOld + (ptr_t)baseNew)



#include <string>
#include <vector>
#include <initializer_list>
using ptr_t = uint64_t;


	class PatternSearch
	{
	public:
		 PatternSearch(const std::vector<uint8_t>& pattern);
		 PatternSearch(const std::initializer_list<uint8_t>&& pattern);
		 PatternSearch(const std::string& pattern);
		 PatternSearch(const char* pattern, size_t len = 0);
		 PatternSearch(const uint8_t* pattern, size_t len = 0);

		 ~PatternSearch() = default;

		/// <summary>
		/// Default pattern matching with wildcards.
		/// std::search is approximately 2x faster than naive approach.
		/// </summary>
		/// <param name="wildcard">Pattern wildcard</param>
		/// <param name="scanStart">Starting address</param>
		/// <param name="scanSize">Size of region to scan</param>
		/// <param name="out">Found results</param>
		/// <param name="value_offset">Value that will be added to resulting addresses</param>
		/// <returns>Number of found addresses</returns>
		 size_t Search(
			uint8_t wildcard,
			void* scanStart,
			size_t scanSize,
			std::vector<ptr_t>& out,
			ptr_t value_offset = 0
		) const;

		/// <summary>
		/// Full pattern match, no wildcards.
		/// Uses Boyer�Moore�Horspool algorithm.
		/// </summary>
		/// <param name="scanStart">Starting address</param>
		/// <param name="scanSize">Size of region to scan</param>
		/// <param name="out">Found results</param>
		/// <param name="value_offset">Value that will be added to resulting addresses</param>
		/// <returns>Number of found addresses</returns>
		 size_t Search(
			void* scanStart,
			size_t scanSize,
			std::vector<ptr_t>& out,
			ptr_t value_offset = 0
		) const;
	private:
		std::vector<uint8_t> _pattern;      // Pattern to search
	};

