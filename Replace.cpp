#include <iostream>
using namespace std;

void replace(int arr[], int oldItem, int newItem, int first, int last) {
	if (last > first) {
		int mid = (first + last) / 2;

		replace(arr, oldItem, newItem, first, mid);
		replace(arr, oldItem, newItem, mid + 1, last);
	}
	else if (arr[first] == oldItem)
		arr[first] = newItem;
}

int main() {
	int size, entry, oldItem, newItem;

	cout << "How many numbers do you wish to input? ";
	cin >> size;

	int* arr = new int[size];

	cout << "Type number and press enter for all numbers separately: \n";
	for (int i = 0; i < size; i++) {
		cin >> entry;
		arr[i] = entry;
	}

	cout << "Here is your list of numbers: ";
	for (int j = 0; j < size; j++)
		cout << arr[j] << " ";

	cout << "\nEnter the number you would like to replace: ";
	cin >> oldItem;

	cout << "Enter the number to replace the old number: ";
	cin >> newItem;

	replace(arr, oldItem, newItem, 0, size - 1);

	cout << "\nYour list after replacement: ";
	for (int k = 0; k < size; k++)
		cout << arr[k] << " ";
}