// The MIT License (MIT)
//
// Copyright (c) 2025 Andrey Gorbachev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <chrono>
#include <utility>


namespace fin_calendar
{

	template<typename T = double>
	class thirty_E_360_ISDA final
	{

	public:

		explicit thirty_E_360_ISDA(std::chrono::year_month_day termination);

	public:

		auto fraction(
			const std::chrono::year_month_day& start,
			const std::chrono::year_month_day& end
		) const noexcept -> T;

	private:

		std::chrono::year_month_day termination_;

	};


	template<typename T>
	thirty_E_360_ISDA<T>::thirty_E_360_ISDA(std::chrono::year_month_day termination) :
		termination_{ std::move(termination) }
	{
	}


	template<typename T>
	auto thirty_E_360_ISDA<T>::fraction(
		const std::chrono::year_month_day& start,
		const std::chrono::year_month_day& end
	) const noexcept -> T
	{
		const auto start_year = start.year();
		const auto start_month = start.month();
		auto start_day = start.day();
		const auto end_year = end.year();
		const auto end_month = end.month();
		auto end_day = end.day();

		if (start_day == std::chrono::day{ 31 } ||
			start == start.year() / std::chrono::February / std::chrono::last
		)
			start_day = std::chrono::day{ 30 };
		if (end_day == std::chrono::day{ 31 }  ||
			(end == end.year() / std::chrono::February / std::chrono::last && end != termination_)
		)
			end_day = std::chrono::day{ 30 };

		const auto days_between = static_cast<T>(
			(static_cast<int>(end_year) - static_cast<int>(start_year)) * 360 +
			(static_cast<unsigned>(end_month) - static_cast<unsigned>(start_month)) * 30 +
			(static_cast<unsigned>(end_day) - static_cast<unsigned>(start_day))
		);

		return days_between / 360;
	}

}
