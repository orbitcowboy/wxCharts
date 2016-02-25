/*
	Copyright (c) 2016 Xavier Leclercq

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
	IN THE SOFTWARE.
*/

/*
	Part of this file were copied from the Chart.js project (http://chartjs.org/)
	and translated into C++.

	The files of the Chart.js project have the following copyright and license.

	Copyright (c) 2013-2016 Nick Downie
	Released under the MIT license
	https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

#include "wxchartgridmapping.h"

wxChartGridMapping::wxChartGridMapping(const wxSize &size,
									   const wxChartAxis::ptr xAxis,
									   const wxChartAxis::ptr yAxis)
	: m_size(size), 
    m_minXValue(0), m_maxXValue(1), m_minYValue(0), m_maxYValue(1),
	m_XAxis(xAxis), m_YAxis(yAxis)
{
}

const wxSize& wxChartGridMapping::GetSize() const
{
	return m_size;
}

void wxChartGridMapping::SetSize(const wxSize &size)
{
	m_size = size;
}

wxDouble wxChartGridMapping::GetMinXValue() const
{
    return m_minXValue;
}

void wxChartGridMapping::SetMinXValue(wxDouble minValue)
{
    m_minXValue = minValue;
}

wxDouble wxChartGridMapping::GetMaxXValue() const
{
    return m_maxXValue;
}

void wxChartGridMapping::SetMaxXValue(wxDouble maxValue)
{
    m_maxXValue = maxValue;
}

wxDouble wxChartGridMapping::GetMinYValue() const
{
	return m_minYValue;
}

void wxChartGridMapping::SetMinYValue(wxDouble minValue)
{
	m_minYValue = minValue;
}

wxDouble wxChartGridMapping::GetMaxYValue() const
{
	return m_maxYValue;
}

void wxChartGridMapping::SetMaxYValue(wxDouble maxValue)
{
	m_maxYValue = maxValue;
}

wxPoint2DDouble wxChartGridMapping::GetWindowPosition(wxDouble x, 
                                                      wxDouble y) const
{
    if ((m_XAxis->GetOptions().GetPosition() == wxCHARTAXISPOSITION_BOTTOM) &&
        (m_YAxis->GetOptions().GetPosition() == wxCHARTAXISPOSITION_LEFT))
    {
        return wxPoint2DDouble(
            m_XAxis->GetPosition((x - m_minXValue) / (m_maxXValue - m_minXValue)).m_x,
            m_YAxis->GetPosition((y - m_minYValue) / (m_maxYValue - m_minYValue)).m_y
            );
    }
    else if ((m_XAxis->GetOptions().GetPosition() == wxCHARTAXISPOSITION_LEFT) &&
        (m_YAxis->GetOptions().GetPosition() == wxCHARTAXISPOSITION_BOTTOM))
    {
        return wxPoint2DDouble(
            m_YAxis->GetPosition((y - m_minYValue) / (m_maxYValue - m_minYValue)).m_x,
            m_XAxis->GetPosition((x - m_minXValue) / (m_maxXValue - m_minXValue)).m_y
            );
    }

    wxTrap();
    return wxPoint2DDouble(0, 0);
}

wxPoint2DDouble wxChartGridMapping::GetWindowPositionAtTickMark(size_t index,
                                                                wxDouble value) const
{
	if ((m_XAxis->GetOptions().GetPosition() == wxCHARTAXISPOSITION_BOTTOM) &&
		(m_YAxis->GetOptions().GetPosition() == wxCHARTAXISPOSITION_LEFT))
	{
		return wxPoint2DDouble(
			m_XAxis->GetTickMarkPosition(index).m_x,
			m_YAxis->GetPosition((value - m_minYValue) / (m_maxYValue - m_minYValue)).m_y
			);
	}
	else if ((m_XAxis->GetOptions().GetPosition() == wxCHARTAXISPOSITION_LEFT) &&
		(m_YAxis->GetOptions().GetPosition() == wxCHARTAXISPOSITION_BOTTOM))
	{
		return wxPoint2DDouble(
			m_YAxis->GetPosition((value - m_minYValue) / (m_maxYValue - m_minYValue)).m_x,
			m_XAxis->GetTickMarkPosition(index).m_y
			);
	}

	wxTrap();
	return wxPoint2DDouble(0, 0);
}

const wxChartAxis& wxChartGridMapping::GetXAxis() const
{
	return *m_XAxis;
}
