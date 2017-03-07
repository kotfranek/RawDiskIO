/* 
 * File:   log.h
 * Author: p.podwapinski
 *
 * Created on March 6, 2017, 11:38 AM
 */

#ifndef LOG_H
#define LOG_H

#include <iostream>

#if defined (LOG_ENABLED)
#define LOG(L,M) ::std::wcout << wchar_t( L ) << L": " << M << ::std::endl;
#else
#define LOG(L,M) (void)0
#endif

#define LOG_I(M) LOG('I',M)
#define LOG_E(M) LOG('E',M)

#endif /* LOG_H */

