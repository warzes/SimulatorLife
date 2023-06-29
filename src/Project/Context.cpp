#include "stdafx.h"
#include "Context.h"
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) noexcept
{
	Context* context = reinterpret_cast<Context*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (context == nullptr) return DefWindowProc(hwnd, message, wparam, lparam);

	switch (message) 
	{
	case WM_DESTROY:
		context->m_running = false;
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE) 
		{
			context->m_running = false;
			PostQuitMessage(0);
		}
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	return 0;
}
//-----------------------------------------------------------------------------
Context::Context()
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = L"MyWindowClass";
	RegisterClass(&wc);

	m_hwnd = CreateWindow(wc.lpszClassName, L"Simulators", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);
	m_hdc = GetDC(m_hwnd);

	PIXELFORMATDESCRIPTOR pfd = { sizeof(pfd), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 0, 32, 16 };
	SetPixelFormat(m_hdc, ChoosePixelFormat(m_hdc, &pfd), &pfd);
	m_hglrc = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, m_hglrc);

	ShowWindow(m_hwnd, SW_SHOWNORMAL);

	SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	//glShadeModel(GL_FLAT);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	m_running = true;


	
}
//-----------------------------------------------------------------------------
Context::~Context()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hglrc);
	ReleaseDC(m_hwnd, m_hdc);
	DestroyWindow(m_hwnd);
}
//-----------------------------------------------------------------------------
void Context::Run(std::unique_ptr<IApp> app)
{
	if (app == nullptr) return;
	app->Init();

	auto prevTime = std::chrono::high_resolution_clock::now();
	float deltaTime = 0.0f;
	float tickPause = 0.0f;

	constexpr float TickSize = 1.0f;

	while (m_running)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const std::chrono::duration<float> elapsedTime = currentTime - prevTime;
		prevTime = currentTime;
		deltaTime = elapsedTime.count();
		tickPause += deltaTime;

		if (PeekMessage(&m_msg, m_hwnd, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}

		if (!app->Update(deltaTime)) break;

		if (tickPause > TickSize)
		{
			tickPause = 0.0f;
			app->Tick();
		}

		RECT rect;
		GetClientRect(m_hwnd, &rect);

		m_windowWidth = rect.right - rect.left;
		m_windowHeight = rect.bottom - rect.top;
		m_aspectWindows = (float)m_windowWidth / (float)m_windowHeight;

		glViewport(0, 0, m_windowWidth, m_windowHeight);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, 480.0 * m_aspectWindows, 480.0, 0.0);

		app->Frame();

		

		SwapBuffers(m_hdc);

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
//-----------------------------------------------------------------------------