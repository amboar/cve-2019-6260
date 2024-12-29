// SPDX-License-Identifier: Apache-2.0
// Copyright (C) 2024 Tan Siewert

#ifndef _ARG_HELPER_H
#define _ARG_HELPER_H

#include "connection.h"

#include <argp.h>
#include <stdlib.h>

struct subcommand {
    const char *name;
    int argc;
    char **argv;
};
int parse_subcommand(const struct argp* argp, char* name, void* arguments,
                     struct argp_state* state, struct subcommand* subcommand);

/**
 * Parse everything after the `via` word.
 * The `via` word itself is not included in the arguments.
 * The arguments are expected to be in the following order:
 * 1. interface
 * 2. ip
 * 3. port
 * 4. username
 * 5. password
 *
 * @param argi The index of the `via` word in the argv array.
 * @param state The argp state.
 * @param args The connection arguments struct that should be modified.
 */
int parse_via(int argi, struct argp_state *state, struct connection_args *args);
#endif
