#ifndef GENERIC_FUNCTIONS_H
#define GENERIC_FUNCTIONS_H

struct GenericData {
    int type; // 0 para int, 1 para float, 2 para string
    union {
        int intValue;
        float floatValue;
        char *stringValue;
    } data;
};

int readGenericData(struct GenericData *data, int *dataSize);
int printGenericData(struct GenericData *data, int dataSize);

#endif /* GENERIC_FUNCTIONS_H */
