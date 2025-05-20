#include "pch.h"
#include "LayoutManager.h"


void CLayoutManager::Init(CWnd* pParentDlg) 
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

void CLayoutManager::AddControl(CWnd* pParentDlg, UINT controlID) {
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

void CLayoutManager::UpdateLayout(int newWidth, int newHeight) 
{
    for (auto& info : m_controls) {
        if (!info.pWnd || !::IsWindow(info.pWnd->GetSafeHwnd()))
            continue;

        int left = (int)(newWidth * info.xRatio);
        int top = (int)(newHeight * info.yRatio);
        int width = (int)(newWidth * info.wRatio);
        int height = (int)(newHeight * info.hRatio);

        info.pWnd->MoveWindow(left, top, width, height, TRUE);
    }
}


void CLayoutManager::UpdateLayoutHeightOnly(int newHeight)
{
    for (auto& info : m_controls) {
        if (!info.pWnd || !::IsWindow(info.pWnd->GetSafeHwnd()))
            continue;

        CRect currentRect;
        info.pWnd->GetWindowRect(&currentRect);
        info.pWnd->GetParent()->ScreenToClient(&currentRect);

        int top = (int)(newHeight * info.yRatio);
        int height = (int)(newHeight * info.hRatio);
        int left = currentRect.left;
        int width = currentRect.Width();

        info.pWnd->MoveWindow(left, top, width, height, TRUE);
    }
}

void CLayoutManager::UpdateLayoutWidthOnly(int newWidth)
{
    for (auto& info : m_controls) {
        if (!info.pWnd || !::IsWindow(info.pWnd->GetSafeHwnd()))
            continue;

        CRect currentRect;
        info.pWnd->GetWindowRect(&currentRect);
        info.pWnd->GetParent()->ScreenToClient(&currentRect);

        int left = (int)(newWidth * info.xRatio);
        int width = (int)(newWidth * info.wRatio);
        int top = currentRect.top;
        int height = currentRect.Height();

        info.pWnd->MoveWindow(left, top, width, height, TRUE);
    }
}
