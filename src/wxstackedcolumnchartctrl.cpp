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

#include "wxstackedcolumnchartctrl.h"
#include <wx/dcbuffer.h>

wxStackedColumnChartDataset::wxStackedColumnChartDataset(const wxColor &fillColor,
														 const wxColor &strokeColor,
														 const wxVector<wxDouble> &data)
	: m_fillColor(fillColor), m_strokeColor(strokeColor), m_data(data)
{
}

const wxColor& wxStackedColumnChartDataset::GetFillColor() const
{
	return m_fillColor;
}

const wxColor& wxStackedColumnChartDataset::GetStrokeColor() const
{
	return m_strokeColor;
}

const wxVector<wxDouble>& wxStackedColumnChartDataset::GetData() const
{
	return m_data;
}

wxStackedColumnChartData::wxStackedColumnChartData(const wxVector<wxString> &labels)
	: m_labels(labels)
{
}

void wxStackedColumnChartData::AddDataset(wxStackedColumnChartDataset::ptr dataset)
{
	m_datasets.push_back(dataset);
}

const wxVector<wxString>& wxStackedColumnChartData::GetLabels() const
{
	return m_labels;
}

const wxVector<wxStackedColumnChartDataset::ptr>& wxStackedColumnChartData::GetDatasets() const
{
	return m_datasets;
}

wxStackedColumnChartCtrl::Column::Column(wxDouble value,
										 wxDouble x,
										 wxDouble y,
										 const wxColor &fillColor,
										 const wxColor &strokeColor)
	: wxChartRectangle(x, y, wxChartRectangleOptions(fillColor, strokeColor)),
	m_value(value)
{
}

wxDouble wxStackedColumnChartCtrl::Column::GetValue() const
{
	return m_value;
}

wxStackedColumnChartCtrl::Dataset::Dataset()
{
}

const wxVector<wxStackedColumnChartCtrl::Column::ptr>& wxStackedColumnChartCtrl::Dataset::GetColumns() const
{
	return m_columns;
}

void wxStackedColumnChartCtrl::Dataset::AppendColumn(Column::ptr column)
{
	m_columns.push_back(column);
}

wxStackedColumnChartCtrl::wxStackedColumnChartCtrl(wxWindow *parent,
												   wxWindowID id,
												   const wxStackedColumnChartData &data,
												   const wxPoint &pos,
												   const wxSize &size,
												   long style)
	: wxChartCtrl(parent, id, pos, size, style), 
	m_grid(size, data.GetLabels(), GetCumulativeMinValue(data.GetDatasets()),
		GetCumulativeMaxValue(data.GetDatasets()), m_options.GetGridOptions())
{
	const wxVector<wxStackedColumnChartDataset::ptr>& datasets = data.GetDatasets();
	for (size_t i = 0; i < datasets.size(); ++i)
	{
		const wxStackedColumnChartDataset& dataset = *datasets[i];
		Dataset::ptr newDataset(new Dataset());

		const wxVector<wxDouble>& data = dataset.GetData();
		for (size_t j = 0; j < data.size(); ++j)
		{
			newDataset->AppendColumn(Column::ptr(new Column(data[j], 25, 50, dataset.GetFillColor(), dataset.GetStrokeColor())));
		}

		m_datasets.push_back(newDataset);
	}
}

const wxStackedColumnChartOptions& wxStackedColumnChartCtrl::GetOptions() const
{
	return m_options;
}

wxDouble wxStackedColumnChartCtrl::GetCumulativeMinValue(const wxVector<wxStackedColumnChartDataset::ptr>& datasets)
{
	wxDouble result = 0;
	
	size_t i = 0;
	while (true)
	{
		wxDouble sum = 0;
		bool stop = true;
		for (size_t j = 0; j < datasets.size(); ++j)
		{
			const wxStackedColumnChartDataset& dataset = *datasets[j];
			if (i < dataset.GetData().size())
			{
				sum += dataset.GetData()[i];
				stop = false;
			}
		}
		if (sum < result)
		{
			result = sum;
		}
		if (stop)
		{
			break;
		}
		++i;
	}

	return result;
}

wxDouble wxStackedColumnChartCtrl::GetCumulativeMaxValue(const wxVector<wxStackedColumnChartDataset::ptr>& datasets)
{
	wxDouble result = 0;
	
	size_t i = 0;
	while (true)
	{
		wxDouble sum = 0;
		bool stop = true;
		for (size_t j = 0; j < datasets.size(); ++j)
		{
			const wxStackedColumnChartDataset& dataset = *datasets[j];
			if (i < dataset.GetData().size())
			{
				sum += dataset.GetData()[i];
				stop = false;
			}
		}
		if (sum > result)
		{
			result = sum;
		}
		if (stop)
		{
			break;
		}
		++i;
	}

	return result;
}

void wxStackedColumnChartCtrl::Resize(const wxSize &size)
{
	m_grid.Resize(size);
}

wxSharedPtr<wxVector<const wxChartElement*> > wxStackedColumnChartCtrl::GetActiveElements(const wxPoint &point)
{
	wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
	return activeElements;
}

void wxStackedColumnChartCtrl::OnPaint(wxPaintEvent &evt)
{
	wxAutoBufferedPaintDC dc(this);

	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		m_grid.Draw(*gc);

		wxVector<wxDouble> heightOfPreviousDatasets;
		for (size_t i = 0; i < m_datasets[0]->GetColumns().size(); ++i)
		{
			heightOfPreviousDatasets.push_back(0);
		}

		for (size_t i = 0; i < m_datasets.size(); ++i)
		{
			Dataset& currentDataset = *m_datasets[i];
			for (size_t j = 0; j < currentDataset.GetColumns().size(); ++j)
			{
				Column& column = *(currentDataset.GetColumns()[j]);

				wxPoint2DDouble upperLeftCornerPosition = m_grid.GetMapping().GetWindowPosition(j, column.GetValue());
				upperLeftCornerPosition.m_x += m_options.GetColumnSpacing();
				upperLeftCornerPosition.m_y -= heightOfPreviousDatasets[j];
				wxPoint2DDouble upperRightCornerPosition = m_grid.GetMapping().GetWindowPosition(j + 1, column.GetValue());
				upperRightCornerPosition.m_x -= m_options.GetColumnSpacing();
				upperRightCornerPosition.m_y -= heightOfPreviousDatasets[j];

				column.SetPosition(upperLeftCornerPosition);
				column.SetSize(upperRightCornerPosition.m_x - upperLeftCornerPosition.m_x,
					(m_grid.GetMapping().GetEndPoint() - heightOfPreviousDatasets[j]) - upperLeftCornerPosition.m_y);

				heightOfPreviousDatasets[j] = m_grid.GetMapping().GetEndPoint() - upperLeftCornerPosition.m_y;
			}
		}

		for (size_t i = 0; i < m_datasets.size(); ++i)
		{
			Dataset& currentDataset = *m_datasets[i];
			for (size_t j = 0; j < currentDataset.GetColumns().size(); ++j)
			{
				currentDataset.GetColumns()[j]->Draw(*gc);
			}
		}

		DrawTooltips(*gc);

		delete gc;
	}
}

BEGIN_EVENT_TABLE(wxStackedColumnChartCtrl, wxChartCtrl)
	EVT_PAINT(wxStackedColumnChartCtrl::OnPaint)
END_EVENT_TABLE()