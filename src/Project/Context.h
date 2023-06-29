#pragma once

#include "IApp.h"

class Context final
{
public:
	Context();
	~Context();

	void Run(std::unique_ptr<IApp> app);

private:
	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM) noexcept;
	HWND m_hwnd = nullptr;
	HDC m_hdc = nullptr;
	HGLRC m_hglrc = nullptr;
	MSG m_msg = {};
	int m_windowWidth = 0;
	int m_windowHeight = 0;
	float m_aspectWindows = 0.0f;
	bool m_running = false;
};