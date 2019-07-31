#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include <stddef.h>
#include <sys/cdefs.h>

#define OPTS_HELP_HANDLER NULL

#define arg_handler(type)                                                                          \
	struct {                                                                                   \
		const char *opt;                                                                   \
		const char *optlong;                                                               \
		int (*handler)(type * data, const char *args[]);                                   \
		const char *help;                                                                  \
		const char *args_type_info;                                                        \
		bool argument_needed : 1;                                                          \
	}

typedef struct options_hander_s {
	const arg_handler(void *) * array;
	const char *binary_name;
	size_t len;
} opts_handler_t;


void opts_create(opts_handler_t *opts, const char *binary_name, const void *opts_array,
		 size_t length) __nonnull((1, 2));
int opts_get(const opts_handler_t *opts, int ac, const char *av[], void *data) __THROW
	__nonnull((1, 3, 4));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_ARGUMENTS_H_ */
