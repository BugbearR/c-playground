#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>
#include <unistd.h>

// // (RFC 5424)
// enum LOG_FACILITY {
//     LOG_KERN, // 0 kernel messages
//     LOG_USER, // 1 user-level messages
//     LOG_MAIL, // 2 mail system
//     LOG_DAEMON, // 3 system daemons
//     LOG_AUTH, // 4 security/authorization messages
//     LOG_SYSLOG, // 5 messages generated internally by syslogd
//     LOG_LPR, // 6 line printer subsystem
//     LOG_NEWS, // 7 network news subsystem
//     LOG_UUCP, // 8 UUCP subsystem
//     LOG_CRON, // 9 clock daemon
//     LOG_AUTHPRIV, // 10 security/authorization messages
//     LOG_FTP, // 11 FTP daemon
//     L_LOG_NTP, // 12 NTP subsystem
//     L_LOG_LOG_AUDIT, // 13 log audit
//     L_LOG_LOG_ALERT, // 14 log alert
//     L_LOG_CLOCK_DAEMON, // 15 clock daemon
//     LOG_LOCAL0, // 16 local use 0 (local0)
//     LOG_LOCAL1, // 17 local use 1 (local1)
//     LOG_LOCAL2, // 18 local use 2 (local2)
//     LOG_LOCAL3, // 19 local use 3 (local3)
//     LOG_LOCAL4, // 20 local use 4 (local4)
//     LOG_LOCAL5, // 21 local use 5 (local5)
//     LOG_LOCAL6, // 22 local use 6 (local6)
//     LOG_LOCAL7 // 23 local use 7 (local7) 
// };

char *g_ident = NULL;
int g_option = 0;
int g_facility = LOG_USER;
int g_priority = LOG_INFO;

typedef struct StrIntValue
{
    char *pStr;
    int value;
} StrIntValue_t;

StrIntValue_t g_facilityList[] =
{
    {"KERN", LOG_KERN}, // 0 kernel messages
    {"USER", LOG_USER}, // 1 user-level messages
    {"MAIL", LOG_MAIL}, // 2 mail system
    {"DAEMON", LOG_DAEMON}, // 3 system daemons
    {"AUTH", LOG_AUTH}, // 4 security/authorization messages
    {"SYSLOG", LOG_SYSLOG}, // 5 messages generated internally by syslogd
    {"LPR", LOG_LPR}, // 6 line printer subsystem
    {"NEWS", LOG_NEWS}, // 7 network news subsystem
    {"UUCP", LOG_UUCP}, // 8 UUCP subsystem
    {"CRON", LOG_CRON}, // 9 clock daemon
    {"AUTHPRIV", LOG_AUTHPRIV}, // 10 security/authorization messages
    {"FTP", LOG_FTP}, // 11 FTP daemon
    {"LOCAL0", LOG_LOCAL0}, // 16 local use 0 (local0)
    {"LOCAL1", LOG_LOCAL1}, // 17 local use 1 (local1)
    {"LOCAL2", LOG_LOCAL2}, // 18 local use 2 (local2)
    {"LOCAL3", LOG_LOCAL3}, // 19 local use 3 (local3)
    {"LOCAL4", LOG_LOCAL4}, // 20 local use 4 (local4)
    {"LOCAL5", LOG_LOCAL5}, // 21 local use 5 (local5)
    {"LOCAL6", LOG_LOCAL6}, // 22 local use 6 (local6)
    {"LOCAL7", LOG_LOCAL7}, // 23 local use 7 (local7) 
    {NULL, -1}
};

StrIntValue_t g_optionList[] =
{
    {"PID", LOG_PID},
    {"CONS", LOG_CONS},
    {"ODELAY", LOG_ODELAY},
    {"NDELAY", LOG_NDELAY},
    {"NOWAIT", LOG_NOWAIT},
    {"PERROR", LOG_PERROR},
    {NULL, -1}
};

StrIntValue_t g_priorityList[] =
{
    {"EMERG", LOG_EMERG},
    {"ALERT", LOG_ALERT},
    {"CRIT", LOG_CRIT},
    {"ERR", LOG_ERR},
    {"WARNING", LOG_WARNING},
    {"NOTICE", LOG_NOTICE},
    {"INFO", LOG_INFO},
    {"DEBUG", LOG_DEBUG},
    {NULL, -1}
};

void usage(const char *pProg)
{
    int i;
    fprintf(stderr, "usage: %s [options] message\n", pProg);
    fprintf(stderr, "options:\n");
    fprintf(stderr, "  -h : Help\n");
    fprintf(stderr, "  -i ident\n");
    fprintf(stderr, "  -f facility\n");
    for (i = 0; g_facilityList[i].pStr; i++)
    {
        fprintf(stderr, "    %s\n", g_facilityList[i].pStr);
    }
    fprintf(stderr, "  -p priority\n");
    for (i = 0; g_priorityList[i].pStr; i++)
    {
        fprintf(stderr, "    %s\n", g_priorityList[i].pStr);
    }
    fprintf(stderr, "  -o option\n");
    for (i = 0; g_optionList[i].pStr; i++)
    {
        fprintf(stderr, "    %s\n", g_optionList[i].pStr);
    }
}

int StrIntValue_find(StrIntValue_t *pThis, const char *pStr) {
    int i = 0;

    for (i = 0; pThis[i].pStr; i++)
    {
        if (strcmp(pThis[i].pStr, pStr) == 0)
        {
            return pThis[i].value;
        }
    }
    return -1;
}

int parseInt(const char *pStr)
{
    return atoi(pStr);
}

int parseFacility(const char *pStr)
{
    int r;
    r = StrIntValue_find(g_facilityList, pStr);
    if (r != -1)
    {
        return r;
    }
    return parseInt(pStr);
}

int parseOption(const char *pStr)
{
    int r;
    r = StrIntValue_find(g_optionList, pStr);
    if (r != -1)
    {
        return r;
    }
    return parseInt(pStr);
}

int parsePriority(const char *pStr)
{
    int r;
    r = StrIntValue_find(g_priorityList, pStr);
    if (r != -1)
    {
        return r;
    }
    return parseInt(pStr);
}

int main(int argc, char *argv[])
{
    char opt;
    extern char *optarg;
    extern int optind, opterr;
    int facilityWk;
    int optionWk;
    int priorityWk;
    int hasError = 0;

    while ((opt = getopt(argc, argv, "f:hi:o:p:")) != -1)
    {
        switch (opt)
        {
        case 'f':
            facilityWk = parseFacility(optarg);
            if (facilityWk == -1)
            {
                fprintf(stderr, "bad facility\n");
                hasError = 1;
            }
            else
            {
                g_facility = facilityWk;
            }
            break;

        case 'h':
            usage(argv[0]);
            return EXIT_FAILURE;

        case 'i':
            g_ident = optarg;
            break;

        case 'o':
            optionWk = parseOption(optarg);
            if (optionWk == -1)
            {
                fprintf(stderr, "bad option\n");
                hasError = 1;
            }
            else
            {
                g_option ^= optionWk;
            }
            break;

        case 'p':
            priorityWk = parsePriority(optarg);
            if (priorityWk == -1)
            {
                fprintf(stderr, "bad priority\n");
                hasError = 1;
            }
            else
            {
                g_priority = priorityWk;
            }
            break;

        case '?':
        default:
            fprintf(stderr, "unknown option\n");
            hasError = 1;
        }
    }
    if (hasError)
    {
        return EXIT_FAILURE;
    }

    openlog(g_ident, g_option, g_facility);
    // POSIX has no vsyslog.
    syslog(g_priority, "%s", argv[optind]);

    closelog();

    return EXIT_SUCCESS;
}
