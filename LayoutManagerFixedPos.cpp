#include "pch.h"
#include "LayoutManagerFixedPos.h"


void CLayoutManagerFixedPos::Init(CWnd* pParentDlg)
{
    m_controls.clear();
    pParentDlg->GetClientRect(&m_originalClientRect);

    HWND hWndChild = ::GetWindow(pParentDlg->GetSafeHwnd(), GW_CHILD);
    while (hWndChild) {
        CWnd* pChild = CWnd::FromHandle(hWndChild);
        //if (pChild && ::IsWindowVisible(hWndChild)) 
        {
            CRect rect;
            pChild->GetWindowRect(&rect);
            pParentDlg->ScreenToClient(&rect);
            cout<< rect <<endl;
            ControlInfo info;
            info.pWnd = pChild;
            info.initRect = rect;
            info.xRatio = (double)rect.left / m_originalClientRect.Width();
            info.yRatio = (double)rect.top / m_originalClientRect.Height();
            info.wRatio = (double)rect.Width() / m_originalClientRect.Width();
            info.hRatio = (double)rect.Height() / m_originalClientRect.Height();
            info.xMargin = (int)(m_originalClientRect.Width() - (rect.left+ rect.Width()));
            info.yMargin = (int)(m_originalClientRect.Height() - (rect.top + rect.Height()));

            m_controls.push_back(info);
        }

        hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT);
    }
}

void CLayoutManagerFixedPos::AddControl(CWnd* pParentDlg, UINT controlID) {
    if (m_controls.empty()) {
        pParentDlg->GetClientRect(&m_originalClientRect);
    }

    CWnd* pWnd = pParentDlg->GetDlgItem(controlID);
    if (!pWnd || !::IsWindow(pWnd->GetSafeHwnd())) return;

    CRect rect;
    pWnd->GetWindowRect(&rect);
    pParentDlg->ScreenToClient(&rect);

    ControlInfo info;
    info.pWnd = pWnd;
    info.initRect = rect;
    info.xRatio = (double)rect.left / m_originalClientRect.Width();
    info.yRatio = (double)rect.top / m_originalClientRect.Height();
    info.wRatio = (double)rect.Width() / m_originalClientRect.Width();
    info.hRatio = (double)rect.Height() / m_originalClientRect.Height();
    info.xMargin = (int)(m_originalClientRect.Width() - (rect.left + rect.Width()));
    info.yMargin = (int)(m_originalClientRect.Height() - (rect.top + rect.Height()));

    m_controls.push_back(info);
}

void CLayoutManagerFixedPos::UpdateLayout(int newWidth, int newHeight)
{
    for (auto& info : m_controls) {
        if (!info.pWnd || !::IsWindow(info.pWnd->GetSafeHwnd()))
            continue;

        // 위치는 고정 (초기 위치 유지)
        int left = info.initRect.left;
        int top = info.initRect.top;

        // 크기만 비율로 조정
        int width = (int)(newWidth - left - info.xMargin);
        int height = (int)(newHeight - top - info.yMargin);

        info.pWnd->MoveWindow(left, top, width, height, TRUE);
    }
}

void CLayoutManagerFixedPos::UpdateLayoutHeightOnly(int newHeight)
{
    for (auto& info : m_controls) {
        if (!info.pWnd || !::IsWindow(info.pWnd->GetSafeHwnd()))
            continue;

        int left = info.initRect.left;
        int top = info.initRect.top;
        int height = (int)(newHeight - top - info.yMargin);
        int width = info.initRect.Width();

        info.pWnd->MoveWindow(left, top, width, height, TRUE);
    }
}