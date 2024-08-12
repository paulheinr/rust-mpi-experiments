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

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    cxxopts::Options options("MPI Program", "A simple MPI program");
    options.add_options()
        ("i,id", "Id of client", cxxopts::value<std::string>());

    auto result = options.parse(argc, argv);
    std::string id = result["id"].as<std::string>();

    std::cout << "Hello from client " << id << "!" << std::endl;
    no_comm(id);

    MPI_Finalize();
    return 0;
}
