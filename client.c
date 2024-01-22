#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void	exit_handler()
{
	printf("Usage: ./client <pid> <msg>\n");
	exit(1);
}

void	send_char(pid_t server_pid, unsigned char c)
{
	int						i;
	unsigned char	curr_bit;

	i = 7;
	while (i >= 0)
	{
		curr_bit = (c >> i--) % 2;
		if (curr_bit == 0)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	char		*msg;
	pid_t		server_pid;

	if (argc != 3)
		exit_handler();
	server_pid = atoi(argv[1]);
	if (server_pid <= -1)
		exit_handler();
	msg = argv[2];
	while (*msg)
		send_char(server_pid, *(msg++));
	send_char(server_pid, '\0');
	return (0);
}
