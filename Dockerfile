# SPDX-License-Identifier: MIT
FROM ubuntu:24.04 AS builder
ARG BUILDOS BUILDARCH
RUN apt-get update -y -q && \
    DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y -q \
        ca-certificates \
        curl \
        git \
        build-essential \
        llvm \
        clang \
        libbpf-dev \
    && rm -rf /var/lib/apt/lists/*
ARG GO_VERSION=1.25.3
ENV PATH=$PATH:/usr/local/go/bin
RUN curl -sL https://go.dev/dl/go${GO_VERSION}.${BUILDOS}-${BUILDARCH}.tar.gz | tar -v -C /usr/local -xz
WORKDIR /opt/ebpf-demo
COPY . . 
RUN make build

FROM scratch
COPY --from=builder /opt/ebpf-demo/bin/ebpf-demo /opt/ebpf-demo/bin/ebpf-demo
CMD ["/opt/ebpf-demo/bin/ebpf-demo"]
