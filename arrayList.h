typedef struct {
    int* buffer;
    int length;
    int contentLength;
} ArrayList;

void InitArrayList(ArrayList* al, const unsigned int initialLength);

void Append(ArrayList* al, const int n);

void Remove(ArrayList *al, const unsigned int index);

int ALGet(ArrayList* al, const unsigned int index);

void CleanupArraylist(ArrayList* al);

