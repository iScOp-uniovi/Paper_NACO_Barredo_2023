//WINDOWS #pragma once
#ifndef _CRONO_H
#define _CRONO_H

#include <sys/times.h> // LINUX
#include <unistd.h>
#include <iostream>
#include <stack>
#include <stdexcept>

class crono
{
private:
	crono(void) // bloqueo de constructor
	{
		throw std::runtime_error("No se pueden crear instancias de clases est�ticas");
	}

public:
	static void setTick(){ // set a tick
		_ticks.push(getTime());
	}

	static double getTick(){ // get the last tick period
		double res = getTime() - _ticks.top();
		_ticks.pop();

		return res;
	}

	static double readTick(){
		//get the last tick period
		double res = getTime() - _ticks.top();

		return res;
	}

	static	double getTime(){
		struct tms buf;
		
		times(&buf);
	        double dwUser = buf.tms_utime /(double)sysconf(_SC_CLK_TCK);
		return dwUser;
	}
/*
	static	double getTime(){
		FILETIME CreationTime = { 0 };
		FILETIME ExitTime     = { 0 };
		FILETIME KernelTime   = { 0 };
		FILETIME UserTime     = { 0 };

		// Get Process times.
		GetProcessTimes( GetCurrentProcess(),
			&CreationTime,
			&ExitTime,
			&KernelTime,
			&UserTime );

		/_*
		// Format time to readable form.
		SYSTEMTIME SystemTime = { 0 };
		FileTimeToSystemTime( &KernelTime, & SystemTime );

		// Kernel Time in HH:MM:SS:mmm.
		CString csKernelTime;
		csKernelTime.Format( _T("Kernel Time - %02d:%02d:%02d:%04d"),
		SystemTime.wHour,
		SystemTime.wMinute,
		SystemTime.wSecond,
		SystemTime.wMilliseconds );

		// Format user time to readable form.
		FileTimeToSystemTime( &UserTime, & SystemTime );

		// Kernel Time in HH:MM:SS:mmm.
		CString csUserTime;
		csUserTime.Format( _T("User Time - %02d:%02d:%02d:%04d"),
		SystemTime.wHour,
		SystemTime.wMinute,
		SystemTime.wSecond,
		SystemTime.wMilliseconds );
		*_/

		/_*
		CT2CA pszConvertedAnsiString (csUserTime);
		std::string strStd (pszConvertedAnsiString); 
		std::cout << strStd << std::endl;
		*_/

		// Return User time as seconds
		__int64 i64User = *((__int64 *) &UserTime);
		double dwUser = (double) (i64User / (double)10000000U);
		//std::cout << i64User << " " << dwUser << std::endl;

		return dwUser;
	}
*/
private:
	static std::stack<double> _ticks; // stack of ticks
};
#endif
