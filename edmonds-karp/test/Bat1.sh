#!/bin/bash

edmondskarp=./edmonds-karp.bin

echo "Testando algoritmo de Edmonds-Karp"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
    vertice_destino=$(grep $i gabarito_edmonds-karp.txt | cut -d ' ' -f 2);

    echo -n "Fluxo máximo está correto? ";
    val=$($edmondskarp -f $i -d ${vertice_destino} | cut -d ':' -f 2);
	correto=$(grep $i gabarito_edmonds-karp.txt | cut -d ' ' -f 3);
	[ $val -eq $correto ] && echo -e "\e[32mSim\e[0m" || echo -e "\e[31mNão\e[0m";

	$edmondskarp -f $i -d ${vertice_destino} -c > temp;
	j=$(basename $i);
	diff -w temp ./sp/$j > /dev/null ;
	if [ $? -eq 0 ]; then
		echo -e "Rede resultante \e[32mOK\e[0m"
	else
		echo -e "\e[31mRede resultante incorreta\e[0m";
	fi
	rm temp;
done
