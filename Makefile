# Compiler and flags for C++
CXX = mpic++
CXXFLAGS = -std=c++11

# Directories and files
RUST_TARGET = target/release/mpi_server_client
CPP_SOURCE = cpp/client.cpp
CPP_TARGET = target/client

# Default target
all: rust cpp

# Build Rust project
rust:
	cargo build --release

# Build C++ project
cpp: rust
	@mkdir -p target
	$(CXX) $(CXXFLAGS) -o $(CPP_TARGET) $(CPP_SOURCE)

# Clean up build artifacts
clean:
	cargo clean
	rm -f $(CPP_TARGET)

# Phony targets
.PHONY: all rust cpp clean
