#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;                        // Définition de la fonction de procédure de fenêtre
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);                                 // Enregistrement de la classe de fenêtre

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Exemple de formulaire WinAPI",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    // Création d'une étiquette
    HWND hLabel = CreateWindow(
        L"STATIC",                                      // Classe prédéfinie pour l'étiquette
        L"Ceci est un label",                            // Texte de l'étiquette
        WS_VISIBLE | WS_CHILD | WS_BORDER,               // Styles
        50, 50, 200, 20,                                 // Position et taille
        hwnd,                                           // Fenêtre parente
        NULL,
        hInstance,
        NULL
    );

    // Création d'un bouton
    HWND hButton = CreateWindow(
        L"BUTTON",                                      // Classe prédéfinie pour le bouton
        L"Cliquez ici",                                 // Texte du bouton
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,        // Styles
        50, 100, 100, 30,                                // Position et taille
        hwnd,                                           // Fenêtre parente
        (HMENU)1,                                       // Identifiant du bouton
        hInstance,
        NULL
    );

    if (hLabel == NULL || hButton == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1)
        {
            MessageBox(hwnd, L"Le bouton a été cliqué !", L"Information", MB_OK);
            return 0;
        }
        break;
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
