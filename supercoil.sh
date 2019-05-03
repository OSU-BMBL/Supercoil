	./supercoil -i ../expression-fast-0.6 -j ../../DATA/NC_000913.ptt  -o ../../DATA/NC_000913.gi.operon -p ../../DATA/pathway/ecocyc.gi  -a ../../DATA/NAP_bindingsites -e ../../DATA/ecoli.heg.txt -D expression-value -A ~/Supercoil/DATA/NC_000913_promoter_4144-AT -n 0.3 -g 0.5 -t 15 -S 6 -U 110000
	mv ../expression-fast-0.6.dynamic ../expression-fast-0.6.dynamic.1
	./supercoil -i ../expression-fast-0.6 -j ../../DATA/NC_000913.ptt  -o ../../DATA/NC_000913.gi.operon -p ../../DATA/pathway/ecocyc.gi  -a ../../DATA/NAP_bindingsites -e ../../DATA/ecoli.heg.txt -D expression-value -A ~/Supercoil/DATA/NC_000913_promoter_4144-AT -n 0.3 -g 0.5 -t 15 -S 6 -U 700000
	mv ../expression-fast-0.6.dynamic ../expression-fast-0.6.dynamic.2
	cat ../expression-fast-0.6.dynamic.1 ../expression-fast-0.6.dynamic.2 > ../expression-fast-0.6.dynamic.opt  
