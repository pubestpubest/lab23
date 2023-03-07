#include <windows.h>
#include <stdio.h>
#include <cstdlib>
HWND textField, button, textBox1, textBox2;
char text1[20];
char text2[20];
double input1 = 0, input2 = 0;
int windowHeight = 200;
int windowWidth = 250;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{

	/* Upon destruction, tell the main thread to stop */
	case WM_ERASEBKGND:
	{
		HDC hdc = (HDC)wParam;
		RECT rc;
		GetClientRect(hwnd, &rc);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // red background
		FillRect(hdc, &rc, hBrush);
		DeleteObject(hBrush);
		return (LRESULT)1;
	}

	case WM_CREATE:
	{
		textField = CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD, (windowWidth / 2) - (180 / 2), 10, 175, 20, hwnd, NULL, NULL, NULL);
		// button = CreateWindow("BUTTON","CLOSE",WS_VISIBLE|WS_CHILD|WS_BORDER,20,50,100,50,hwnd,(HMENU) 1,NULL,NULL);
		textBox1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, (windowWidth / 2) - 80, 35, 150, 20, hwnd, NULL, NULL, NULL);
		textBox2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, (windowWidth / 2) - 80, 60, 150, 20, hwnd, NULL, NULL, NULL);
		CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 65, 100, 25, 25, hwnd, (HMENU)1, NULL, NULL);
		CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 95, 100, 25, 25, hwnd, (HMENU)2, NULL, NULL);
		CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 125, 100, 25, 25, hwnd, (HMENU)3, NULL, NULL);
		CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 155, 100, 25, 25, hwnd, (HMENU)4, NULL, NULL);
		break;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 1:
		{
			GetWindowText(textBox1, &text1[0], 20);
			GetWindowText(textBox2, &text2[0], 20);
			input1 = std::atof(text1);
			input2 = std::atof(text2);
			char t[100];
			sprintf(t, "%f", input1 + input2);
			::MessageBox(hwnd, t, "Result", MB_OK);
		}
		/*::MessageBeep(MB_ICONERROR);
		PostQuitMessage(0);
		::MessageBox(hwnd,"Button was clicked","clicked",MB_OK);*/
		break;
		case 2:
		{
			GetWindowText(textBox1, &text1[0], 20);
			GetWindowText(textBox2, &text2[0], 20);
			input1 = std::atof(text1);
			input2 = std::atof(text2);
			char t[100];
			sprintf(t, "%f", input1 - input2);
			::MessageBox(hwnd, t, "Result", MB_OK);
		}
		/*int gwtstat=0;
		char * t= &textSaved[0];
		gwtstat=GetWindowText(textBox1,t,20);

		::MessageBox(hwnd,textSaved,"text",MB_OK);*/
		break;
		case 3:
		{
			GetWindowText(textBox1, &text1[0], 20);
			GetWindowText(textBox2, &text2[0], 20);
			input1 = std::atof(text1);
			input2 = std::atof(text2);
			char t[100];
			sprintf(t, "%f", input1 * input2);
			::MessageBox(hwnd, t, "Result", MB_OK);
		}

		break;
		case 4:
		{
			GetWindowText(textBox1, &text1[0], 20);
			GetWindowText(textBox2, &text2[0], 20);
			input1 = std::atof(text1);
			input2 = std::atof(text2);
			char t[100];
			sprintf(t, "%f", input1 / input2);
			::MessageBox(hwnd, t, "Result", MB_OK);
		}

		break;
		}

		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	/* All other messages (a lot of them) are processed using default procedures */
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd;	   /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg;	   /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc; /* This is where we will send messages to */
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	  /* Load a standard icon */
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "My Calculator", WS_VISIBLE | WS_SYSMENU,
						  CW_USEDEFAULT, /* x */
						  CW_USEDEFAULT, /* y */
						  windowWidth,	 /* width */
						  windowHeight,	 /* height */
						  NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{							/* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg);	/* Send it to WndProc */
	}
	return msg.wParam;
}
