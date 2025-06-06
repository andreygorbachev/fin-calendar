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


namespace fin_calendar
{

	template<typename T = double>
	class actual_365_L final // actually in ISDA 2021 it is only defined as Act/365L
	{

	public:

		auto fraction(
			const std::chrono::year_month_day& start,
			const std::chrono::year_month_day& end
		) const noexcept -> T;

	};


	template<typename T>
	auto actual_365_L<T>::fraction(
		const std::chrono::year_month_day& start,
		const std::chrono::year_month_day& end
	) const noexcept -> T
	{
		const auto start_date = std::chrono::sys_days{ start };
		const auto end_date = std::chrono::sys_days{ end };
		const auto days_between = static_cast<T>((end_date - start_date).count());

		if(end.year().is_leap())
			return days_between / 366;
		else
			return days_between / 365;
	}

}
