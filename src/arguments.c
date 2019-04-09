#include <stdio.h>
#include <string.h>

#include "arguments.h"

static void display_help(const opts_handler_t *opts)
{
  printf("USAGE: %s [OPTIONS]\n", opts->binary_name);
  for (size_t i = 0; i < opts->len; ++i) {
    printf("\n  %s", opts->array[i].opt);
    if (opts->array[i].optlong != NULL)
      printf(", %s", opts->array[i].optlong);
    if (opts->array[i].args_type_info != NULL && *opts->array[i].args_type_info)
      printf(" [%s]\n", opts->array[i].args_type_info);
    else
      printf("\n");
    printf("    %s\n", opts->array[i].help);
  }
}

static bool is_valid_opt(const opts_handler_t *opts, const char *opt, size_t index)
{
  return (!strcmp(opt, opts->array[index].opt) || !strcmp(opt, opts->array[index].optlong));
}

static int check_opt(const opts_handler_t *opts, const char *iargs[], void *dest)
{
  for (size_t i = 0; i < opts->len; ++i) {
    if (is_valid_opt(opts, iargs[0], i)) {
      if (opts->array[i].argument_needed == true && iargs[1] == NULL) {
        fprintf(stderr, "Option: '%s' needs an argument\n", iargs[0]);
        return (-1);
      }
      else if (opts->array[i].handler == OPTS_HELP_HANDLER) {
        display_help(opts);
        return (1);
      }
      else if (opts->array[i].handler(dest, iargs) != 0) {
        fprintf(stderr, "Invalid parameter after '%s' option.\n", iargs[0]);
        return (-1);
      }
      return (0);
    }
  }
  fprintf(stderr, "Unknown parameter: '%s'.\n", iargs[0]);
  return (-1);
}

void opts_create(opts_handler_t *opts, const char *binary_name, const void *opts_array, size_t length)
{
  opts->array = opts_array;
  opts->len = length;
  opts->binary_name = binary_name;
}

int opts_get(const opts_handler_t *opts, int ac, const char *av[], void *data)
{
  int ret = 0;
  int chk;

  if (opts->array == NULL)
    return (-1);
  for (int i = 1; i < ac; ++i) {
    if (av[i][0] == '-') {
      chk = check_opt(opts, &av[i], data);
      if (chk != 0)
        return (chk);
      ret += chk;
      ++i;
    }
  }
  return (ret);
}
