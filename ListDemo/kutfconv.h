#pragma once

#ifndef KUTFCONV_H
#define KUTFCONV_H

#include <assert.h>

// UTF8 To UTF16
template<int t_nBufferLength = 128>
class KUTF8ToUTF16Ex
{
public:
	KUTF8ToUTF16Ex(const char* psz)
		: m_psz(m_szBuffer)
	{
		Init(psz);
	}

	virtual ~KUTF8ToUTF16Ex() throw()
	{
		if (m_psz != m_szBuffer)
		{
			delete[] m_psz;
		}
	}

	operator const wchar_t*() const
	{
		return(m_psz);
	}

	// 包含终结符'\0'在内的字符数目
	size_t CharCount()
	{
		if (m_psz == NULL)
			return 0;

		return m_nCharCount;
	}

protected:
	void Init(const char* psz)
	{
		if (psz == NULL)
		{
			m_psz = NULL;
			return;
		}

		m_nCharCount = MultiByteToWideChar(CP_UTF8, 0, psz, -1, NULL, 0);
		assert(m_nCharCount > 0);

		if (m_nCharCount > t_nBufferLength)
		{
			m_psz = new wchar_t[m_nCharCount];
			if (m_psz == NULL)
			{
				throw E_OUTOFMEMORY;
			}
		}

		m_nCharCount = MultiByteToWideChar(CP_UTF8, 0, psz, -1, m_psz, static_cast<int>(m_nCharCount));
		assert(m_nCharCount > 0);
	}

	wchar_t*   m_psz;
	wchar_t    m_szBuffer[t_nBufferLength];
	size_t     m_nCharCount;

	KUTF8ToUTF16Ex(const KUTF8ToUTF16Ex<t_nBufferLength>&) throw();
	KUTF8ToUTF16Ex<t_nBufferLength>& operator=(const KUTF8ToUTF16Ex<t_nBufferLength>&) throw();
};

// ANSI To UTF16
template<int t_nBufferLength = 128>
class KANSIToUTF16Ex
{
public:
	KANSIToUTF16Ex(const char* psz)
		: m_psz(m_szBuffer)
	{
		Init(psz);
	}

	virtual ~KANSIToUTF16Ex() throw()
	{
		if (m_psz != m_szBuffer)
		{
			delete[] m_psz;
		}
	}

	operator const wchar_t*() const
	{
		return(m_psz);
	}

	// 包含终结符'\0'在内的字符数目
	size_t CharCount()
	{
		if (m_psz == NULL)
			return 0;

		return m_nCharCount;
	}

protected:
	void Init(const char* psz)
	{
		if (psz == NULL)
		{
			m_psz = NULL;
			return;
		}

		m_nCharCount = MultiByteToWideChar(CP_ACP, 0, psz, -1, NULL, 0);
		assert(m_nCharCount > 0);

		if (m_nCharCount > t_nBufferLength)
		{
			m_psz = new wchar_t[m_nCharCount];
			if (m_psz == NULL)
			{
				throw E_OUTOFMEMORY;
			}
		}

		m_nCharCount = MultiByteToWideChar(CP_ACP, 0, psz, -1, m_psz, static_cast<int>(m_nCharCount));
		assert(m_nCharCount > 0);
	}

	wchar_t*   m_psz;
	wchar_t    m_szBuffer[t_nBufferLength];
	size_t     m_nCharCount;

	KANSIToUTF16Ex(const KANSIToUTF16Ex<t_nBufferLength>&) throw();
	KANSIToUTF16Ex<t_nBufferLength>& operator=(const KANSIToUTF16Ex<t_nBufferLength>&) throw();
};

// UTF16转换到UTF8
template<int t_nBufferLength = 128>
class KUTF16ToUTF8Ex
{
public:
	KUTF16ToUTF8Ex(const wchar_t* psz)
		: m_psz(m_szBuffer)
	{
		Init(psz);
	}

	virtual ~KUTF16ToUTF8Ex() throw()
	{
		if (m_psz != m_szBuffer)
		{
			delete[] m_psz;
		}
	}

	operator const char*() const
	{
		return(m_psz);
	}

	// 包含终结符'\0'在内的字符数目
	// 对于UTF8,是指的字节长度，即ASCII长度
	size_t CharCount()
	{
		if (m_psz == NULL)
			return 0;

		return m_nCharCount;
	}

protected:
	void Init(const wchar_t* psz)
	{
		if (psz == NULL)
		{
			m_psz = NULL;
			return;
		}

		m_nCharCount = WideCharToMultiByte(CP_UTF8, 0, psz, -1, NULL, 0, NULL, NULL);
		assert(m_nCharCount > 0);

		if (m_nCharCount > t_nBufferLength)
		{
			m_psz = new char[m_nCharCount];
			if (m_psz == NULL)
			{
				throw E_OUTOFMEMORY;
			}
		}

		m_nCharCount = WideCharToMultiByte(CP_UTF8, 0, psz, -1, m_psz, static_cast<int>(m_nCharCount), NULL, NULL);
		assert(m_nCharCount > 0);
	}

	char*   m_psz;
	char    m_szBuffer[t_nBufferLength];
	size_t  m_nCharCount;

	KUTF16ToUTF8Ex(const KUTF16ToUTF8Ex<t_nBufferLength>&) throw();
	KUTF16ToUTF8Ex<t_nBufferLength>& operator=(const KUTF16ToUTF8Ex<t_nBufferLength>&) throw();
};

// UTF16转换到ANSI
template<int t_nBufferLength = 128>
class KUTF16ToANSIEx
{
public:
	KUTF16ToANSIEx(const wchar_t* psz)
		: m_psz(m_szBuffer)
	{
		Init(psz);
	}

	virtual ~KUTF16ToANSIEx() throw()
	{
		if (m_psz != m_szBuffer)
		{
			delete[] m_psz;
		}
	}

	operator const char*() const
	{
		return(m_psz);
	}

	// 包含终结符'\0'在内的字符数目
	// 对于ANSI,是指的字节长度，即ASCII长度
	size_t CharCount()
	{
		if (m_psz == NULL)
			return 0;

		return m_nCharCount;
	}

protected:
	void Init(const wchar_t* psz)
	{
		if (psz == NULL)
		{
			m_psz = NULL;
			return;
		}

		m_nCharCount = WideCharToMultiByte(CP_ACP, 0, psz, -1, NULL, 0, NULL, NULL);
		assert(m_nCharCount > 0);

		if (m_nCharCount > t_nBufferLength)
		{
			m_psz = new char[m_nCharCount];
			if (m_psz == NULL)
			{
				throw E_OUTOFMEMORY;
			}
		}

		m_nCharCount = WideCharToMultiByte(CP_ACP, 0, psz, -1, m_psz, static_cast<int>(m_nCharCount), NULL, NULL);
		assert(m_nCharCount > 0);
	}

	char*   m_psz;
	char    m_szBuffer[t_nBufferLength];
	size_t  m_nCharCount;

	KUTF16ToANSIEx(const KUTF16ToANSIEx<t_nBufferLength>&) throw();
	KUTF16ToANSIEx<t_nBufferLength>& operator=(const KUTF16ToANSIEx<t_nBufferLength>&) throw();
};

//#define KUTF8ToUTF16(a) (LPCWSTR)KUTF8ToUTF16Ex<>(a)
//#define KANSIToUTF16(a) (LPCWSTR)KANSIToUTF16Ex<>(a)
//#define KUTF16ToUTF8(a) (LPCSTR)KUTF16ToUTF8Ex<>(a)
//#define KUTF16ToANSI(a) (LPCSTR)KUTF16ToANSIEx<>(a)
//#define KUTF8ToANSI(a)  (LPCSTR)KUTF16ToANSIEx<>((LPCWSTR)KUTF8ToUTF16Ex<>(a))
//#define KANSIToUTF8(a)  (LPCSTR)KUTF16ToUTF8Ex<>((LPCWSTR)KANSIToUTF16Ex<>(a))

#ifdef _UNICODE
#define TCharToUTF16(a) (LPCWSTR)a
#define TCharToANSI(a)	KUTF16ToANSI(a)
#define TCharToUTF8(a)  KUTF16ToUTF8(a)
#define UTF8ToTChar(a)  KUTF8ToUTF16(a)
#else
#define TCharToUTF16(a) KANSIToUTF16(a)
#define TCharToANSI(a)	(LPCSTR)a
#define TCharToUTF8(a)  KANSIToUTF8(a)
#define UTF8ToTChar(a)  KUTF8ToANSI(a)
#endif

#endif