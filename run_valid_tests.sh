bold=$(tput bold)
normal=$(tput sgr0)

for i in valid_tests/*.s; do
	echo "${bold} $i ${normal}"  && cat $i && ./abstract_vm $i

done
