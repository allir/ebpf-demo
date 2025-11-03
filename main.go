// SPDX-License-Identifier: MIT
package main

import (
	"context"
	"fmt"
	"log"
	"os"
	"os/signal"
	"sync"
	"syscall"

	"github.com/cilium/ebpf/rlimit"

	"github.com/allir/ebpf-demo/internal/ebpf"
)

func main() {
	// Set up signal handling to gracefully shut down on interrupt signals.
	ctx, stop := signal.NotifyContext(context.Background(), os.Interrupt, syscall.SIGTERM)

	// Allow the current process to lock memory for eBPF resources.
	must(rlimit.RemoveMemlock(), "memlock error")

	processExec := new(ebpf.ProcessExecTracePoint)
	must(processExec.Start(), "processExec start")
	defer func() {
		err := processExec.Close()
		if err != nil {
			fmt.Println("Error closing processExec: ", err)
		}
	}()

	// Set up waitgroup to wait for goroutines to finish.
	wg := sync.WaitGroup{}

	// Start a goroutine to read events from the eBPF program.
	wg.Go(
		func() {
			must(processExec.Read(ctx), "processExec read")
		})

	// Wait for a signal to stop the program.
	// Once the signal is received, cancel the context and wait for the reader to finish.
	<-ctx.Done()
	log.Println("Received signal, exiting program...")
	stop()

	wg.Wait()
}

func must(err error, msg ...string) {
	if err != nil {
		m := "error"
		if msg != nil {
			m = msg[0]
		}
		log.Fatalf("%s: %v", m, err)
	}
}
