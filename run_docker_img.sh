#!/bin/bash

docker build -t ft_traceroute_img .
docker run -itd --name ft_traceroute -v $(pwd)/srcs:/opt/ft_traceroute ft_traceroute_img
docker exec -it ft_traceroute "/bin/bash"
