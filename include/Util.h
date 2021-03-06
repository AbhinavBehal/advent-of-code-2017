#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <array>
#include <numeric>
#include <sstream>
#include <functional>
#include <string>
#include <cctype>

namespace util
{
	std::string knotHash(const std::string &str)
	{
		int iter = 64;
		std::vector<int> lengths;
		for (char c : str)
			lengths.push_back(c);
		lengths.insert(lengths.end(), {17, 31, 73, 47, 23});
		std::array<int, 256> list;
		std::iota(list.begin(), list.end(), 0);
		int pos = 0;
		int skip = 0;
		while (iter--) {
			for (int len : lengths) {
				std::vector<int> slice(len);
				for (int i = 0; i < len; ++i)
					slice[i] = list[(pos + i) % 256];
				std::reverse(slice.begin(), slice.end());
				for (int i = 0; i < len; ++i)
					list[(pos + i) % 256] = slice[i];
				pos += len + skip;
				++skip;
			}
		}
		std::ostringstream ss;
		for (auto it = list.begin(); it != list.end(); std::advance(it, 16)) {
			auto val = std::accumulate(it, std::next(it, 16), 0, std::bit_xor<int>());
			ss << std::setw(2) << std::setfill('0') << std::hex << val;
		}
		return ss.str();
	}

	bool isNumber(const std::string &str)
	{
		return (std::isdigit(str[0]) || str[0] == '-' || str[0] == '+') &&
				str.substr(1).find_first_not_of("0123456789") == std::string::npos;
	}

	bool isPrime(std::int64_t n) {
		if (n < 2) return false;
		if (n == 2) return true;
		if (n % 2 == 0) return false;
		for (std::int64_t i = 3; i * i <= n; i += 2) {
			if (n % i == 0)
				return false;
		}
		return true;
	}

	template <typename T>
	T read(std::istream &is, const std::string &fmt)
	{
		T out;
		std::string line;
		std::getline(is, line);
		std::sscanf(line.c_str(), fmt.c_str(), &out);
		return out;
	}
}

#endif
