#include "gsa.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline const char *scan_next(const char *x)
{
    for (char a = *x; *x == a; x++)
        ;
    return x;
}

void edits_to_cigar(const char *edits, char **cigar_buf)
{
    size_t n = strlen(edits);
    char *cigar = *cigar_buf = malloc(2 * n + 1);

    for (const char *x = scan_next(edits);
         *edits;
         edits = x, x = scan_next(edits))
    {
        cigar += sprintf(cigar, "%d%c", (int)(x - edits), *edits);
    }
}

static inline int count_edits(const char *cigar)
{
    int count = 0, scanned, repeats;
    for (; *cigar; cigar += scanned)
    {
        sscanf(cigar, "%d%*c%n", &repeats, &scanned);
        count += repeats;
    }
    return count;
}

static inline char *expand(char *buf, int count, char a)
{
    for (; count > 0; count--)
        *(buf++) = a;
    return buf;
}

void cigar_to_edits(const char *cigar, char **edits_buf)
{
    int no_edits = count_edits(cigar);
    char *edits = *edits_buf = malloc(no_edits + 1);

    int scanned, repeats;
    char op;
    for (; *cigar; cigar += scanned)
    {
        sscanf(cigar, "%d%c%n", &repeats, &op, &scanned);
        edits = expand(edits, repeats, op);
    }
    *edits = '\0';
}
