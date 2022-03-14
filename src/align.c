#include "gsa.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void local_align(const char *p, const char *x, int i, const char *edits,
                 char **p_row_buf, char **x_row_buf)
{
    size_t n = strlen(edits);
    char *p_row = *p_row_buf = malloc(n + 1);
    char *x_row = *x_row_buf = malloc(n + 1);
    assert(p_row && x_row); // Don't want to handle allocation failures

    size_t j = 0, k = 0;
    for (size_t l = 0; l < n; l++)
    {
        switch (edits[l])
        {
        case 'M':
            p_row[l] = p[j++];
            x_row[l] = x[i + k++];
            break;
        case 'I':
            p_row[l] = '-';
            x_row[l] = x[i + k++];
            break;
        case 'D':
            p_row[l] = p[j++];
            x_row[l] = '-';
            break;
        }
    }
    p_row[n] = x_row[n] = '\0';
}

void align(const char *p, const char *q, const char *edits,
           char **p_row, char **q_row)
{
    local_align(p, q, 0, edits, p_row, q_row);
}
