/************************************************************

	Time.h
	Date and time
	
	Copyright © Apple Computer,Inc.  1987-1991.
	All Rights Reserved.

************************************************************/


#ifndef __TIME_H__ /* __TIME__ is a reserved preprocessor symbol */
#define __TIME_H__

#ifndef NULL
#define NULL 0
#endif

#ifndef __size_t__
#define __size_t__
typedef unsigned int size_t;
#endif

/*
 *	Declarations
 */

#define CLOCKS_PER_SEC 60
typedef unsigned long int clock_t;
typedef unsigned long int time_t;
struct tm {
	int tm_sec;		/* Seconds after the minute -- [0, 61] */
	int tm_min;		/* Minutes after the hour -- [0, 59] */
	int tm_hour;	/* Hours after midnight -- [0, 23] */
	int tm_mday;	/* Day of the month -- [1, 31] */
	int tm_mon;		/* Months since January -- [0, 11] */
	int tm_year;	/* Years since 1900 */
	int tm_wday;	/* Days since Sunday -- [0, 6] */
	int tm_yday;	/* Days since January 1 -- [0, 365] */
	int tm_isdst;	/* Daylight Savings Time flag */
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 *	Time manipulation functions
 */

clock_t clock(void);						/* function */
#define clock() __tickcount()				/* macro - TickCount() */
pascal unsigned long __tickcount(void)
    = 0xA975; 

double  difftime(time_t time1, time_t time0);        		/* function */
#define difftime(time1,time0) ((long double)time1 - time0)	/* macro */

time_t mktime(struct tm *timeptr);
time_t time(time_t *timer);


/*
 *	Time conversion functions
 */

char *asctime (const struct tm *timeptr);
char *ctime(const time_t *timer);
struct tm *gmtime(const time_t *timer);
struct tm *localtime(const time_t *timer);
size_t strftime(char *s, size_t maxsize,
				 const char *format, const struct tm *timerptr);

#ifdef __cplusplus
}
#endif

#endif
