#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Remove the element at index 2 (which is the third element, 3)
    int indexToRemove = 2;
    if (indexToRemove >= 0 && indexToRemove < numbers.size()) {
        numbers.erase(numbers.begin() + indexToRemove);
    }

    // Print the updated vector
    for (int number : numbers) {
        std::cout << number << " ";
    }

    return 0;
}