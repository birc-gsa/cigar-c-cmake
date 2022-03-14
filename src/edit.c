#include "gsa.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_edits(const char *p_row, const char *q_row,
               char **p_buf, char **q_buf, char **edits_buf)
{
    size_t n = strlen(p_row);
    assert(n == strlen(q_row));

    // For p and q we might be allocating more than needed, but
    // it is hard to make efficient without being a little wasteful
    char *p = *p_buf = malloc(n + 1);
    char *q = *q_buf = malloc(n + 1);
    char *edits = *edits_buf = malloc(n + 1);
    assert(p && q && edits); // Don't want to handle allocation failures

#ifdef EXERCISE
    // FIXME: do the actual calculations here

    p[0] = '\0';     // for now we just make
    q[0] = '\0';     // empty strings
    edits[0] = '\0'; // so at least we can run tests.
#endif

    size_t j = 0, k = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (p_row[i] == '-')
        {
            edits[i] = 'I';
            q[k++] = q_row[i];
            continue;
        }
        if (q_row[i] == '-')
        {
            edits[i] = 'D';
            p[j++] = p_row[i];
            continue;
        }
        edits[i] = 'M';
        p[j++] = p_row[i];
        q[k++] = q_row[i];
    }

    // Terminate strings
    edits[n] = '\0';
    p[j] = '\0';
    q[k] = '\0';
}

int edit_dist(const char *p, const char *x, int i, const char *edits)
{
    int dist = 0;
    int j = 0;
    for (; *edits; edits++)
    {
        switch (*edits)
        {
        case 'I':
            dist++;
            i++;
            break;
        case 'D':
            dist++;
            j++;
            break;
        case 'M':
            dist += (x[i] != p[j]);
            i++;
            j++;
        }
    }
    return dist;
}
