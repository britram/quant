// Copyright (c) 2016-2017, NetApp, Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <stdint.h>
#include <warpcore/warpcore.h>

struct q_conn;
struct stream;

struct q_stream {
    SPLAY_ENTRY(q_stream) next;
    struct q_conn * c;

    uint32_t id;
    uint8_t state;
    uint8_t _unused[3];

    struct w_iov_stailq o; ///< tail queue containing outbound data
    uint64_t out_off;

    struct w_iov_stailq i; ///< tail queue containing inbound data
    uint64_t in_off;
};


extern int64_t __attribute__((nonnull))
stream_cmp(const struct q_stream * const a, const struct q_stream * const b);

SPLAY_PROTOTYPE(stream, q_stream, next, stream_cmp)


extern struct q_stream * __attribute__((nonnull))
get_stream(struct q_conn * const c, const uint32_t id);

extern struct q_stream * __attribute__((nonnull))
new_stream(struct q_conn * const c, const uint32_t id);

extern void tls_handshake(struct q_stream * const s __attribute__((nonnull)),
                          const struct w_iov * const i);
