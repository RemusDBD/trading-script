#include <windows.h>
#include <stdio.h>

#define ID_CALCULATE_BUTTON 1

HWND hPortfolioOld, hPortfolioNew;
HWND hSpxOld, hSpxNew;
HWND hIxicOld, hIxicNew;
HWND hDjiOld, hDjiNew;
HWND hResultText;
HWND hResultText, hAuthorText, hDescriptionText;


// Function to calculate percentage return
double calculateReturn(double oldValue, double newValue) {
    return ((newValue - oldValue) / oldValue) * 100;
}

// Function to retrieve double from input field
double getInputValue(HWND hwnd) {
    char buffer[256];
    GetWindowText(hwnd, buffer, sizeof(buffer));
    return atof(buffer);
}

// Window Procedure to handle events
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            // Create textboxes and labels for inputs
            CreateWindow("STATIC", "Portfolio Old Value:", WS_VISIBLE | WS_CHILD, 20, 20, 200, 25, hwnd, NULL, NULL, NULL);
            hPortfolioOld = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 20, 100, 25, hwnd, NULL, NULL, NULL);

            CreateWindow("STATIC", "Portfolio New Value:", WS_VISIBLE | WS_CHILD, 20, 60, 200, 25, hwnd, NULL, NULL, NULL);
            hPortfolioNew = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 60, 100, 25, hwnd, NULL, NULL, NULL);
			
			CreateWindow("STATIC", "SPX Old Close Price:", WS_VISIBLE | WS_CHILD, 20, 100, 200, 25, hwnd, NULL, NULL, NULL);
            hSpxOld = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 100, 100, 25, hwnd, NULL, NULL, NULL);

            CreateWindow("STATIC", "SPX New Close Price:", WS_VISIBLE | WS_CHILD, 20, 140, 200, 25, hwnd, NULL, NULL, NULL);
            hSpxNew = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 140, 100, 25, hwnd, NULL, NULL, NULL);

            CreateWindow("STATIC", "IXIC Old Close Price:", WS_VISIBLE | WS_CHILD, 20, 180, 200, 25, hwnd, NULL, NULL, NULL);
            hIxicOld = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 180, 100, 25, hwnd, NULL, NULL, NULL);

            CreateWindow("STATIC", "IXIC New Close Price:", WS_VISIBLE | WS_CHILD, 20, 220, 200, 25, hwnd, NULL, NULL, NULL);
            hIxicNew = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 220, 100, 25, hwnd, NULL, NULL, NULL);

            CreateWindow("STATIC", "DJI Old Close Price:", WS_VISIBLE | WS_CHILD, 20, 260, 200, 25, hwnd, NULL, NULL, NULL);
            hDjiOld = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 260, 100, 25, hwnd, NULL, NULL, NULL);

            CreateWindow("STATIC", "DJI New Close Price:", WS_VISIBLE | WS_CHILD, 20, 300, 200, 25, hwnd, NULL, NULL, NULL);
            hDjiNew = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 300, 100, 25, hwnd, NULL, NULL, NULL);

            // Button to calculate
            CreateWindow("BUTTON", "Calculate", WS_VISIBLE | WS_CHILD, 100, 350, 100, 30, hwnd, (HMENU)ID_CALCULATE_BUTTON, NULL, NULL);

            // Textbox to show results
            hResultText = CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD, 20, 400, 300, 200, hwnd, NULL, NULL, NULL);

            // Display author and description
            hAuthorText = CreateWindow("STATIC", "Author: RemusDBD", WS_VISIBLE | WS_CHILD, 20, 510, 200, 25, hwnd, NULL, NULL, NULL);
            hDescriptionText = CreateWindow("STATIC", 
                "Algorithm: Computes the percentage change between two values.\n"
                "Formula: (New Value - Old Value) / Old Value * 100", 
                WS_VISIBLE | WS_CHILD, 20, 440, 350, 50, hwnd, NULL, NULL, NULL);

            break;
        }
		
        case WM_COMMAND:
            if (LOWORD(wp) == ID_CALCULATE_BUTTON) {
                // Retrieve values from inputs
                double portfolioOldValue = getInputValue(hPortfolioOld);
                double portfolioNewValue = getInputValue(hPortfolioNew);
                double spxOldValue = getInputValue(hSpxOld);
                double spxNewValue = getInputValue(hSpxNew);
                double ixicOldValue = getInputValue(hIxicOld);
                double ixicNewValue = getInputValue(hIxicNew);
                double djiOldValue = getInputValue(hDjiOld);
                double djiNewValue = getInputValue(hDjiNew);

                // Calculate returns
                double portfolioReturn = calculateReturn(portfolioOldValue, portfolioNewValue);
                double spxReturn = calculateReturn(spxOldValue, spxNewValue);
                double ixicReturn = calculateReturn(ixicOldValue, ixicNewValue);
                double djiReturn = calculateReturn(djiOldValue, djiNewValue);

                // Format the results and display them
                char resultBuffer[512];
                sprintf(resultBuffer, "Portfolio Return: %.2f%%\nSPX Return: %.2f%%\nIXIC Return: %.2f%%\nDJI Return: %.2f%%", 
                        portfolioReturn, spxReturn, ixicReturn, djiReturn);
                SetWindowText(hResultText, resultBuffer);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

// WinAPI main function
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = "returnCalcWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClass(&wc)) {
        return -1;
    }

    CreateWindow("returnCalcWindowClass", "Portfolio & Index Absolute Return Calculator", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
                100, 100, 400, 600, NULL, NULL, NULL, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
