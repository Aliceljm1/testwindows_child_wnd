#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcChild(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcChild2(HWND, UINT, WPARAM, LPARAM);


HWND f, c;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	static char szAppNameChild[] = TEXT("HelloWinChild");
	HWND hwnd;
	HWND hwndChild;
	HWND hwndChild2;
	MSG msg;
	WNDCLASS wndclass;
	WNDCLASS wndclassChild;
	WNDCLASS wndclassChild2;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("The hellow program father"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	f = hwnd;
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//�����Ӵ���
	wndclassChild.style = CS_HREDRAW | CS_VREDRAW;
	wndclassChild.lpfnWndProc = WndProcChild;
	wndclassChild.cbClsExtra = 0;
	wndclassChild.cbWndExtra = 0;
	wndclassChild.hInstance = hInstance;
	wndclassChild.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassChild.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassChild.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassChild.lpszMenuName = NULL;
	wndclassChild.lpszClassName = szAppNameChild;

	if (!RegisterClass(&wndclassChild))
	{
		MessageBox(NULL, TEXT("This program requires windows NT!"),
			szAppNameChild, MB_ICONERROR);
		return 0;
	}

	wndclassChild2.style = CS_HREDRAW | CS_VREDRAW;
	wndclassChild2.lpfnWndProc = WndProcChild2;
	wndclassChild2.cbClsExtra = 0;
	wndclassChild2.cbWndExtra = 0;
	wndclassChild2.hInstance = hInstance;
	wndclassChild2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassChild2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassChild2.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassChild2.lpszMenuName = NULL;
	wndclassChild2.lpszClassName = TEXT("child2");
	if (!RegisterClass(&wndclassChild2))
	{
		MessageBox(NULL, TEXT("This program requires windows NT!"),
			TEXT("child2"), MB_ICONERROR);
		return 0;
	}




	//�����Ӹ�������

	//������WS_CHILD ���Ի��ô���֮����ֻ�����������������
	//�Ӵ��ڵĻ��������ܳ��������ڣ����Գ����߽�

	//ȡ������WS_CHILD �����л�����������ƣ�ֻ����ͬ��������ʾ�Ļ��ƣ�ͬʱ�Ӵ��ڻ��ڸ����ڵ�ǰ��

	//ע��**ֻ���ϸ���Ӹ����Ĺ�ϵ����ʵ�ָ��������ٵ�ʱ���Ӵ���һ�����٣����ֻ������parentWnd,û��WS_CHILD������Ϊ�����ϸ���Ӹ�����ϵ��

	//���ϸ���Ӹ������ڹ�ϵ֮�£���С���Ӵ��ڻ����Ӵ�����С�������ڵ����½ǣ����ϸ�����С��ϵͳ��������½ǡ�

	//���ϸ�״̬�������Ӵ��ڵ��ƶ��������Ӱ�죬�ϸ�״̬�»����Ӱ�죬��Ϊ�ƶ�û�д���WM_PAINT��Ϣ

	//SetParent(c, f); �˺�����ʵ������WS_CHILDһ����Ч�������ǲ���Ӱ�촰�ڵ����Ա�λ�������Ҫ����һ����ô����Ҫ�Լ�����
	
	//�ϸ�ͷ��ϸ��Ӹ����������С�������ڲ��ᴥ���Ӵ��ڵ���С����Ϣ
	hwndChild = CreateWindow(szAppNameChild,
		TEXT("The hellow program Child"),
		WS_OVERLAPPEDWINDOW | WS_CHILD,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		300,
		200,
		hwnd,
		NULL,
		hInstance,
		NULL);

	//����Ϊ�����ϸ��Ӹ�����ϵ
	//hwndChild = CreateWindow(szAppNameChild,
	//	TEXT("The hellow program Child"),
	//	WS_OVERLAPPEDWINDOW ,
	//	CW_USEDEFAULT,
	//	CW_USEDEFAULT,
	//	300,
	//	200,
	//	hwnd,
	//	NULL,
	//	hInstance,
	//	NULL);


	c = hwndChild;
	ShowWindow(hwndChild, iCmdShow);
	UpdateWindow(hwndChild);
	//�Ӵ��ڴ�������

	//**WS_CLIPSIBLINGS ��������֮��ͻ��СZ������ͬ�����������Ϸ�

	//���ڴ��������Ӵ��ڣ��۲��Ƿ���Ӱ��
	hwndChild2 = CreateWindow(TEXT("child2"),
		TEXT("child2"),
		WS_OVERLAPPEDWINDOW ,
		300,
		300,
		300,
		200,
		hwnd,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwndChild2, iCmdShow);
	UpdateWindow(hwndChild2);




	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//��������Ϣת��Ϊ�ַ���Ϣ������WM_CHAR�п��Ի������ļ����ַ�
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	CHAR chCharCode;

	switch (message)
	{
	case WM_CREATE:
		return 0;

	case WM_LBUTTONDOWN:
		SetParent(c, f);//������parentWnd,
		MessageBox(NULL, TEXT("���Ǹ����ڣ��������!,���ø��Ӵ��ڹ�ϵ"),
			"������", MB_OKCANCEL);
		return 0;

	case WM_RBUTTONDOWN:
		MessageBox(NULL, TEXT("���Ǹ����ڣ��Ҽ�����!"),
			"������", MB_OKCANCEL);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("Hello, ���Ǹ�����!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		return 0;
	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_MINIMIZE:
			MessageBox(NULL, TEXT("��С��������!"),
				"��С��������", MB_OKCANCEL);
			break;

		default:
			break;
		}
		break;
	case WM_CHAR:
		chCharCode = (TCHAR)wParam;
		return 0;
	case WM_DESTROY:
		//PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProcChild(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:
		return 0;

	case WM_LBUTTONDOWN:
		MessageBox(NULL, TEXT("�����Ӵ��ڣ��������!"),
			"�Ӵ���", MB_OKCANCEL);
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, TEXT("Hello, �����Ӵ���!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_MINIMIZE:
			MessageBox(NULL, TEXT("��С����1!"),
				"��С����1����", MB_OKCANCEL);
			break;

		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProcChild2(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:
		return 0;

	case WM_LBUTTONDOWN:
		MessageBox(NULL, TEXT("�����Ӵ���2���������!"),
			"�Ӵ���2", MB_OKCANCEL);
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, TEXT("Hello, 22�����Ӵ���2!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		return 0;


	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_MINIMIZE:
			MessageBox(NULL, TEXT("��С����2!"),
				"��С����2����", MB_OKCANCEL);
			break;

		default:
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
