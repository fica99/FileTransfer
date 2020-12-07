# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/14 13:42:05 by aashara           #+#    #+#              #
#    Updated: 2020/12/07 13:38:28 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

client := client

server := server

.PHONY: all $(client) $(server) clean fclean re

all: $(client) $(server)

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
