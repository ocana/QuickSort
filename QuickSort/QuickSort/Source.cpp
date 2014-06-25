#include <iostream>
#include <cstdlib>
#include <ctime>

#define NUM_CHARS_TO_SKIP 1000

using std::cin;
using std::cout;
using std::endl;

typedef int(*PIVOT_FUNC_PTR)(int*, int, int);

enum option{
	first,
	random,
	middle,
	median_of_3
};

PIVOT_FUNC_PTR get_pivot_election_algorithm(option op);
void fill_numbers_from_args(int* numbers, const int argc, char** argv);
void print_array(const int* array, const int length);
option get_chosen_option();

void quick_sort(const int length, int* numbers, PIVOT_FUNC_PTR);

void quicksort(int* numbers, int i, int j, PIVOT_FUNC_PTR);
void swap(int* i, int* j);


int main(int argc, char* argv[]){
	srand(time(nullptr));

	int numbers_length = argc - 1;
	int* numbers = new int[numbers_length];
	fill_numbers_from_args(numbers, argc, argv);
	
	cout << "Sorting: ";
	print_array(numbers, numbers_length);
	cout << endl;

	option op = get_chosen_option();

	quick_sort(numbers_length, numbers, get_pivot_election_algorithm(op));

	cout << "Sorted: ";
	print_array(numbers, numbers_length);
	cout << endl;

	delete numbers;

	cin.ignore();
	cin.ignore();
	return 0;
}

void quick_sort(const int length, int* numbers, PIVOT_FUNC_PTR choose_pivot_func){
	
	quicksort(numbers, 0, length - 1, choose_pivot_func);
}

void quicksort(int* numbers, int i, int j, PIVOT_FUNC_PTR choose_pivot_func){
	int start_index = i;
	int end_index = j;

	if (start_index >= end_index){
		return;
	}
	
	int pivot_index = choose_pivot_func(numbers, i, j);
	swap(numbers + i, numbers + pivot_index); // Store chosen pivot into the first position.
	pivot_index = i;

	i++;
	while (i <= j)
	{
		if (numbers[i] > numbers[pivot_index] && numbers[j] <= numbers[pivot_index]){
			swap(numbers + i, numbers + j);
			continue;
		}

		if (numbers[i] <= numbers[pivot_index])
		{
			i++;
		}
		
		if (numbers[j] > numbers[pivot_index])
		{
			j--;
		}
	}

	swap(&numbers[pivot_index], numbers + j);
	quicksort(numbers, start_index, j - 1, choose_pivot_func);
	quicksort(numbers, j + 1, end_index, choose_pivot_func);
}

void swap(int* i, int* j){
	int aux = *i;
	*i = *j;
	*j = aux;
}

void fill_numbers_from_args(int* numbers, const int argc, char** argv){
	argv++; // Skip first argv position (the program name)
	for (int i = 1; i < argc; i++)
	{
		*(numbers++) = atoi(*(argv++));
	}
}

void print_array(const int* array, const int length){
	for (int i = 0; i < length; i++)
	{
		cout << *(array++) << ' ';
	}
}

option get_chosen_option(){
	int op = 0;
	while (true)
	{
		cout << endl << "Please, choose a pivot election algorithm: " << endl
			<< " 0 - First element" << endl
			<< " 1 - Random element" << endl
			<< " 2 - Middle element" << endl
			<< " 3 - Median of the first, middle and last element" << endl << endl;
		cin >> op;

		if (cin && op >= 0 && op < 4){
			cout << endl;
			return option(op);
		}
		
		cin.clear();
		cin.ignore(NUM_CHARS_TO_SKIP, '\n');

		cout << "Incorrect option." << endl;
	}
}

int median_of_three(int* numbers, int i, int j) {
	int middle = get_pivot_election_algorithm(option(2))(numbers, i, j);
	if (numbers[j] < numbers[i])
	{
		swap(numbers + j, numbers + i);
	}

	if (numbers[middle] < numbers[i])
	{
		swap(numbers + middle, numbers + i);
	}

	if (numbers[j] < numbers[middle])
	{
		swap(numbers + middle, numbers + j);
	}

	return middle;
};

PIVOT_FUNC_PTR get_pivot_election_algorithm(option op){
	switch (op)
	{
	case first:
		return [](int* numbers, int i, int j) {return i; };
	case random:
		return [](int* numbers, int i, int j) {
			int length = j - i + 1;
			if (length == 0) return i + length;
			return i + (rand() % length); 
		};
	case middle:
		return [](int* numbers, int i, int j) -> int {return (i + j) / 2; };
	case median_of_3:
		return median_of_three;
	}
}