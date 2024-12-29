// SPDX-License-Identifier: Apache-2.0
// Copyright (C) 2024 Tan Siewert

#include "arg_helper.h"
#include "connection.h"
#include "log.h"

#include <argp.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int parse_subcommand(const struct argp* argp, char* name, void *arguments,
                     struct argp_state* state, struct subcommand* subcommand)
{
    int argc = state->argc - state->next + 1;
    char **argv = &state->argv[state->next - 1];

    argv[0] = malloc(strlen(state->name) + strlen(name) + 1);
    if (!argv[0])
        argp_failure(state, 1, ENOMEM, 0);

    sprintf(argv[0], "%s %s", state->name, name);

    subcommand->name = name;
    subcommand->argc = argc;
    subcommand->argv = argv;

    argp_parse(argp, argc, argv, ARGP_IN_ORDER, 0, arguments);

    return 0;
}

int parse_via(int argi, struct argp_state *state, struct connection_args *args)
{
    if (argi >= state->argc)
        return -EINVAL;

    /* global argc - already processed arguments - 1 (for the `via` word) */
    int argc = state->argc - argi - 1;
    logt("parse_via found %d arguments\n", argc);

    /* Preflight validation if argc is either 1 or 5 */
    if (argc != 1 && argc != 5)
        return -EINVAL;

    args->interface = state->argv[argi + 1];
    logt("parse_via interface: %s\n", args->interface);

    if (argc == 1)
        return 0;

    args->ip = state->argv[argi + 2];
    logt("parse_via ip: %s\n", args->ip);
    args->port = atoi(state->argv[argi + 3]);
    args->username = state->argv[argi + 4];
    args->password = state->argv[argi + 5];

    return 0;
}
