#pragma once

class Exception final
{
public:
	Exception() noexcept = default;
	Exception(std::string_view str) noexcept : m_message(str) {}
	Exception(const Exception&) = default;
	Exception& operator=(const Exception&) = default;

	[[nodiscard]] std::string What() const noexcept { return m_message; }

private:
	std::string m_message;
};