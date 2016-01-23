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

#include "wxchartlabel.h"

wxChartLabel::wxChartLabel(const wxString &text)
	: m_text(text), m_position(0, 0), m_size(0, 0)
{
}

wxChartLabel::wxChartLabel(const wxString &text,
						   wxDouble width,
						   wxDouble height)
	: m_text(text), m_position(0, 0), 
	m_size(width, height)
{
}

bool wxChartLabel::HitTest(const wxPoint &point) const
{
	return false;
}

void wxChartLabel::Draw(wxGraphicsContext &gc) const
{
	gc.DrawText(m_text, m_position.m_x, m_position.m_y);
}

const wxString& wxChartLabel::GetText() const
{
	return m_text;
}

const wxPoint2DDouble& wxChartLabel::GetPosition() const
{
	return m_position;
}

void wxChartLabel::SetPosition(wxDouble x,
							   wxDouble y)
{
	m_position.m_x = x;
	m_position.m_y = y;
}

const wxSize& wxChartLabel::GetSize() const
{
	return m_size;
}

void wxChartLabel::SetSize(const wxSize &size)
{
	m_size = size;
}

void wxChartLabel::SetSize(wxDouble width, wxDouble height)
{
	m_size.x = width;
	m_size.y = height;
}