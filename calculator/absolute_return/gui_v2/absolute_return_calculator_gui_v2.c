#include <windows.h>
#include <stdio.h>

// Global handles
HWND hPortfolioOld, hPortfolioNew, hSpxOld, hSpxNew, hIxicOld, hIxicNew, hDjiOld, hDjiNew, hResultText;
double portfolioReturn = 0, spxReturn = 0, ixicReturn = 0, djiReturn = 0;

// Function to get user input from text boxes
double getInputValue(HWND hEdit) {
    char buffer[50];
    GetWindowText(hEdit, buffer, 50);
    return atof(buffer);
}

// Function to calculate percentage return
double calculateReturn(double oldValue, double newValue) {
    return ((newValue - oldValue) / oldValue) * 100;
}

// Function to draw a simple candle chart
void drawCandleChart(HDC hdc, RECT rect) {
    int barWidth = 60;
    int startX = 50;
    int maxBarHeight = 150;  // Maximum height for the largest return percentage
    
    // Normalize the returns for visualization
    double maxReturn = max(max(portfolioReturn, ixicReturn), max(spxReturn, djiReturn));
    
    // Draw portfolio return
    int portfolioHeight = (int)((portfolioReturn / maxReturn) * maxBarHeight);
    Rectangle(hdc, startX, rect.bottom - portfolioHeight, startX + barWidth, rect.bottom);
    SetTextColor(hdc, RGB(0, 0, 0));
    TextOut(hdc, startX, rect.bottom - portfolioHeight - 20, "Portfolio", 9);

    // Draw SPX return
    int spxHeight = (int)((spxReturn / maxReturn) * maxBarHeight);
    Rectangle(hdc, startX + 80, rect.bottom - spxHeight, startX + 80 + barWidth, rect.bottom);
    SetTextColor(hdc, RGB(0, 0, 0));
    TextOut(hdc, startX + 80, rect.bottom - spxHeight - 20, "SPX", 3);
	
	// Draw IXIC return
    int ixicHeight = (int)((ixicReturn / maxReturn) * maxBarHeight);
    Rectangle(hdc, startX + 160, rect.bottom - ixicHeight, startX + 160 + barWidth, rect.bottom);
    SetTextColor(hdc, RGB(0, 0, 0));
    TextOut(hdc, startX + 160, rect.bottom - ixicHeight - 20, "IXIC", 4);

    // Draw DJI return
    int djiHeight = (int)((djiReturn / maxReturn) * maxBarHeight);
    Rectangle(hdc, startX + 240, rect.bottom - djiHeight, startX + 240 + barWidth, rect.bottom);
    SetTextColor(hdc, RGB(0, 0, 0));
    TextOut(hdc, startX + 240, rect.bottom - djiHeight - 20, "DJI", 3);
}

// Window procedure for handling events
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch (msg) {
        case WM_CREATE:
            CreateWindowW(L"static", L"Portfolio Old Value:", WS_VISIBLE | WS_CHILD, 20, 20, 200, 20, hwnd, NULL, NULL, NULL);
            hPortfolioOld = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 20, 200, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindowW(L"static", L"Portfolio New Value:", WS_VISIBLE | WS_CHILD, 20, 50, 200, 20, hwnd, NULL, NULL, NULL);
            hPortfolioNew = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 50, 200, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindowW(L"static", L"SPX Old Value:", WS_VISIBLE | WS_CHILD, 20, 80, 200, 20, hwnd, NULL, NULL, NULL);
            hSpxOld = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 80, 200, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindowW(L"static", L"SPX New Value:", WS_VISIBLE | WS_CHILD, 20, 110, 200, 20, hwnd, NULL, NULL, NULL);
            hSpxNew = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 110, 200, 20, hwnd, NULL, NULL, NULL);
            
			CreateWindowW(L"static", L"IXIC Old Value:", WS_VISIBLE | WS_CHILD, 20, 140, 200, 20, hwnd, NULL, NULL, NULL);
            hIxicOld = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 140, 200, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindowW(L"static", L"IXIC New Value:", WS_VISIBLE | WS_CHILD, 20, 170, 200, 20, hwnd, NULL, NULL, NULL);
            hIxicNew = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 170, 200, 20, hwnd, NULL, NULL, NULL);
			
            CreateWindowW(L"static", L"DJI Old Value:", WS_VISIBLE | WS_CHILD, 20, 200, 200, 20, hwnd, NULL, NULL, NULL);
            hDjiOld = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 200, 200, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindowW(L"static", L"DJI New Value:", WS_VISIBLE | WS_CHILD, 20, 230, 200, 20, hwnd, NULL, NULL, NULL);
            hDjiNew = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 230, 200, 20, hwnd, NULL, NULL, NULL);
            
            // Calculate button
            CreateWindowW(L"button", L"Calculate", WS_VISIBLE | WS_CHILD, 150, 270, 100, 40, hwnd, (HMENU) 1, NULL, NULL);

            // Output area for displaying results (placed below the Calculate button)
            hResultText = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | SS_LEFT,
                                        20, 330, 450, 80, hwnd, NULL, NULL, NULL);

            break;
        case WM_COMMAND:
            if (LOWORD(wp) == 1) {
                // Retrieve user input
                double portfolioOldValue = getInputValue(hPortfolioOld);
                double portfolioNewValue = getInputValue(hPortfolioNew);
                double spxOldValue = getInputValue(hSpxOld);
                double spxNewValue = getInputValue(hSpxNew);
                double ixicOldValue = getInputValue(hIxicOld);
                double ixicNewValue = getInputValue(hIxicNew);
                double djiOldValue = getInputValue(hDjiOld);
                double djiNewValue = getInputValue(hDjiNew);

                // Calculate percentage returns
                portfolioReturn = calculateReturn(portfolioOldValue, portfolioNewValue);
                spxReturn = calculateReturn(spxOldValue, spxNewValue);
                ixicReturn = calculateReturn(ixicOldValue, ixicNewValue);
                djiReturn = calculateReturn(djiOldValue, djiNewValue);

                // Display results
                char result[512];
                snprintf(result, sizeof(result),
                         "Portfolio Return: %.2f%%\nSPX Return: %.2f%%\nIXIC Return: %.2f%%\nDJI Return: %.2f%%", 
                         portfolioReturn, spxReturn, ixicReturn, djiReturn);
                SetWindowText(hResultText, result);

                // Trigger a redraw for the chart
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);

            // Draw chart only after calculation
            if (portfolioReturn != 0 && ixicReturn != 0 && spxReturn != 0 && djiReturn != 0) {
                RECT chartRect = {20, 430, 480, 600};  // Adjust the position of the chart to be below the result area
                drawCandleChart(hdc, chartRect);
            }

            EndPaint(hwnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow) {
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"PortfolioApp";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"PortfolioApp", L"Portfolio & Index Absolute Return Calculator", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
                  100, 100, 500, 800, NULL, NULL, NULL, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
