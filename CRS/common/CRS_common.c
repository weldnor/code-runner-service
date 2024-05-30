#include <malloc.h>
#include <string.h>
#include <time.h>


char *itoa(int value, char *result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) {
        *result = '\0';
        return result;
    }

    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 +
                                                                                           (tmp_value - value * base)];
    } while (value);

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';

    // Reverse the string
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}


char *concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


char *get_current_date_str() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char *text = calloc(100, sizeof(char));
    sprintf(text, "%d/%d/%d", t->tm_mday, t->tm_mon, t->tm_year);
    return text;
}

void CRS_log_info(const char *msg) {
    char *text = get_current_date_str();
    text = concat(text, " [info] ");
    text = concat(text, msg);
    text = concat(text, "\n");
    printf("%s", text);
}

void CRS_log_debug(const char *msg) {
    char *text = get_current_date_str();
    text = concat(text, " [debug] ");
    text = concat(text, msg);
    text = concat(text, "\n");
    printf("%s", text);
}

void CRS_log_warn(const char *msg) {
    char *text = get_current_date_str();
    text = concat(text, " [warn] ");
    text = concat(text, msg);
    text = concat(text, "\n");
    printf("%s", text);
}

void CRS_log_trace(const char *msg) {
    char *text = get_current_date_str();
    text = concat(text, " [trace] ");
    text = concat(text, msg);
    text = concat(text, "\n");
    printf("%s", text);
}

void CRS_log_err(const char *msg) {
    char *text = get_current_date_str();
    text = concat(text, " [err] ");
    text = concat(text, msg);
    text = concat(text, "\n");
    printf("%s", text);
}
