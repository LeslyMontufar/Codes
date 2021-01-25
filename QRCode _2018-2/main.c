#include <windows.h>
#include "QRCodeEncode.h"

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define HELP 4

#define GET_QR_CODE_BUTTON 5
#define CLEAR_ALL_BUTTON 6
#define DELETE_ALL_QR_BUTTON 7

#define LARGURA_WINDOW 500
#define ALTURA_WINDOW 500

#define ALTURA_ENTER_TEXT 20
#define LARGURA_ENTER_TEXT 150 + 100

#define Y0_ENTER_TEXT 25
#define Y0_ENTER_TEXT_INPUT Y0_ENTER_TEXT + ALTURA_ENTER_TEXT+2

#define Y0_ERROR_CORRECTION Y0_ENTER_TEXT_INPUT + 2*ALTURA_ENTER_TEXT
#define Y0_ERROR_CORRECTION_INPUT Y0_ERROR_CORRECTION+ALTURA_ENTER_TEXT +2
#define Y0_TEXT_ENTERED 25+5*ALTURA_ENTER_TEXT+ 30
#define Y0_TEXT_ENTERED_OUTPUT 25+6*ALTURA_ENTER_TEXT+30

#define Y0_LAST_QR Y0_TEXT_ENTERED_OUTPUT+ ALTURA_ENTER_TEXT + 20
#define Y0_LAST_QR_OUTPUT Y0_LAST_QR + ALTURA_ENTER_TEXT +2

#define Y0_IMAGE_INFO Y0_LAST_QR_OUTPUT + ALTURA_ENTER_TEXT +1
#define Y0_VERSION_INFO Y0_IMAGE_INFO + ALTURA_ENTER_TEXT +1
#define Y0_ERROR_INFO Y0_VERSION_INFO + ALTURA_ENTER_TEXT +1
#define Y0_MASK_INFO Y0_ERROR_INFO + ALTURA_ENTER_TEXT +1

#define LARGURA_LAST_QR 150
#define X_OUTPUT 25+100

#define TEXT_N 300

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND); // prototipo
void AddControls(HWND);

HWND hText, hTextEntered, hErrorCorrection, hLastQRImage, hLastQRVersion, hLastQRError, hLastQRMask;
HMENU hMenu;

void getQRCode(HWND);
void clearAll();
void deleteAllQR();

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    //system("chcp 1252");
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass", L"QR Code Generator - by Lesly Montufar", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, LARGURA_WINDOW, ALTURA_WINDOW,
                  NULL, NULL, NULL, NULL);


    MSG msg = {0};

    while( GetMessageW(&msg, NULL, NULL, NULL) ) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    int val;
    switch(msg) {
    case WM_COMMAND:
        switch(wp) {
        case FILE_MENU_EXIT:
            val = MessageBoxW(hWnd, L"Are you sure?", L"Wait!", MB_YESNO | MB_ICONEXCLAMATION);

            if(val == IDYES) {
                DestroyWindow(hWnd);
            }
            break;
        case FILE_MENU_NEW:
            MessageBeep(MB_ICONINFORMATION);
            break;
        case HELP:
            MessageBeep(MB_ICONEXCLAMATION);
            MessageBox(NULL, "A QR code is a special type of barcode that can encode information like numbers, letters, and Kanji characters.","Help", MB_SERVICE_NOTIFICATION);
            break;
        case GET_QR_CODE_BUTTON:
            getQRCode(hWnd);
            break;
        case CLEAR_ALL_BUTTON:
            clearAll();
            break;
        case DELETE_ALL_QR_BUTTON:
            deleteAllQR();
            break;
        }
        break;

    case WM_CREATE:
        AddMenus(hWnd);
        AddControls(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void AddMenus(HWND hWnd) {
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();
    AppendMenu(hSubMenu, MF_STRING, NULL, "Do something");

    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open SubMenu");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");


    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    AppendMenu(hMenu, MF_STRING, HELP, "Help");

    SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd) {
    CreateWindowW(L"static", L"Enter text:", WS_VISIBLE | WS_CHILD, 25, Y0_ENTER_TEXT, LARGURA_ENTER_TEXT, ALTURA_ENTER_TEXT, hWnd,
                  NULL, NULL, NULL);
    hText = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 25, Y0_ENTER_TEXT_INPUT, LARGURA_ENTER_TEXT, ALTURA_ENTER_TEXT, hWnd,
                          NULL, NULL, NULL);
    CreateWindowW(L"static", L"Enter error correction (L, M, Q, H):", WS_VISIBLE | WS_CHILD, 25, Y0_ERROR_CORRECTION, LARGURA_ENTER_TEXT+100, ALTURA_ENTER_TEXT, hWnd,
                  NULL, NULL, NULL);
    hErrorCorrection = CreateWindowW(L"Edit", L"H", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 25, Y0_ERROR_CORRECTION_INPUT, LARGURA_ENTER_TEXT, ALTURA_ENTER_TEXT, hWnd,
                          NULL, NULL, NULL);


    CreateWindowW(L"static", L"Text entered:", WS_VISIBLE | WS_CHILD, 25, Y0_TEXT_ENTERED, LARGURA_ENTER_TEXT, ALTURA_ENTER_TEXT, hWnd,
                  NULL, NULL, NULL);
    hTextEntered = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL, 25, Y0_TEXT_ENTERED_OUTPUT, LARGURA_ENTER_TEXT, ALTURA_ENTER_TEXT, hWnd,
                                 NULL, NULL, NULL);

    CreateWindowW(L"static", L"Last QR Code Generated:", WS_VISIBLE | WS_CHILD, 25, Y0_LAST_QR, LARGURA_ENTER_TEXT, ALTURA_ENTER_TEXT, hWnd,
                  NULL, NULL, NULL);
    CreateWindowW(L"static", L"Image", WS_VISIBLE | WS_CHILD, 25, Y0_IMAGE_INFO, 100, ALTURA_ENTER_TEXT, hWnd,
                  NULL, NULL, NULL);
    CreateWindowW(L"static", L"Version", WS_VISIBLE | WS_CHILD, 25, Y0_VERSION_INFO, 100, ALTURA_ENTER_TEXT, hWnd,
                  NULL, NULL, NULL);
    CreateWindowW(L"static", L"Error", WS_VISIBLE | WS_CHILD, 25, Y0_ERROR_INFO, 100, ALTURA_ENTER_TEXT, hWnd,
                  NULL, NULL, NULL);
    CreateWindowW(L"static", L"Mask", WS_VISIBLE | WS_CHILD, 25, Y0_MASK_INFO, 100, ALTURA_ENTER_TEXT, hWnd,
                  NULL, NULL, NULL);

    hLastQRImage = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE, X_OUTPUT, Y0_IMAGE_INFO, LARGURA_LAST_QR, ALTURA_ENTER_TEXT, hWnd,
                                    NULL, NULL, NULL);
    hLastQRVersion = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE, X_OUTPUT, Y0_VERSION_INFO, LARGURA_LAST_QR, ALTURA_ENTER_TEXT, hWnd,
                                    NULL, NULL, NULL);
    hLastQRError = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE, X_OUTPUT, Y0_ERROR_INFO, LARGURA_LAST_QR, ALTURA_ENTER_TEXT, hWnd,
                                    NULL, NULL, NULL);
    hLastQRMask = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE, X_OUTPUT, Y0_MASK_INFO, LARGURA_LAST_QR, ALTURA_ENTER_TEXT, hWnd,
                                    NULL, NULL, NULL);


    CreateWindowW(L"Button", L"Get QR Code", WS_VISIBLE | WS_CHILD, 25, ALTURA_WINDOW-100, 100, ALTURA_ENTER_TEXT, hWnd, (HMENU)GET_QR_CODE_BUTTON, NULL, NULL);
    CreateWindowW(L"Button", L"Clear All", WS_VISIBLE | WS_CHILD, 200, ALTURA_WINDOW-100, 100, ALTURA_ENTER_TEXT, hWnd, (HMENU)CLEAR_ALL_BUTTON, NULL, NULL);
    CreateWindowW(L"Button", L"Delete All QR", WS_VISIBLE | WS_CHILD, 375, ALTURA_WINDOW-100, 100, ALTURA_ENTER_TEXT, hWnd, (HMENU)DELETE_ALL_QR_BUTTON, NULL, NULL);

}

void getQRCode(HWND hWnd) {
    char text[TEXT_N];
    int val;
    GetWindowText(hText, text, TEXT_N);
    char error[TEXT_N], errcorrection;
    GetWindowText(hErrorCorrection, error, TEXT_N);

    if(strcmp(text, "")==0) {
        val = MessageBoxW(hWnd, L"You did not enter any word!", NULL, MB_ABORTRETRYIGNORE | MB_ICONERROR);
        switch(val) {
        case IDABORT:
            DestroyWindow(hWnd);
            break;
        case IDRETRY:
            return 0;
        case IDIGNORE:
            break;
        }
    }
    SetWindowText(hTextEntered, text);

    switch(error[0]){
    case 'L':
        errcorrection = _L;
        break;
    case 'M':
        errcorrection = _M;
        break;
    case 'Q':
        errcorrection = _Q;
        break;
    case 'H':
        errcorrection = _H;
        break;
    default:
        val = MessageBoxW(hWnd, L"Invalid error correction!", NULL, MB_ABORTRETRYIGNORE | MB_ICONERROR);
        switch(val) {
        case IDABORT:
            DestroyWindow(hWnd);
            break;
        case IDRETRY:
            return 0;
        case IDIGNORE:
            break;
        }
    }


    int num;
    readFileInt("Enumeration.bin", &num);
    char imageName[14] = "QRCode";
    fromDecimal(DECIMAL, num, imageName + 6, 3);
    strcat(imageName, ".pbm");
    SetWindowText(hLastQRImage, imageName);
    SetWindowText(hLastQRError, error);

    char version[TEXT_N]= "1", mask[TEXT_N] = "1";
    QRCodeMain(text, errcorrection, version, mask);
    SetWindowText(hLastQRVersion, version);
    SetWindowText(hLastQRMask, mask);

}

void clearAll() {
    SetWindowText(hText, "");
    SetWindowText(hErrorCorrection, "H");
    SetWindowText(hTextEntered, "");
    SetWindowText(hLastQRImage, "");
    SetWindowText(hLastQRVersion, "");
    SetWindowText(hLastQRError, "");
    SetWindowText(hLastQRMask, "");
}
void deleteAllQR(){
    int num, i;
    const char command[18] = "del QRCode";
    readFileInt("Enumeration.bin", &num);
    for(i=num-1; i>0; i--){
        fromDecimal(DECIMAL, i, command + 10, 3);
        strcat(command, ".pbm");
        system(command);
    }
    num = 1;
    writeFileInt("Enumeration.bin", num);
    clearAll();
}
