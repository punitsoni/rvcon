#ifndef __RVCON_LOG_H__
#define __RVCON_LOG_H__

#define LOG_LEVEL 1

extern FILE *logfile;

#define P_ERR(fmt, args...) fprintf(logfile, "%s:%d: error: " fmt, __FILE__, __LINE__, ##args)
#define P_INFO(fmt, args...) fprintf(logfile, "%s:%d: info: " fmt, __FILE__, __LINE__, ##args)
#define P_DBG(fmt, args...) fprintf(logfile, "%s:%d: debug: " fmt, __FILE__, __LINE__, ##args)

#endif
