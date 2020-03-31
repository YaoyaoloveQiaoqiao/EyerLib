#ifndef	EYER_LIB_LOG_H
#define	EYER_LIB_LOG_H

#define EYER_LOG_LEVEL_ERROR 1
#define EYER_LOG_LEVEL_INFO 2
#define EYER_LOG_LEVEL_WARNING 3

#define MBLog(format, ...) MBPrintf(__FILE__, __FUNCTION__ ,__LINE__, 2, format, ##__VA_ARGS__)
#define BaseMBLog(format, ...) printf(format, ##__VA_ARGS__)

void MBPrintf(const char * file, const char * function, int line, int level, const char * _format, ...);

#endif