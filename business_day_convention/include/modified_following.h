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

#include <calendar.h>
#include <business_day_adjusters.h>


namespace fin_calendar
{

	class modified_following final
	{

	public:

		auto adjust(
			const std::chrono::year_month_day& ymd,
			const gregorian::calendar& cal
		) const -> std::chrono::year_month_day;

		auto adjust(
			const std::chrono::sys_days& sd,
			const gregorian::calendar& cal
		) const -> std::chrono::sys_days;

	};



	inline auto modified_following::adjust(
		const std::chrono::year_month_day& ymd,
		const gregorian::calendar& cal
	) const -> std::chrono::year_month_day
	{
		auto result = ymd;
		while (!cal.is_business_day(result))
		{
			if (result.day() == (ymd.year() / ymd.month() / std::chrono::last).day())
			{
				// don't want to move to a different month
				return gregorian::Preceding.adjust(ymd, cal);
			}

			result = std::chrono::sys_days{ result } + std::chrono::days{ 1 };
		}
		return result;
	}

	inline auto modified_following::adjust(
		const std::chrono::sys_days& sd,
		const gregorian::calendar& cal
	) const -> std::chrono::sys_days
	{
		return std::chrono::sys_days{ adjust(std::chrono::year_month_day{ sd }, cal) };
	}

}
