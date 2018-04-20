#include <stdio.h>
#include <stdlib.h>

#define SIZE 26

void decode(char matrix[SIZE][SIZE], char *key, char *mess, char *out);
void get_input(char **key, int * k_len, char **mess, int *m_len, char *file);
void create_cipher(char matrix[SIZE][SIZE]);
void print_cipher(char matrix[SIZE][SIZE]);

int main(int argc, char **argv)
{
	char cipher[SIZE][SIZE];
	char *keyword, *message, *output;
	int key_length, message_length;

	if (argc != 2) {
		printf("Usage: ./cipher <challenge input>\n");
		exit(0);
	}

	printf("Alphabet Cipher\n");

	create_cipher(cipher);
	//print_cipher(cipher);

	get_input(&keyword, &key_length, &message, &message_length, argv[1]);
	printf("\tkey length:%d\n",key_length);
	printf("\tmessage length:%d\n",message_length);
	printf("\tkeyword:%s\n",keyword);
	printf("\tmessage:%s\n",message);

	output = malloc(message_length + 1);
	if (output ==  NULL) {
		printf("ERROR: Not enough resources\n");
		exit(0);
	}

	decode(cipher, keyword, message, output);
	printf("\toutput: %s\n",output);

	return 0;
}

void decode(char matrix[SIZE][SIZE], char *key, char *mess, char *out)
{
	int r, c, i, j;
	char *k;
	k = key;

	while (*mess != '\0') {
		r = *k - 'a';
		c = *mess - 'a';
		*out = matrix[r][c];
		mess++;
		k++;
		out++;
		if (*k == '\0')
			k = key;
	}
	*out = '\0';
}

void get_input(char **key, int * k_len, char **mess, int *m_len, char *file)
{
	FILE *fd;
	char c, *k, *m;
	fd = fopen(file, "r");
	*k_len = 0;
	*m_len = 0;

	// Get keyword
	while (fgetc(fd) != ' ') {
		++*k_len;
	}
	fgetc(fd);

	// Get message
	while (fgetc(fd) != EOF) {
		++*m_len;
	}

	*key = malloc(*k_len + 1);
	if (*key ==  NULL) {
		printf("ERROR: Not enough resources\n");
		exit(0);
	}
	*mess = malloc(*m_len + 1);
	if (*mess ==  NULL) {
		printf("ERROR: Not enough resources\n");
		exit(0);
	}
	k = *key;
	m = *mess;
	fclose(fd);

	fd = fopen(file, "r");
	c = fgetc(fd);
	while (c != ' ') {
		*k++ = c;
		c = fgetc(fd);
	}
	c = fgetc(fd);
	while (c != EOF) {
		*m++ = c;
		c = fgetc(fd);
	}
	k = *key;
	m = *mess;
	k[*k_len] = '\0';
	m[*m_len] = '\0';
}

void create_cipher(char matrix[SIZE][SIZE])
{
	int r, c;

	for (c = 0; c < SIZE; c++) {
		matrix[0][c] = 'a' + c;
	}

	for (r = 1; r < SIZE; r++) {
		for (c = 0; c < SIZE - 1; c++) {
			matrix[r][c] = matrix[r - 1][c + 1];
		}
		matrix[r][c] = matrix[r - 1][0];
	}
}

void print_cipher(char matrix[SIZE][SIZE])
{
	int r, c;

	for (r = 0; r < SIZE; r++) {
		printf("\t");
		for (c = 0; c < SIZE; c++) {
			printf("%2c", matrix[r][c]);
		}
		printf("\n");
	}
}
