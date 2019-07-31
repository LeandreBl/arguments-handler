#include <criterion/criterion.h>

#include "arguments.h"

#define ARRAY_LEN(array) sizeof(array) / sizeof(*array)

struct options_s {
	int iflag;
	bool test_flag;
};

static int iflag_handler(struct options_s *options, const char *args[])
{
	cr_assert_str_eq(args[1], "157");
	options->iflag = atoi(args[1]);
	return (0);
}

static int tflag_handler(struct options_s *options, __attribute__((unused)) const char *args[])
{
	options->test_flag = true;
	return (0);
}

static const arg_handler(struct options_s) TEST_OPTS[] = {
	{"-i", "--index", iflag_handler, "I'm a flag to be tested", "INTEGER", true},
	{"-t", "--test", tflag_handler, "I'm a flag to be tested", NULL, false},
	{"-h", "--help", OPTS_HELP_HANDLER, "Display this help", NULL, false},
};


Test(opts, success)
{
	static const char *av[] = {"libtest", "-i", "157", "--test"};
	struct options_s options;
	opts_handler_t handler;

	opts_create(&handler, "tests", TEST_OPTS, ARRAY_LEN(TEST_OPTS));
	cr_assert(opts_get(&handler, ARRAY_LEN(av), av, &options) == 0);
	cr_assert_eq(options.iflag, 157);
	cr_assert_eq(options.test_flag, true);
}
