#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
	struct RecordType * next;
};

// Fill out this structure
struct HashType
{
	struct RecordType * head;
};

// Compute the hash function
int hash(int x, int tablesize)
{
	return (x%tablesize);
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}



// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}


//transfers record array into hashTable array
void insertRecord(struct HashType * hashTable, struct RecordType * record, int tableSize, int recordSize){
	int hmod;
	struct RecordType * current;

	for(int i = 0; i<recordSize; i++){
		//assign hash
		hmod = hash(record[i].id, tableSize);

		//checks for availability
		if(hashTable[hmod].head == NULL){
			hashTable[hmod].head = &(record[i]);
		}

		//if filled goes to end of chain and adds recrod there
		else{
			current = hashTable[hmod].head;
			while(current->next != NULL){
				current = current->next;
			}
			current->next = &record[i];
		}

	}
}



// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;
	struct RecordType * current;
	printf("Records Hash:\n");
	for (i=0;i<hashSz;i++)
	{
		current = pHashArray[i].head;
		// if index is occupied with any records, print all
		if(current != NULL){
			//prints until node is pointing at NULL
			while(current->next != NULL){
				printf("\tAt index %d: %d %c %d\n", i, current->id, current->name, current->order);
				current = current->next;
			}
			printf("\tAt index %d: %d %c %d\n", i, current->id, current->name, current->order);
			

		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	
	// hash table
	// create a variable hashTableSize and assign it a value
	int hSize = 11;
    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    struct HashType * hTable = calloc(recordSz, sizeof(struct HashType));
	// for each record in pRecords, insert it into the hash table using the insertRecord function
	insertRecord(hTable, pRecords, hSize, recordSz);
    // call the display records function
	displayRecordsInHash(hTable, recordSz);
    // free all the allocated memory
    free(pRecords);
	free(hTable);

    return 0;
}