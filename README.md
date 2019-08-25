# arguments-handler

[![Build Status](https://travis-ci.org/LeandreBl/arguments-handler.svg?branch=master)](https://travis-ci.org/LeandreBl/arguments-handler)
<a href="https://scan.coverity.com/projects/leandrebl-arguments-handler">
  <img alt="Coverity Scan Build Status" src="https://scan.coverity.com/projects/18979/badge.svg"/>
</a>

A simple C argument parser and handler to replace using getopt and getoptlong

`Here is a code example`

```C
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arguments.h>

struct human_s {
    size_t age;
    bool is_right_handed : 1;
    /* ... */
};

static int age_handler(struct human_s *human, const char *args[])
{
    char *endptr;

    if (args[1][0] == '-') {
            fprintf(stderr, "Error: age must be positive\n");
            return (-1);
    }
    human->age = strtoul(args[1], &endptr, 10);
    if (endptr == NULL || endptr == args[1]) {
            fprintf(stderr, "Error: age must be an intger\n");
            return (-1);
    }
    return (0);
}

static int is_rh_handler(struct human_s *human, __attribute__ ((unused)) const char *args[])
{
    /* Here, this handler does not require an argument */
    human->is_right_handed = true;
    return (0);
}

/* It uses a macro to ensure type safety at compilation, avoiding void * all other the place */
static const arg_handler(struct human_s) OPTIONS[] = {
    {"-a", "--age", age_handler, "The age of your character", "POSITIVE INTEGER", true},
    {"-r", "--isrighthanded", is_rh_handler, "If your character is right handed", NULL, false},
    {"-h", "--help", OPTS_HELP_HANDLER, "Display this help", NULL, false},
    /* The OPTS_HELP_HANDLER function flag will display a custom help message based on the given values */
};

/* An implementation for -h / --help is coming soon */

int main(int ac, const char *av[])
{
    opts_handler_t handler;
    struct human_s human;

    memset(&human, 0, sizeof(human));
    opts_create(&handler, OPTIONS, sizeof(OPTIONS) / sizeof(*OPTIONS));
    /* the use of sizeof here gives us the length of 'OPTIONS' at compile time */
    if (opts_get(&handler, ac, av, &human) == -1) {
            return (EXIT_FAILURE);
    }
    // do whatever you want, this does not need any cleanup
    return (EXIT_SUCCESS);
}
```
