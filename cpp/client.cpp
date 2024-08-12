#include <mpi.h>
#include <iostream>
#include <string>
#include <cxxopts.hpp>

void no_comm(const std::string& id) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::cout << "Client " << id << " rank " << rank << " of " << size << "!" << std::endl;
}

void ping_pong(const std::string& id) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm comm = MPI_COMM_WORLD;

    // Client process
    int received;
    MPI_Status status;
    MPI_Recv(&received, 1, MPI_INT32_T, 0, 0, comm, &status);
    std::cout << "[Client " << id << " " << rank << "] Received message from server: " << received << std::endl;
    
    // Send message back to server
    MPI_Send(&received, 1, MPI_INT32_T, 0, 0, comm);
    std::cout << "[Client " << id << " " << rank << "] Sent message back to server" << std::endl;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    cxxopts::Options options("MPI Program", "A simple MPI program");
    options.add_options()
        ("i,id", "Id of client", cxxopts::value<std::string>());

    auto result = options.parse(argc, argv);
    std::string id = result["id"].as<std::string>();

    std::cout << "Hello from client " << id << "!" << std::endl;
    no_comm(id);
    ping_pong(id);

    MPI_Finalize();
    return 0;
}
