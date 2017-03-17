/** 
    An MPI program to compute factors of a number using 2 MPI processes:

    Rank 0: Operates as manager (performs I/O) 
    Rank 1: Operates as worker  (computes number of factors)

    Copyright (C) 2015 raodm@miamiOH.edu
*/

#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


const int NUMBER_TAG  = 1;
const int FACTORS_TAG = 2;

const int MANAGER_RANK = 0;
const int WORKER_RANK  = 1;

// Prototype to keep compiler happy
int getFactorCount(const long long n);

void doWorkerTasks() {
    long long number;
    do {
        /* read number from the manager (rank == 0) */
        MPI_Recv(&number, 1, MPI_LONG_LONG_INT, MANAGER_RANK, NUMBER_TAG,
                 MPI_COMM_WORLD, NULL);
        if (number != -1) {
            int factors = getFactorCount(number);
            /* send number of factors back to the manager */
            MPI_Send(&factors, 1, MPI_INT, MANAGER_RANK, FACTORS_TAG,
                     MPI_COMM_WORLD);
        }
    } while (number != -1);
}

void listen(int count, std::vector<long long>& nums, const std::string& path) {
    std::ifstream data(path);
    long long number;
    int factors;
    // Continually feed workers more input until at EOF
    while (count > 0) {
        MPI_Status status;
        MPI_Recv(&factors, 1, MPI_LONG_LONG_INT, MPI_ANY_SOURCE, FACTORS_TAG,
                 MPI_COMM_WORLD, &status);
        count--;
        std::cout  << "Number " << nums[status.MPI_SOURCE] << " has " << factors
                   << " factors.\n";
        if (data >> number) {
            MPI_Send(&number, 1, MPI_LONG_LONG_INT, status.MPI_SOURCE,
                     NUMBER_TAG, MPI_COMM_WORLD);
                count++;
                nums[status.MPI_SOURCE] = number;
        }
    }
}

void doManagerTasks(const std::string& path) {
    std::ifstream data(path);
    int procs, rank;
    if (!data.good()) {
        std::cout << "Unable to open " << path << " for input. "
                  << "Manager aborting.\n";
    } else {
        MPI_Comm_size(MPI_COMM_WORLD, &procs);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        long long number; int count = 0;
        std::vector<long long> nums(procs, 0);
        for (int i = 1; i < procs; i++) {
            data >> number;
            MPI_Comm_rank(MPI_COMM_WORLD, &rank);
            MPI_Send(&number, 1, MPI_LONG_LONG_INT, i, NUMBER_TAG,
                     MPI_COMM_WORLD);
            nums[i] = number; count++;
        }
        listen(count, nums, path);
    }
    // send -1 to worker to inform worker to end processing
    long long number = -1;
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    for (int p = 1; p < procs; p++) {
        MPI_Send(&number, 1, MPI_LONG_LONG_INT, p, NUMBER_TAG, MPI_COMM_WORLD);
    }
}

//------------------------------------------------------------------
//          DO   NOT  MODIFY  CODE  BELOW  THIS  LINE
//------------------------------------------------------------------

/**
   This is a simple function that can be used to determine the number
   of factors for a given integer i.
*/
int getFactorCount(const long long n) {
    long long i = 0;
    int factorCount = 0;

    for (i = 1; (i <= n); i++) {
        if (!(n % i)) {
            factorCount++;
        }
    }
    return factorCount;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 2) {
        std::cerr << "This program must be run with at least 2 processes!\n";
    } else if (argc != 2) {
        std::cerr << "Specify name of file to process\n";
    } else {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        if (rank == 0) {
            doManagerTasks(argv[1]);
        } else {
            doWorkerTasks();
        }
    }

    MPI_Finalize();
    return 0;
}

// End of source code.
