#include <iostream>
#include <fstream>
using namespace std;

void Merge(int list[], int first, int middle, int last) {
	int mergeSize = last - first + 1;
	int mergeIndex = 0;
	int leftList = first;
	int rightList = middle + 1;
	int* mergedList = new int[mergeSize];

	while (leftList <= middle && rightList <= last) {
		if (list[leftList] >= list[rightList]) {
			mergedList[mergeIndex] = list[leftList];
			++leftList;
		}
		else {
			mergedList[mergeIndex] = list[rightList];
			++rightList;
		}
		++mergeIndex;
	}

	while (leftList <= middle) {
		mergedList[mergeIndex] = list[leftList];
		++leftList;
		++mergeIndex;
	}

	while (rightList <= last) {
		mergedList[mergeIndex] = list[rightList];
		++rightList;
		++mergeIndex;
	}

	for (int i = 0; i < mergeSize; i++)
		list[first + i] = mergedList[i];

	delete[] mergedList;
}

void MergeSort(int list[], int first, int last) {
	if (first < last) {
		int middle = (first + last) / 2;

		MergeSort(list, first, middle);
		MergeSort(list, middle + 1, last);
		Merge(list, first, middle, last);
	}
}

int main() {
	int number, size;
	char loop;

	do {
		cout << "How many numbers would you like to enter? ";
		cin >> size;

		int* list = new int[size];

		cout << "Enter each number separately: ";

		for (int i = 0; i < size; i++) {
			cin >> number;
			list[i] = number;
		}

		cout << "Original List: ";

		for (int i = 0; i < size; i++) {
			cout << list[i] << " ";
		}

		MergeSort(list, 0, size - 1);

		cout << "\n\nList in descending order: ";
		for (int j = 0; j < size; j++)
			cout << list[j] << " ";

		delete[] list;

		cout << "\n\nWould you like to enter another list (Enter y or n): ";
		cin >> loop;
	} while (loop == 'y');
}