#include "../headers/PmergeMe.hpp"

int error(std::string error_msg)
{
    std::cerr << error_msg << std::endl;
    return (1);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
        return (error("Error: Too few arguments."));

    clock_t start, end;
    double time_vec, time_deq;
    std::vector<int> nbs_vector;
    std::deque<int> nbs_deque;
    std::string numbers_vec, numbers_deq;

    start = clock();
    numbers_vec = PmergeMeVector::concatenateStrings(argc, argv);
    if (!PmergeMeVector::fillContainer(nbs_vector, numbers_vec))
        return (error("Error: Invalid input"));
    if (PmergeMeVector::isSorted(nbs_vector))
        return (error("Error: The number list is already sorted."));
    PmergeMeVector::sortNumbers(nbs_vector);
    end = clock();
    time_vec = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    start = clock();
    numbers_deq = PmergeMeDeque::concatenateStrings(argc, argv);
    if (!PmergeMeDeque::fillContainer(nbs_deque, numbers_deq))
        return (error("Error: Invalid input"));
    if (PmergeMeDeque::isSorted(nbs_deque))
        return (error("Error: The number list is already sorted."));
    PmergeMeDeque::sortNumbers(nbs_deque);
    end = clock();
    time_deq = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    // std::cout << "Before: ";
    // PmergeMeVector::displayContainer(nbs_vector);
    // std::cout << "After: ";
    // PmergeMeVector::displayContainer(nbs_vector);
    std::cout << "Before: ";
    PmergeMeDeque::displayContainer(nbs_deque);
    std::cout << "After: ";
    PmergeMeDeque::displayContainer(nbs_deque);
    std::cout << "Time to process a range of " << nbs_vector.size() << " elements with std::vector : " << time_vec << "µs" << std::endl;
    std::cout << "Time to process a range of " << nbs_vector.size() << " elements with std::deque : " << time_deq << "µs" << std::endl;
}
