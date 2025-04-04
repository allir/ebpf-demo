# ebpf-demo

A demo eBPF application using Go and C.

## Program Description

This project demonstrates how to build and run eBPF programs in user space using Go and C. It includes:

- An eBPF program for tracing process execution events using the `sched_process_exec` tracepoint.
- Architecture-agnostic tracing by leveraging this tracepoint, which is stable across kernel versions and architectures.
- A Go user-space application that loads, attaches, and reads events from the eBPF program via a ringbuffer.
- Example setup for cross-platform development (macOS host, Linux VM target).

The template is suitable for extending with additional eBPF programs and user-space integrations.

**Why use `sched_process_exec` instead of `sys_enter_execve`?**

`sched_process_exec` is a tracepoint that is triggered after a process successfully executes a new program (i.e., after `execve` completes). This provides a reliable and architecture-independent way to observe process execution events, including the process's new PID and command-line arguments. In contrast, `sys_enter_execve` is triggered before the syscall is executed, may not reflect the final state, and can be less portable across kernel versions and architectures. Using `sched_process_exec` ensures more accurate and consistent tracing of process execution events.

## Requirements

### macOS

- [Lima](https://lima-vm.io)
- QEMU

When running on **macOS** you need to build and run this in a Linux virtual machine (VM). On macOS 13.0+ VMs can also be run
using macOS's Virtualization Framework (**vz**) instead of QEMU but it has some limitations so QEMU is preferred.

**_Note_**: Some of the limitations of **vz** are that it fails to cross-compile for multiple architectures and also can not
emulate a different architecture and can only run VMs using its own native architecture; example M3 Macs (arm64 arch) can only
run arm64 VMs.

#### Install Dependencies (macOS)

```shell
brew bundle
```

Start a virtual machine using Lima and QEMU, and getting a terminal:

```shell
limactl start ./lima/ebpf-dev.yaml
limactl shell ebpf-dev
```

- To start the VM using a different architecture add `--arch=<ARCH>` where `<ARCH>` can be one of: `x86_64` or `aarch64`.

## Linux

- Go
- linux-tools
- build-essential
- llvm
- clang
- libbpf-dev
- libelf-dev
- libpcap-dev
- bpftool
- curl

### Install Dependencies (Linux)

- [Install Go](https://go.dev/doc/install)
- Install dependencies:

    ```shell
    export KERNEL_VERSION=`uname -r`
    apt-get update -q
    apt-get install -q -y \
    apt-transport-https ca-certificates curl \
    linux-tools-common linux-tools-generic linux-tools-${KERNEL_VERSION} \
    build-essential llvm clang \
    libbpf-dev libelf-dev libpcap-dev
    ```

- Install BPFTool

    ```shell
    git clone --recurse-submodules https://github.com/libbpf/bpftool.git /tmp/bpftool
    pushd /tmp/bpftool/src
    make install
    popd
    ```

## Building

On a linux environment run `make build`.

## Running

Running applications that load BPF programs needs privilege so running the application as root or using `sudo` is required.

```shell
sudo ./bin/ebpf-demo
```

## Links

Some useful links for additional information and learning about **eBPF**:

- [Official Documentary - eBPF: Unlocking the Kernel](https://www.youtube.com/watch?v=Wb_vD3XZYOA)
- [eBPF.io](https://ebpf.io)
- [eBPF Docs](https://docs.ebpf.io)
- [eBPF Labs](https://ebpf.io/labs/)
- [eBPF Books](https://ebpf.io/get-started/#books)
