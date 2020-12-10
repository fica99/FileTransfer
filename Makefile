client := client

server := server

.PHONY: all $(client) $(server) clean fclean re

all: $(client) $(server)

run_client: all
	./FileClient -i 0.0.0.0 -p 2222 -f $(client) $(server)

run_server: all
	./FileServer -p 2222


$(client):
	$(MAKE) all --no-print-directory -C $(client)

$(server):
	$(MAKE) all --no-print-directory -C $(server)

clean:
	$(MAKE) clean --no-print-directory -C $(client)
	$(MAKE) clean --no-print-directory -C $(server)

fclean:
	$(MAKE) fclean --no-print-directory -C $(client)
	$(MAKE) fclean --no-print-directory -C $(server)

re: fclean all
