# Experiments

## Language agnostic MPI
Run `mpirun -n 1 target/release/server : -n 1 target/client --id cpp : -n 1 target/release/client --id rust` to run the server in Rust and the clients in C++ and Rust.

Known issues: The C++ client does receive "32512" instead of "0".