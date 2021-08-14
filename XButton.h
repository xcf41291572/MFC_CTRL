#pragma once
class XButton : public CButton
{

public:

	struct XBITMAP
{
	CBitmap  bitmap;
	BITMAP   bitmap_info;

};

	enum BUTTONSTATE
	{
		NORMAL,
		PRESSED,
		HOVER,
		DISABLED,

	};

private:
	XBITMAP				x_BitmapContainer[4];		//λͼ����
	XBITMAP             x_CheckedBitmap;
	BUTTONSTATE			x_ButtonState;				//��ť״̬
	BOOL                x_CanBeChecked;
	BOOL                x_CheckState;
public:
	XButton();
	virtual ~XButton();
protected:
	DECLARE_MESSAGE_MAP()

public:
	//������ť
	void CreateButton(CWnd* p_parent,UINT nid, const RECT& rect);
	//����λͼ
	void LoadBitmaps(UINT bitmap_id_state_N, UINT bitmap_id_state_P, UINT bitmap_id_state_D=0, UINT bitmap_id_state_H=0);

private:

	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEnable(BOOL bEnable);

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


