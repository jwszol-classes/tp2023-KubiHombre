// wind.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "wind.h"
#include "vector"
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
UINT_PTR timerId = 1;
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
std::vector<int> kolejka;                       // vector przechowywujący kolejnosc jazdy windy
int ruch_windy_y = 445;                         // wartosc przesuniecia windy wzdluz osi y
int ruch_windy_od = 0;
int ruch_windy_do = 0;
bool od_do = true; 
bool czy_na_dol = false;
int czas_5s = 0;
bool stop = false;
int czas_stop = 0;
unsigned int liczba_pasazerow = 0;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Funkcja przypisuje koordynaty do ktorych ma zmierzac winda w zaleznosci od pierwszego przywolania windy w kolejce.
void planowanie_ruchow_windy() {
    if (!kolejka.empty()) {
        switch (kolejka[0])
        {
        case 0:
            ruch_windy_od = 445;
            ruch_windy_do = 295;
            break;
        case 1:
            ruch_windy_od = 445;
            ruch_windy_do = 145;
            break;
        case 2:
            ruch_windy_od = 295;
            ruch_windy_do = 445;
            break;
        case 3:
            ruch_windy_od = 295;
            ruch_windy_do = 145;
            break;
        case 4:
            ruch_windy_od = 145;
            ruch_windy_do = 295;
            break;
        case 5:
            ruch_windy_od = 145;
            ruch_windy_do = 445;
            break;
        default:
            break;
        }
    }
}

// Funkcja odpowiada za ruch windy (tzn. zmienia pozycje windy wzdloz osi y i rysuje scene na nowo)
void ruch_windy(HWND hWnd) {
    if (!kolejka.empty() or czy_na_dol) {
        if (od_do) {
            if (ruch_windy_y < ruch_windy_od) {
                ruch_windy_y+=5;
            }
            else {
                ruch_windy_y-=5;
            }
            if (ruch_windy_y == ruch_windy_od) {
                od_do = false;
                stop = true;
                EnableWindow(GetDlgItem(hWnd, ID_start), true);
                EnableWindow(GetDlgItem(hWnd, ID_dodaj_osobe_1), true);
                EnableWindow(GetDlgItem(hWnd, ID_dodaj_osobe_2), true);
            }
        }
        else {
            if (ruch_windy_y < ruch_windy_do) {
                ruch_windy_y+=5;
            }
            else {
                ruch_windy_y-=5;
            }
            if (ruch_windy_y == ruch_windy_do) {
                if(!czy_na_dol)
                    kolejka.erase(kolejka.begin());
                od_do = true;
                if (kolejka.empty() and ruch_windy_do != 445)
                    czy_na_dol = true;
                czas_5s = 0;
                stop = true;
                EnableWindow(GetDlgItem(hWnd, ID_start), true);
                EnableWindow(GetDlgItem(hWnd, ID_dodaj_osobe_1), true);
                EnableWindow(GetDlgItem(hWnd, ID_dodaj_osobe_2), true);
            }
        }
        RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE);
    }
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIND, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIND));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIND));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIND);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   // Wyswietlanie przyciskow
   HWND button_2_0 = CreateWindow(L"BUTTON", L"0", WS_VISIBLE | WS_CHILD, 10, 10, 70, 70, hWnd, (HMENU)ID_button_2_do_0, hInstance, nullptr);
   HWND button_2_1 = CreateWindow(L"BUTTON", L"1", WS_VISIBLE | WS_CHILD, 10, 80, 70, 70, hWnd, (HMENU)ID_button_2_do_1, hInstance, nullptr);
   HWND button_1_0 = CreateWindow(L"BUTTON", L"0", WS_VISIBLE | WS_CHILD, 10, 150 + 10, 70, 70, hWnd, (HMENU)ID_button_1_do_0, hInstance, nullptr);
   HWND button_1_2 = CreateWindow(L"BUTTON", L"2", WS_VISIBLE | WS_CHILD, 10, 220 + 10, 70, 70, hWnd, (HMENU)ID_button_1_do_2, hInstance, nullptr);
   HWND button_0_1 = CreateWindow(L"BUTTON", L"1", WS_VISIBLE | WS_CHILD, 10, 290 + 20, 70, 70, hWnd, (HMENU)ID_button_0_do_1, hInstance, nullptr);
   HWND button_0_2 = CreateWindow(L"BUTTON", L"2", WS_VISIBLE | WS_CHILD, 10, 360 + 20, 70, 70, hWnd, (HMENU)ID_button_0_do_2, hInstance, nullptr);
   HWND button_start = CreateWindow(L"BUTTON", L"start", WS_VISIBLE | WS_CHILD, 700, 340, 170, 70, hWnd, (HMENU)ID_start, hInstance, nullptr);
   HWND button_dodaj1 = CreateWindow(L"BUTTON", L"Dodaj pasażera", WS_VISIBLE | WS_CHILD, 700, 160, 170, 70, hWnd, (HMENU)ID_dodaj_osobe_1, hInstance, nullptr);
   HWND button_dodaj2 = CreateWindow(L"BUTTON", L"Odejmi pasażera", WS_VISIBLE | WS_CHILD, 700, 250, 170, 70, hWnd, (HMENU)ID_dodaj_osobe_2, hInstance, nullptr);



   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    //licznik czasu 
    case WM_CREATE:
        SetTimer(hWnd, 1, 25, nullptr);
        break;

    case WM_TIMER:
        if (liczba_pasazerow * 70 > 600) {
            liczba_pasazerow = 0;
            MessageBox(NULL, L"Masa została przekroczona!", L"Blad!", MB_ICONINFORMATION | MB_OK);
            RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE);
        }
        
        if (stop) {
            // Winda rusza po 3s lub po wcisniecie start
            czas_stop += 25;
            if (czas_stop == 50000) {
                stop = false;
                czas_stop = 0;
            }
        }
        else {
            if (czy_na_dol == false) {
                planowanie_ruchow_windy();
                ruch_windy(hWnd);
                czas_stop = 0;
            }
            else {
                // powrot windy na pietro nr.0 po 5s bezczynnosci 
                czas_5s += 25;
                if (czas_5s > 5000) {
                    ruch_windy_do = 445;
                    ruch_windy(hWnd);
                }
            }
        }
        break;

    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;



    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);

            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            // Przyciski przywolujace winde
            case ID_button_0_do_1:
                kolejka.push_back(0);
                czy_na_dol = false;
                break;
            case ID_button_0_do_2:
                kolejka.push_back(1);
                czy_na_dol = false;
                break;
            case ID_button_1_do_0:
                kolejka.push_back(2);
                czy_na_dol = false;
                break;
            case ID_button_1_do_2:
                kolejka.push_back(3);
                czy_na_dol = false;
                break;
            case ID_button_2_do_1:
                kolejka.push_back(4);
                czy_na_dol = false;
                break;
            case ID_button_2_do_0:
                kolejka.push_back(5);
                czy_na_dol = false;
                break;

            // przcisk aktywujacy ruch windy 
            case ID_start:
                stop = false;
                if (!kolejka.empty()) {
                    EnableWindow(GetDlgItem(hWnd, ID_start), false);
                    EnableWindow(GetDlgItem(hWnd, ID_dodaj_osobe_1), false);
                    EnableWindow(GetDlgItem(hWnd, ID_dodaj_osobe_2), false);
                }
                break;

            // przyciski dodajace pasazerow
            case ID_dodaj_osobe_1:
                liczba_pasazerow++;
                RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE);
                czas_5s = 0;
                break;
            case ID_dodaj_osobe_2:
                if (liczba_pasazerow > 0) {
                    liczba_pasazerow--;
                    czas_5s = 0;
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE);
                }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
    
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // rysowanie pieter 
            RECT trzecie_pietro = { 10, 10, 500, 150 }; 
            HBRUSH trzecie_pietro_wypelnienie = CreateSolidBrush(RGB(211, 211, 211));
            FillRect(hdc, &trzecie_pietro, trzecie_pietro_wypelnienie);
            RECT drugie_pietro = { 10, 160, 500, 300 };
            HBRUSH drugie_pietro_wypelnienie = CreateSolidBrush(RGB(211, 211, 211));
            FillRect(hdc, &drugie_pietro, drugie_pietro_wypelnienie);
            RECT pierwsze_pietro = { 10, 160 + 150, 500, 300 + 150 };
            HBRUSH pierwsze_pietro_wypelnienie = CreateSolidBrush(RGB(211, 211, 211));
            FillRect(hdc, &pierwsze_pietro, pierwsze_pietro_wypelnienie);

            // rysowanie windy
            RECT winda_ramka = { 510, 10, 650, 450 };
            HBRUSH winda_ramka_wypelnienie = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(hdc, &winda_ramka, winda_ramka_wypelnienie);
            RECT winda = { 515, ruch_windy_y - 135, 645, ruch_windy_y};
            HBRUSH winda_wypelnienie = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdc, &winda, winda_wypelnienie);

            // Rysowanie pasazerow
            for (int i = 0; i < liczba_pasazerow; i++) {
                MoveToEx(hdc, 525 + i * 15, ruch_windy_y - 2, NULL);
                LineTo(hdc, 525 + i * 15, ruch_windy_y - 122);
            }

            // Opisy pieter
            TextOutA(hdc, 400, 20, "Pietro nr.2", strlen("Pietro nr.2"));
            TextOutA(hdc, 400, 170, "Pietro nr.1", strlen("Pietro nr.1"));
            TextOutA(hdc, 400, 320, "Pietro nr.0", strlen("Pietro nr.0"));

            // Wyswietlanie masy
            std::string masa = std::to_string(liczba_pasazerow * 70);
            std::string napis = "Masa pasazerow = " + masa;
            TextOutA(hdc, 680, 30, napis.c_str(), static_cast<int>(napis.length()));
            

            EndPaint(hWnd, &ps);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
    