#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "common.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "yestty: you must specify a program to run\n");
        return 1;
    }

    if (setenv(YESTTY_MODE_ENVVAR, YESTTY_MODE_ENVVAR_YES, 1) < 0) {
        fprintf(stderr, "yestty: failed to set envvar %s to %s: %s\n",
                YESTTY_MODE_ENVVAR, YESTTY_MODE_ENVVAR_YES, strerror(errno));
        return 1;
    }

    const char *ld_preload = getenv("LD_PRELOAD");
    char *new_ld_preload = NULL;
    if (ld_preload == NULL) {
        new_ld_preload="libyestty.so";
    } else {
        new_ld_preload = malloc(strlen("libyestty.so:") + strlen(ld_preload) + 1);
        if (new_ld_preload == NULL) {
            fprintf(stderr, "yestty: memory allocation failed: %s", strerror(errno));
        }
        stpcpy(stpcpy(new_ld_preload, "libyestty.so:"), ld_preload);
    }
    if (setenv("LD_PRELOAD", new_ld_preload, 1) < 0) {
        fprintf(stderr, "yestty: failed to set LD_PRELOAD envvar to %s: %s",
                new_ld_preload, strerror(errno));
        return 1;
    };

    argv = &argv[1];
    execvp(argv[0], argv);

    fprintf(stderr, "yestty: failed to execute %s: %s\n", argv[0], strerror(errno));
    return 1;
}

