/*	$OpenBSD: log.h,v 1.7 2002/05/19 20:54:52 deraadt Exp $	*/

/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 */

#ifndef SSH_LOG_H
#define SSH_LOG_H

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h> /* For O_NONBLOCK */
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>

#include <syslog.h> /* Needed for LOG_AUTHPRIV (if present) */

/* Supported syslog facilities and levels. */
typedef enum {
	SYSLOG_FACILITY_DAEMON,
	SYSLOG_FACILITY_USER,
	SYSLOG_FACILITY_AUTH,
#ifdef LOG_AUTHPRIV
	SYSLOG_FACILITY_AUTHPRIV,
#endif
	SYSLOG_FACILITY_LOCAL0,
	SYSLOG_FACILITY_LOCAL1,
	SYSLOG_FACILITY_LOCAL2,
	SYSLOG_FACILITY_LOCAL3,
	SYSLOG_FACILITY_LOCAL4,
	SYSLOG_FACILITY_LOCAL5,
	SYSLOG_FACILITY_LOCAL6,
	SYSLOG_FACILITY_LOCAL7,
	SYSLOG_FACILITY_NOT_SET = -1
}       SyslogFacility;

typedef enum {
	SYSLOG_LEVEL_QUIET,
	SYSLOG_LEVEL_FATAL,
	SYSLOG_LEVEL_ERROR,
	SYSLOG_LEVEL_INFO,
	SYSLOG_LEVEL_VERBOSE,
	SYSLOG_LEVEL_DEBUG1,
	SYSLOG_LEVEL_DEBUG2,
	SYSLOG_LEVEL_DEBUG3,
	SYSLOG_LEVEL_NOT_SET = -1
}       LogLevel;

void     log_init(char *, LogLevel, SyslogFacility, FILE*, int);
extern LogLevel log_level;


SyslogFacility	log_facility_number(char *);
LogLevel log_level_number(char *);

void     fatal(const char *, ...) __attribute__((format(printf, 1, 2)));
void     error(const char *, ...) __attribute__((format(printf, 1, 2)));
void     log(const char *, ...) __attribute__((format(printf, 1, 2)));
void     verbose(const char *, ...) __attribute__((format(printf, 1, 2)));
void     debug1(const char *, ...) __attribute__((format(printf, 1, 2)));
void     debug2(const char *, ...) __attribute__((format(printf, 1, 2)));
void     debug3(const char *, ...) __attribute__((format(printf, 1, 2)));

void     fatal_cleanup(void);
void     fatal_add_cleanup(void (*) (void *), void *);
void     fatal_remove_cleanup(void (*) (void *), void *);

void	 do_log(LogLevel, const char *, va_list);

#endif
