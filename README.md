# MFC-Dialog-Control-Resizer
MFC layout manager for auto-resizing all or selected controls dynamically as the dialog window is resized.

# MFC Dialog Control Auto-Resizing

This project demonstrates how to automatically resize and reposition controls in an MFC dialog when the window is resized.

## ✨ Features

- Automatically resizes **all** child controls based on the dialog's new size.
- Alternatively supports **resizing specific controls only**, while keeping their positions fixed.
- Simple and reusable layout manager class 1
  * `CLayoutManager`: Adjusts both size and position of all controls.

![녹화_2025_05_20_15_01_31_395](https://github.com/user-attachments/assets/807d4f0c-428e-44fa-a74b-9af8ebccd505)

- Simple and reusable layout manager class 2
  * `CLayoutManagerFixedPos`: Resizes specific controls without changing their position.
    
![녹화_2025_05_20_15_00_44_382](https://github.com/user-attachments/assets/982c32c0-0b83-490a-a309-89271193a08e)


## 📁 File Structure
/src

├── LayoutManager.h / .cpp

├── LayoutManagerFixedPos.h / .cpp

└── testMFCDlg.* # Sample usage in dialog-based application


## 🚀 How to Use

### 1. Enable dialog resizing

Set the **Border** property of your dialog to `Resizing`.

### 2. Add `CLayoutManager` (for all controls)

In your dialog class:

```cpp
#include "LayoutManager.h"
CLayoutManager m_layoutManager;
```

In ```OnInitDialog()```:

```cpp
m_layoutManager.Init(this);
```

In ```OnSize()```:

```cpp
void CYourDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
    if (cx > 0 && cy > 0) {
        m_layoutManager.UpdateLayout(cx, cy);
    }
}
```


## 🛠 Dependencies

- Microsoft Foundation Classes (MFC)
- Visual Studio with MFC support

## 📄 License

This project is open source under the MIT License.
