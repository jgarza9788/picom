// SPDX-License-Identifier: MPL-2.0
// Copyright (c) Yuxuan Shui <yshuiv7@gmail.com>

#include "dynarr.h"
char *dynarr_join(char **arr, const char *sep) {
	if (dynarr_is_empty(arr)) {
		dynarr_free_pod(arr);
		return strdup("");
	}

	size_t total_len = 0;
	dynarr_foreach(arr, i) {
		total_len += strlen(*i);
	}

	size_t sep_len = strlen(sep);
	char *ret = malloc(total_len + sep_len * (dynarr_len(arr) - 1) + 1);
	size_t pos = 0;
	allocchk(ret);
	dynarr_foreach(arr, i) {
		if (i != arr) {
			strcpy(ret + pos, sep);
			pos += sep_len;
		}
		strcpy(ret + pos, *i);
		pos += strlen(*i);
		free(*i);
	}
	dynarr_free_pod(arr);
	ret[pos] = '\0';
	return ret;
}


TEST_CASE(dynarr_join_empty) {
	char **arr = dynarr_new(char *, 0);
	char *joined = dynarr_join(arr, ", ");
	TEST_STREQUAL(joined, "");
	free(joined);
}
