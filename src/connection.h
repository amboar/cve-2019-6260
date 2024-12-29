// SPDX-License-Identifier: Apache-2.0
// Copyright (C) 2024 Tan Siewert

#ifndef _CONNECTION_H
#define _CONNECTION_H

/*
 * Common struct that can be used in subcommands to pass connection arguments.
 * Commands that use this struct should use connection_parse_arguments() to
 * parse the arguments.
 */
struct connection_args
{
    const char *interface;
    const char *ip;
    const char *username;
    const char *password;
    int port;
};
#endif
