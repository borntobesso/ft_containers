#! /bin/bash

./ft_containers > log_ft
./std_containers > log_std

diff log_ft log_std