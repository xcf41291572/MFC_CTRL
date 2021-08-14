// XButton.cpp: 实现文件
//

#include "pch.h"
#include "XButton/XButton.h"
XButton::XButton()
{
	x_ButtonState = NORMAL;
	ZeroMemory(x_BitmapContainer, 4 * sizeof(XBITMAP));
}

XButton::~XButton()
{
	
}
void XButton::CreateButton(CWnd* p_parent, UINT nid, const RECT& rect)
{
	Create(NULL, WS_CHILD | WS_VISIBLE|BS_OWNERDRAW, rect, p_parent, nid);
}
//加载位图
void XButton::LoadBitmaps(UINT bitmap_id_state_N, UINT bitmap_id_state_P, UINT bitmap_id_state_D , UINT bitmap_id_state_H)
{
	x_BitmapContainer[0].bitmap.LoadBitmap(bitmap_id_state_N);
	::GetObject(x_BitmapContainer[0].bitmap.m_hObject, sizeof(BITMAP), &(x_BitmapContainer[0].bitmap_info));

	x_BitmapContainer[1].bitmap.LoadBitmap(bitmap_id_state_P);
	::GetObject(x_BitmapContainer[1].bitmap.m_hObject, sizeof(BITMAP), &(x_BitmapContainer[1].bitmap_info));

	if (bitmap_id_state_D)
	{
		x_BitmapContainer[2].bitmap.LoadBitmap(bitmap_id_state_D);
		::GetObject(x_BitmapContainer[2].bitmap.m_hObject, sizeof(BITMAP), &(x_BitmapContainer[2].bitmap_info));
	}
	if (bitmap_id_state_H)
	{
		x_BitmapContainer[3].bitmap.LoadBitmap(bitmap_id_state_H);
		::GetObject(x_BitmapContainer[3].bitmap.m_hObject, sizeof(BITMAP), &(x_BitmapContainer[3].bitmap_info));
	}

}

BEGIN_MESSAGE_MAP(XButton, CButton)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_ENABLE()
END_MESSAGE_MAP()

void XButton::OnPaint()
{
	CPaintDC dc(this); 
	CDC mem_dc;
	mem_dc.CreateCompatibleDC(&dc);

	CRect client_rect;
	GetClientRect(client_rect);

	switch (x_ButtonState)
	{
	case PRESSED:
	{
		if (x_BitmapContainer[1].bitmap.m_hObject != nullptr)
		{
			mem_dc.SelectObject(x_BitmapContainer[1].bitmap.m_hObject);

			dc.StretchBlt(0, 0, client_rect.Width(), client_rect.Height(),
				&mem_dc,
				0, 0, x_BitmapContainer[1].bitmap_info.bmWidth, x_BitmapContainer[1].bitmap_info.bmHeight,
				SRCCOPY);

		}

	}
	break;
	case DISABLED:
	{
		if (x_BitmapContainer[2].bitmap.m_hObject != nullptr)
		{
			mem_dc.SelectObject(x_BitmapContainer[2].bitmap.m_hObject);

			dc.StretchBlt(0, 0, client_rect.Width(), client_rect.Height(),
				&mem_dc,
				0, 0, x_BitmapContainer[2].bitmap_info.bmWidth, x_BitmapContainer[2].bitmap_info.bmHeight,
				SRCCOPY);

		}
		else
		{
			if (x_BitmapContainer[0].bitmap.m_hObject != nullptr)
			{
				mem_dc.SelectObject(x_BitmapContainer[0].bitmap.m_hObject);

				dc.StretchBlt(0, 0, client_rect.Width(), client_rect.Height(),
					&mem_dc,
					0, 0, x_BitmapContainer[0].bitmap_info.bmWidth, x_BitmapContainer[0].bitmap_info.bmHeight,
					SRCCOPY);

			}
		}

	}
	break;
	case HOVER:
	{
		if (x_BitmapContainer[3].bitmap.m_hObject != nullptr)
		{
			mem_dc.SelectObject(x_BitmapContainer[3].bitmap.m_hObject);

			dc.StretchBlt(0, 0, client_rect.Width(), client_rect.Height(),
				&mem_dc,
				0, 0, x_BitmapContainer[3].bitmap_info.bmWidth, x_BitmapContainer[3].bitmap_info.bmHeight,
				SRCCOPY);

		}
		else
		{
			if (x_BitmapContainer[0].bitmap.m_hObject != nullptr)
			{
				mem_dc.SelectObject(x_BitmapContainer[0].bitmap.m_hObject);

				dc.StretchBlt(0, 0, client_rect.Width(), client_rect.Height(),
					&mem_dc,
					0, 0, x_BitmapContainer[0].bitmap_info.bmWidth, x_BitmapContainer[0].bitmap_info.bmHeight,
					SRCCOPY);

			}
		}
	}
	break;
	default:
	{
		if (x_BitmapContainer[0].bitmap.m_hObject != nullptr)
		{
			mem_dc.SelectObject(x_BitmapContainer[0].bitmap.m_hObject);

			dc.StretchBlt(0, 0, client_rect.Width(), client_rect.Height(),
				&mem_dc,
				0, 0, x_BitmapContainer[0].bitmap_info.bmWidth, x_BitmapContainer[0].bitmap_info.bmHeight,
				SRCCOPY);

		}
	}
	}

}
void XButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	x_ButtonState = PRESSED;
	Invalidate();
	CButton::OnLButtonDown(nFlags, point);
}

void XButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	ReleaseCapture();

	CRect client_rect;
	GetClientRect(client_rect);

	if (client_rect.PtInRect(point))
	{
		x_ButtonState = HOVER;
		WPARAM value = ((WPARAM)BN_CLICKED << 16) | (GetDlgCtrlID());
		::PostMessage(GetParent()->GetSafeHwnd(), WM_COMMAND, value, (LPARAM)GetSafeHwnd());
	}
	else
	{

		x_ButtonState = NORMAL;

	}

	CButton::OnLButtonUp(nFlags, point);

}


void XButton::OnMouseHover(UINT nFlags, CPoint point)
{
	if (nFlags&MK_LBUTTON)
		x_ButtonState = PRESSED;
	else
		x_ButtonState = HOVER;

	Invalidate();

	CButton::OnMouseHover(nFlags, point);
}


void XButton::OnMouseLeave()
{
	if (x_ButtonState == HOVER)
		x_ButtonState = NORMAL;

	Invalidate();

	CButton::OnMouseLeave();
}


void XButton::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER|TME_LEAVE;
	tme.dwHoverTime = 100;
	tme.hwndTrack = m_hWnd;

	//当鼠标指针离开窗口或将鼠标悬停在指定时间范围内时，发布消息。
	TrackMouseEvent(&tme);

	CButton::OnMouseMove(nFlags, point);
}


void XButton::OnEnable(BOOL bEnable)
{
	CButton::OnEnable(bEnable);

	if (bEnable)
	{
		x_ButtonState = NORMAL;
	}
	else
	{
		x_ButtonState = DISABLED;
	}

}


void XButton::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

}
