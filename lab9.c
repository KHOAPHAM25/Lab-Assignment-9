#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
//this is for id
    int id;
// this is for name
    char name;
//this is for order
    int order;
//this is for recordtype next
    struct RecordType *next; 
};

// HashType
struct HashType {
//this is for size
    int size;
//this is for struct record type
    struct RecordType **table; // create a pointer to a RecordType
};

// Compute the hash function
int hash(int x, int tableSize) {
  //this is a hash function 
    return x % tableSize; // hash function is x % tableSize
}

// Parses input file to a RecordType array
int parseData(char *inputFileName, struct RecordType **ppData) {
  // file open input
    FILE *inFile = fopen(inputFileName, "r");
  // data size
    int dataSz = 0;
  //in for i and n
    int i, n;
  //character C
    char c;
  //struct record type
    struct RecordType *pRecord;
  // Data is NULL
    *ppData = NULL;
//FILE 
    if (inFile) {
      //scan the file
        fscanf(inFile, "%d\n", &dataSz);
      // ppData struct
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
// ppData is NULL
        if (*ppData == NULL) {
          //print out cannot allocate memory
            printf("Cannot allocate memory\n");
          //exit
            exit(-1);
        }
// the i standards 
        for (i = 0; i < dataSz; ++i) {
          //pRecord to Data plus 1
            pRecord = *ppData + i;
          //scan the file
            fscanf(inFile, "%d ", &n);
          // pRecord to id to n
            pRecord->id = n;
          // scan the file 
            fscanf(inFile, "%c ", &c);
          //recird to name to c
            pRecord->name = c;
          //scan the file
            fscanf(inFile, "%d ", &n);
          //precord to order
            pRecord->order = n;
          // record to next
            pRecord->next = NULL;
        }
//close the file
        fclose(inFile);
    }
//this return data size
    return dataSz;
}

// Prints the records
void printRecords(struct RecordType pData[], int dataSz) {
  // integer i
    int i;
  // print the Reoords 
    printf("\nRecords:\n");
  //i standards
    for (i = 0; i < dataSz; ++i) {
      // print out the daa
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
  //tab down
    printf("\n\n");
}
// Insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize) {
  //int index for the hash in which it calls the hash function
    int index = hash(record->id, tableSize); 
// if Recordtype is NULL
    if (hashTable->table[index] == NULL) { 
     // set 'record' equal to the HashType pointer in the table at index   
      hashTable->table[index] = record; 
    }
    else { //ALL  else
        struct RecordType *cur = hashTable->table[index];
      //traverse the list
        while (cur->next != NULL) { 
          //current to current nest
            cur = cur->next;
        }
      //current to next to record
        cur->next = record; 
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
  //struct record type
    struct RecordType *cur;
  //integer for i
    int i;
// i standards
    for (i = 0; i < tableSize; i++) {
      //hashtable is not NULL
        if (hashTable->table[i] != NULL) {
          //print index
            printf("Index %d -> ", i);
          //current to hashtable to table 
            cur = hashTable->table[i];
          //while current is not NULL 
            while (cur != NULL) {
              //print out hashtable
                printf("%d, %c, %d -> ", cur->id, cur->name, cur->order);
              //current to current to next
                cur = cur->next;
            }
          //print NULL
            printf("NULL\n");
        }
    }
}

int main(void)
{
  // struct record tyoe 
    struct RecordType *pRecords;
  //int record to 0
    int recordSz = 0;
  //integr i
    int i;
// record size 
    recordSz = parseData("input.txt", &pRecords);
  //print the records 
    printRecords(pRecords, recordSz);

    // Initialize the hash table
  // TA CAN CHANGE THE INT SIZE
    int hashTableSize = 6;
  //struct Hashtype
    struct HashType *hashTable = (struct HashType *) calloc(1, sizeof(struct HashType));
  //hastable to size
    hashTable->size = hashTableSize;
  //hashtable calloc 
    hashTable->table = (struct RecordType **) calloc(hashTableSize, sizeof(struct RecordType *));
  //i standards
    for (i = 0; i < recordSz; i++) {
      //insertRecord for hashtable 
        insertRecord(hashTable, &pRecords[i], hashTableSize);
    }
// show the records in hash
    displayRecordsInHash(hashTable, hashTableSize);

    // free all the allocated memory
  //free hash 
    free(hashTable->table);
  // free hash 
    free(hashTable);
  //free records
    free(pRecords);

    return 0;
}
