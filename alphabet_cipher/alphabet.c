#include <stdio.h>
#include <stdlib.h>

#define SIZE 26

void create_cipher(char cipher[SIZE][SIZE]);
void print_cipher(char cipher[SIZE][SIZE]);
void get_key_mess(char **keyp, int * kl, char **messp, int *ml, char *file);

int main(int argc, char **argv)
{
	char cipher[SIZE][SIZE];
	char *keyword, *message, *output;
	int *k_len, *m_len;
	int i, j;

	if (argc != 2) {
		printf("Usage: ./cipher <filename>\n");
		return 0;
	}

	printf("Alphabet Cipher\n");
	create_cipher(cipher);
	print_cipher(cipher);
	get_key_mess(&keyword, k_len, &message, m_len, argv[1]);
	/*
	printf("\tk_len:%d\n",*k_len);
	printf("\tm_len:%d\n",*m_len);
	printf("\tkeyword:%s\n",keyword);
	printf("\tmessage:%s\n",message);

	output =  malloc(*m_len + 1);
	if (output == NULL) {
		printf("\tERROR: No resources\n");
		exit(1);
	}

	i = j = 0;

	while (message[j] != '\0') {
		int r, c;
		r = (int) keyword[i] - 'a';
		c = (int) message[j] - 'a';
		output[j] = cipher[r][c];
		printf("r:%d c:%d o:%c\n", r, c, cipher[r][c]);

		i++;
		j++;
		if (i == *k_len)
			i = 0;
	}
	output[*m_len] = '\0';

	printf("\tOutput:%s\n",output);
	*/

	return 0;
}

void get_key_mess(char **keyp, int * kl, char **messp, int *ml, char *file)
{
	FILE *fd;
	int key_length, mess_length;
	char c;
	char *k, *m, *key, *mess;
	key_length = mess_length = 0;

	fd = fopen(file, "r");
	while (c = fgetc(fd) != ' ') {
		key_length++;
	}
	fgetc(fd); // Skip space
	while (fgetc(fd) != EOF) {
		mess_length++;
	}


	key = malloc(key_length + 1);
	if (key == NULL) {
		printf("\tERROR: No resources\n");
		exit(1);
	}
	mess = malloc(mess_length + 1);
	if (mess == NULL) {
		printf("\tERROR: No resources\n");
		exit(1);
	}

	*kl = key_length;
	//printf("wtf:%d\n",*kl);
	*ml = mess_length;
	fclose(fd);

	k = key;
	m = mess;
	*keyp = key;
	*messp = mess;

	fd = fopen(file, "r");
	c = fgetc(fd);
	while (c != ' ') {
		*k++ = c;
		c = fgetc(fd);
	}
	key[key_length] = '\0';

	c = fgetc(fd);
	while (c != EOF) {
		*m++ = c;
		c = fgetc(fd);
	}
	mess[mess_length] = '\0';
	//printf("\tmessage:%s\n",mess);
}

void create_cipher(char cipher[SIZE][SIZE])
{
	int r, c;

	for (c = 0; c < SIZE; c++) {
		cipher[0][c] = 'a' + c;
	}

	for (r = 1; r < SIZE; r++) {
		for (c = 0; c < SIZE; c++) {
			cipher[r][c] = cipher[r - 1][c + 1];
		}
		cipher[r][SIZE - 1] = cipher[r - 1][0];
	}
}
void print_cipher(char cipher[SIZE][SIZE])
{
	int r, c;

	for (r = 0; r < SIZE; r++) {
		printf("\t");
		for (c = 0; c < SIZE; c++) {
			printf("%2c", cipher[r][c]);
		}
		printf("\n");
	}
}
