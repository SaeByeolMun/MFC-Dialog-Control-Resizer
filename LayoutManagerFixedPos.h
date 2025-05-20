#pragma once

class CLayoutManagerFixedPos
{
public:
    struct ControlInfo {
        CWnd* pWnd;
        CRect initRect;
        double xRatio, yRatio, wRatio, hRatio;
        int xMargin, yMargin;
    };

    void Init(CWnd* pParentDlg);
    void AddControl(CWnd* pParentDlg, UINT controlID);

    void UpdateLayout(int newWidth, int newHeight);
    void UpdateLayoutHeightOnly(int newHeight);
private:
    std::vector<ControlInfo> m_controls;
    CRect m_originalClientRect;
};

