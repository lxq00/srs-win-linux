#ifndef __SRS_AUTO_HEADERS_H__
#define __SRS_AUTO_HEADERS_H__

#ifdef _WIN32

#include <ws2tcpip.h>

// include windows first.
#include <windows.h>
#include <stdio.h>
// the type used by this header for windows.
typedef unsigned long long u_int64_t;
typedef u_int64_t uint64_t;
typedef long long int64_t;
typedef unsigned int u_int32_t;
typedef u_int32_t uint32_t;
typedef int int32_t;
typedef unsigned char u_int8_t;
typedef u_int8_t uint8_t;
//typedef char int8_t;
typedef unsigned short u_int16_t;
typedef u_int16_t uint16_t;
typedef short int16_t;
//typedef int64_t size_t;
struct iovec {
    void  *iov_base;    /* Starting address */
    size_t iov_len;     /* Number of bytes to transfer */
};

// for pid.
typedef int pid_t;
pid_t getpid(void);

inline int usleep(int64_t usec)
{
	Sleep((DWORD)(usec / 1000));
	return 0;
}

// for time.
#include <time.h>
#define PRId64 "lld"

// for inet helpers.
typedef int socklen_t;

// for mkdir().
#include<direct.h>


// for open().
typedef int mode_t;
#define S_IRUSR 0
#define S_IWUSR 0
#define S_IXUSR 0
#define S_IRGRP 0
#define S_IWGRP 0
#define S_IXGRP 0
#define S_IROTH 0
#define S_IXOTH 0

// for file seek.
#include <io.h>
#include <fcntl.h>
#define open _open
#define close _close
#define lseek _lseek
#define write _write
#define read _read



// others.
//#define snprintf _snprintf

inline int gettimeofday(struct timeval* tv, struct timezone* tz)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME win_time;

	GetLocalTime(&win_time);

	tm.tm_year = win_time.wYear - 1900;
	tm.tm_mon = win_time.wMonth - 1;
	tm.tm_mday = win_time.wDay;
	tm.tm_hour = win_time.wHour;
	tm.tm_min = win_time.wMinute;
	tm.tm_sec = win_time.wSecond;
	tm.tm_isdst = -1;

	clock = mktime(&tm);

	tv->tv_sec = (long)clock;
	tv->tv_usec = win_time.wMilliseconds * 1000;

	return 0;
}

inline int socket_setup()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.                                  */
		//printf("WSAStartup failed with error: %d\n", err);
		return -1;
	}
	return 0;
}

inline int socket_cleanup()
{
	WSACleanup();
	return 0;
}

inline pid_t getpid(void)
{
	return (pid_t)GetCurrentProcessId();
}

inline size_t writev(int fd, const struct iovec *iov, int iovcnt)
{
	size_t nwrite = 0;
	for (int i = 0; i < iovcnt; i++) {
		const struct iovec* current = iov + i;

		int nsent = ::send(fd, (char*)current->iov_base, current->iov_len, 0);
		if (nsent < 0) {
			return nsent;
		}

		nwrite += nsent;
		if (nsent == 0) {
			return nwrite;
		}
	}
	return nwrite;
}

inline size_t strlcpy(char * __restrict dst, const char * __restrict src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0) {
		while (--n != 0) {
			if ((*d++ = *s++) == '\0')
				break;
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';        /* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);    /* count does not include NUL */
}

#pragma comment(lib, "Ws2_32.lib") // ****


/* const char *
* inet_ntop4(src, dst, size)
*    format an IPv4 address
* return:
*    `dst' (as a const)
* notes:
*    (1) uses no statics
*    (2) takes a u_char* not an in_addr as input
* author:
*    Paul Vixie, 1996.
*/
inline char * inet_ntop4(const u_char *src, char *dst, socklen_t size)
{
	static const char fmt[128] = "%u.%u.%u.%u";
	char tmp[sizeof "255.255.255.255"];
	int l;

	l = _snprintf(tmp, sizeof(tmp), fmt, src[0], src[1], src[2], src[3]); // ****
	if (l <= 0 || (socklen_t)l >= size) {
		return (NULL);
	}
	strlcpy(dst, tmp, size);
	return (dst);
}

/* const char *
* inet_ntop6(src, dst, size)
*    convert IPv6 binary address into presentation (printable) format
* author:
*    Paul Vixie, 1996.
*/
//static char * inet_ntop6(const u_char *src, char *dst, socklen_t size)
//{
//	/*
//	* Note that int32_t and int16_t need only be "at least" large enough
//	* to contain a value of the specified size.  On some systems, like
//	* Crays, there is no such thing as an integer variable with 16 bits.
//	* Keep this in mind if you think this function should have been coded
//	* to use pointer overlays.  All the world's not a VAX.
//	*/
//	char tmp[sizeof "ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255"], *tp;
//	struct { int base, len; } best, cur;
//#define NS_IN6ADDRSZ 16
//#define NS_INT16SZ 2
//	u_int words[NS_IN6ADDRSZ / NS_INT16SZ];
//	int i;
//
//	/*
//	* Preprocess:
//	*    Copy the input (bytewise) array into a wordwise array.
//	*    Find the longest run of 0x00's in src[] for :: shorthanding.
//	*/
//	memset(words, '\0', sizeof words);
//	for (i = 0; i < NS_IN6ADDRSZ; i++)
//		words[i / 2] |= (src[i] << ((1 - (i % 2)) << 3));
//	best.base = -1;
//	best.len = 0;
//	cur.base = -1;
//	cur.len = 0;
//	for (i = 0; i < (NS_IN6ADDRSZ / NS_INT16SZ); i++) {
//		if (words[i] == 0) {
//			if (cur.base == -1)
//				cur.base = i, cur.len = 1;
//			else
//				cur.len++;
//		}
//		else {
//			if (cur.base != -1) {
//				if (best.base == -1 || cur.len > best.len)
//					best = cur;
//				cur.base = -1;
//			}
//		}
//	}
//	if (cur.base != -1) {
//		if (best.base == -1 || cur.len > best.len)
//			best = cur;
//	}
//	if (best.base != -1 && best.len < 2)
//		best.base = -1;
//
//	/*
//	* Format the result.
//	*/
//	tp = tmp;
//	for (i = 0; i < (NS_IN6ADDRSZ / NS_INT16SZ); i++) {
//		/* Are we inside the best run of 0x00's? */
//		if (best.base != -1 && i >= best.base &&
//			i < (best.base + best.len)) {
//			if (i == best.base)
//				*tp++ = ':';
//			continue;
//		}
//		/* Are we following an initial run of 0x00s or any real hex? */
//		if (i != 0)
//			*tp++ = ':';
//		/* Is this address an encapsulated IPv4? */
//		if (i == 6 && best.base == 0 && (best.len == 6 ||
//			(best.len == 7 && words[7] != 0x0001) ||
//			(best.len == 5 && words[5] == 0xffff))) {
//			if (!inet_ntop4(src + 12, tp, sizeof tmp - (tp - tmp)))
//				return (NULL);
//			tp += strlen(tp);
//			break;
//		}
//		tp += std::sprintf(tp, "%x", words[i]); // ****
//	}
//	/* Was it a trailing run of 0x00's? */
//	if (best.base != -1 && (best.base + best.len) ==
//		(NS_IN6ADDRSZ / NS_INT16SZ))
//		*tp++ = ':';
//	*tp++ = '\0';
//
//	/*
//	* Check for overflow, copy, and we're done.
//	*/
//	if ((socklen_t)(tp - tmp) > size) {
//		return (NULL);
//	}
//	strcpy(dst, tmp);
//	return (dst);
//}


/* char *
* inet_ntop(af, src, dst, size)
*    convert a network format address to presentation format.
* return:
*    pointer to presentation format address (`dst'), or NULL (see errno).
* author:
*    Paul Vixie, 1996.
*/
inline const char* inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
	switch (af) {
	case AF_INET:
		return (inet_ntop4((unsigned char*)src, (char*)dst, size));
		//case AF_INET6:
		//   return (char*)(inet_ntop6((unsigned char*)src, (char*)dst, size));
	default:
		return (NULL);
	}
	/* NOTREACHED */
}


#endif


#define SRS_AUTO_STREAM_CASTER

//st
typedef void * st_thread_t;

extern st_thread_t st_thread_create(void *(*start)(void *arg), void *arg,
	int joinable, int stack_size);
extern int st_thread_join(st_thread_t thread, void **retvalp);
extern void st_thread_interrupt(st_thread_t thread);


#endif
