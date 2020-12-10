#include <unistd.h>
#include <stdlib.h>
#include "./errors.h"

// The Errors Module
void	ft_error_and_quit(int n)
{
	// This one is to handle the MAP ERRORS
	if (n == 1) {
		write(2, "INVALID MAP !!", 15);
		exit(EXIT_FAILURE);
	}

	// I need to create one else to handle the memory errors
	if (n == 2) {
		write(2, "The memory is not been allocated successfully !!!", 50);
		exit(EXIT_FAILURE);
	}

	if (n == 3) {
		write(2, "There is more than one player in the map INVALID!", 50);
		exit(EXIT_FAILURE);
	}
}