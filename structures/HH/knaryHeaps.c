// int child = k *i + j // (1...k)
// int parent = (i - 1) / k
// i never changes!

void max_heapify_kary(int arr[], int n, int i, int k)
{
    // n -> chil
    int largest = i;
    for (int j = 1; j <= k; j++)
    {
        int child = k * i + j;
        if (child < n && arr[child] > arr[largest])
        {
            largest = child;
        }
    }
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        max_heapify_kary(arr, n, largest, k);
    }
}

void min_heapify_kary(int arr[], int n, int i, int k)
{
    int smallest = i;
    for (int j = 1; j <= k; j++)
    {
        int child = k * i + j;
        if (child < n && arr[child] < arr[smallest])
        {
            smallest = child;
        }
    }
    if (smallest != i)
    {
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        min_heapify_kary(arr, n, smallest, k);
    }
}