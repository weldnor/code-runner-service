//
// Created by anton on 26.05.24.
//

#ifndef CRS_CRS_COMMON_H
#define CRS_CRS_COMMON_H

char *itoa(int value, char *result, int base);

char *concat(const char *s1, const char *s2);

void CRS_log_info(const char *msg);

void CRS_log_debug(const char *msg);

void CRS_log_warn(const char *msg);

void CRS_log_trace(const char *msg);

void CRS_log_err(const char *msg);

#endif //CRS_CRS_COMMON_H
