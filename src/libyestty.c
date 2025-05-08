#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>

#include "common.h"

enum yestty_mode {
    DEFAULT, /* no changes to isatty() */
    YES, /* always return 1 if fd is valid */
    NO, /* always return 0 if fd is valid */
};

int isatty(int fd) {
    enum yestty_mode mode = DEFAULT;
    const char *mode_envvar = getenv(YESTTY_MODE_ENVVAR);
    if (mode_envvar != NULL && strcmp(mode_envvar, YESTTY_MODE_ENVVAR_YES) == 0) {
        mode = YES;
    } else if (mode_envvar != NULL && strcmp(mode_envvar, YESTTY_MODE_ENVVAR_NO) == 0) {
        mode = NO;
    }

    /* that's what musl does in its isatty() impl */
	struct winsize wsz;
    int ret = ioctl(fd, TIOCGWINSZ, &wsz);

    if (ret == -1 && errno != ENOTTY) {
        /* some other error - invalid fd? just forward the error in this case */
        return 0;
    } else {
        switch (mode) {
        case YES:
            return 1;
        case NO:
            return 0;
        default:
            return ret == 0;
        }
    }
}

