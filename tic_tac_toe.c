#include <stdio.h>
#include <windows.h>
#include <wingdi.h>
#define GRID_SIZE 3
#define SQUARE_SIZE 100

HBRUSH hBackgroundBrush;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{
    WNDCLASSEX wc = {0};
    HWND hwnd;
    MSG msg;

    // Step 1: Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS); // Use IDC_ARROW for a standard arrow cursor
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Zanoon'sGame";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Aint working ya mu3alim", "L Computer", MB_ICONERROR | MB_ICONEXCLAMATION);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowExA(
        0,
        "Zanoon'sGame",      // Class name registered earlier
        "Zanoon's Game",     // Window title
        WS_OVERLAPPEDWINDOW, // Window style
        CW_USEDEFAULT,       // X position
        CW_USEDEFAULT,       // Y position
        750,                 // Width
        750,                 // Height
        NULL,                // Parent window (none)
        NULL,                // Menu (none)
        hInstance,           // Instance handle
        NULL                 // Additional application data (none)
    );

    if (!hwnd)
    {
        MessageBox(NULL, "Window Flopped", "L Computer", MB_ICONERROR);
        return 0;
    }

    // Step 3: Showing and Updating the Window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 4: Message Loop
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// Step 5: Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{    
    switch (uMsg)
    {
        
        case WM_CREATE:
        {

            HWND quitButton = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed 
                "QUIT GAME", // Button text 
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50,         // x position 
                600,         // y position 
                200,        // Button width
                60,         // Button height
                hwnd,       // Parent window
                (HMENU)1,   // Control ID
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL);      // Pointer not needed

             HWND resetbutton = CreateWindow(
                 "BUTTON",
                 "RESET GAME",
                 WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 500,
                 600,
                 200,
                 60,
                 hwnd,
                 (HMENU)2,
                 (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                 NULL

             );

            for (int i = 1; i <=3; i++)
            {
                for (int j = 1; j <= 3; j++)
                {

                }
            }


            
            return 0;
        }
        
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            for(int y = 0; y < SQUARE_SIZE; y++)
            {
                for(int x = 0; y < GRID_SIZE; x++)
                {
                    RECT rect;
                    rect.left = x * SQUARE_SIZE;
                    rect.top = y * SQUARE_SIZE;
                    rect.right = rect.left + SQUARE_SIZE;
                    rect.bottom = rect.top + SQUARE_SIZE;
                    
                    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
                    FrameRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
                }
            }
            FillRect(hdc, &ps.rcPaint, hBackgroundBrush);

            
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_SIZE:
            // Handle resizing if needed
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
