/*
    Copyright (c) 2019 Xavier Leclercq

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

/// @file

#ifndef _WX_CHARTS_WXLINECHARTDATASETOPTIONS_H_
#define _WX_CHARTS_WXLINECHARTDATASETOPTIONS_H_

#include "wxchartspenoptions.h"
#include "wxchartsbrushoptions.h"

class wxLineChartDatasetOptions
{
public:
    wxLineChartDatasetOptions(const wxColor &dotColor, const wxColor &dotStrokeColor);

public:
    /// Whether to show the points on the chart.
    /// @retval true Show the points.
    /// @retval false Don't show the points.
    bool ShowDots() const;

    /// Gets the options for the pen used to draw the dots representing points on the chart.
    /**
        @return The options for the pen used to draw the dots representing points on the chart.
    */
    const wxChartsPenOptions& GetDotPenOptions() const;
    const wxColor& GetDotColor() const;

    /// Gets the radius for the dots representing
    /// points on the chart.
    /// @return The radius of the dots.
    wxDouble GetDotRadius() const;
    /// Gets the width of the pen used to
    /// draw the lines connecting the points
    /// of the chart. Width of the axes and grid
    /// lines are part of the options returned
    /// by the GetGridOptions() function.
    /// @return The width of the pen.
    unsigned int GetLineWidth() const;

private:
    bool m_showDots;
    wxChartsPenOptions m_dotPenOptions;
    wxColor m_dotColor;
    wxDouble m_dotRadius;
    unsigned int m_lineWidth;
};

#endif
