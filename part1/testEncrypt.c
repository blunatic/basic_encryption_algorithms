#include <stdio.h>
#include <string.h>

void encryptDecrypt(char *input, char *output) {
	char key[] = {'G'}; //Can be any chars, and any size array
	
	int i;
	for(i = 0; i < strlen(input); i++) {
		// XOR bitwise flipping
		int flip = input[i] ^ key[i % (sizeof(key)/sizeof(char))];
		// set output to NOT bitwise shift of the previous XOR
		// will create NON-ASCII chars, adding a layer of diffusion
		output[i] = flip;
	}
}

int main (int argc, char *argv[]) {
	char baseStr[] = "this is a test alskjdflkasjdflkjas";
	
	char encrypted[strlen(baseStr)];
	encryptDecrypt(baseStr, encrypted);
	printf("\nEncrypted:%s\n", encrypted);
	
	char decrypted[strlen(baseStr)];
	encryptDecrypt(encrypted, decrypted);
	printf("\nDecrypted:%s\n\n", decrypted);
}